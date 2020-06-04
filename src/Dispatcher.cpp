#include <iostream>
#include "Dispatcher.h"

Dispatcher::Dispatcher(PoolsArray *poolsArray) :
		DispatcherBase(poolsArray)
{
}

/*
 * Tries to acquire an available empty slot in any pool by scanning
 * the pool array sequentially starting from the latest generation.
 * Returns true if succeeds and stores the pool and slot
 * indices in the request structure.
 * If doesn't find anything available after traversing the entire
 * pool array, returns false.
 */
bool Dispatcher::acquireChildSlot(WorkReqInternal *q)
{
	// Look for an empty slot in the next pool for a new child.
	size_t i = q->parentPoolIndex + 1;

	// Try to lock any slot on in this pool.
	for (int j = pools->getSize(i) - 1; j >= 0; j--) {
		if (pools->tryLockIfEmpty(i, j)) {
			// If successful, save the pool/slot indices and return true.
			q->childPoolIndex = i;
			q->childSlotIndex = j;
			return true;
		}
	}

	// If unsuccessful return false.
	return false;
}

/*
 * Tries to acquire an available task in the pool preceding the child's
 * pool. Must be called after a successful call to acquireChildSlot.
 * Scans the respective pool sequentially.
 * Returns true if succeeds and stores the parent's pool and slot
 * indices in the request structure as well as a pointer to the task.
 * If doesn't find anything available after traversing the entire
 * pool, returns false.
 */
bool Dispatcher::acquireParent(WorkReqInternal *q)
{
	for (int i = pools->getSize() - 1; i >= 0; i--) {
		for (int j = pools->getSize(i) - 1; j >= 0; j--) {
			if (pools->tryLockIfFull(i, j)) {
				q->parentPoolIndex = i;
				q->parentSlotIndex = j;
				q->parent = pools->getTask(i, j);
				return true;
			}
		}
	}
	q->parentPoolIndex = q->parentSlotIndex = -1;
	q->parent = nullptr;
	return false;
}

/*
 * Acquires an available task and an available empty spot for a child
 * in successive pools. Stores a pointer to the task and the pool and
 * slots indices in the request. Returns true. Blocks the caller.
 *
 * Returns false after a call to StopWorkers.
 */
bool Dispatcher::acquireWork(WorkRequest *r)
{
	WorkReqInternal q(*r);

	// Keep trying as long as workers don't have to stop.
	while (!MustWorkersStop()) {
		q.clear();

		// For a work item a worker needs (a) a parent task and
		// (b) a slot to put a new child.

		// 1. Try to acquire an available task in any pool.
		if (!acquireParent(&q))
			// If unsuccessful, loop again.
			continue;

		// If the parent is in the last pool any children
		// will be processed and deleted immediately.
		// Return true without looking for an empt slot.
		if (q.parentPoolIndex + 1 == (int)pools->getSize())
			return true;

		// If the parent is not going to create a child on the next step,
		// return true, without looking for an empty slot.
		if (!q.parent->evolveWillCreateAChild())
			return true;

		// 2. Try to acquire an available empty slot.
		// It has to be in the pool following the parent's one.
		if (acquireChildSlot(&q))
			// If successful, return true.
			return true;

		// If unsuccessful, release parent's destination slot
		// before trying again from the beginning of the loop.
		pools->unlock(q.parentPoolIndex, q.parentSlotIndex);
	}

	return false;
}

/*
 * Stores the new child in the reserved slot as well as updates the parent
 * in the old parent's slot. Releases both locks. Must be called after
 * a successful call to acquireWork with the indices fields unchanged.
 */
void Dispatcher::releaseWork(WorkRequest *r)
{
	WorkReqInternal q(*r);

	if (q.hasChildSlot()) {
		pools->setTask(q.childPoolIndex, q.childSlotIndex, q.child);
		pools->unlock(q.childPoolIndex, q.childSlotIndex);
	}

	if (q.hasParentSlot()) {
		if(q.parent == nullptr)
			pools->setTask(q.parentPoolIndex, q.parentSlotIndex, q.parent);
		pools->unlock(q.parentPoolIndex, q.parentSlotIndex);
	}
}
