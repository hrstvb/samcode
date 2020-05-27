#include "Dispatcher.h"

Dispatcher::Dispatcher(PoolsArray *poolsArray):DispatcherBase(poolsArray)
{
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
	q.child = nullptr;

	// Keep trying as long as workers don't have to stop.
	while (!MustWorkersStop()) {

		// For a work item a worker needs (a) a parent task and
		// (b) a slot to put a new child.

		// 1. Try to acquire an available empty spot in any pool.
		if (!acquireChildSlot(&q))
			// If unsuccessful, loop again.
			continue;

		// 2. Try to acquire an available task.
		//It has to be in the pool preceding the child destination.
		if (acquireParent(&q))
			// If successful, return true.
			return true;
		else
			// If unsuccessful, release child's destination slot
			// before trying again from the beginning of the loop.
			pools->unlock(q.childPoolIndex, q.childSlotIndex);
	};
	return false;
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
	for (int i = pools->getSize(); i >= 1; i--) {
		for (int j = pools->getSize(i); j >= 0; j--) {
			if (pools->tryLockIfEmpty(i, j)) {
				q->childPoolIndex = i;
				q->childSlotIndex = j;
				return true;
			}
		}
	}
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
	size_t i = q->parentPoolIndex = q->childPoolIndex - 1;
	for (int j = pools->getSize(i) - 1; j >= 0; j--) {
		if (pools->tryLockIfFull(i, j)) {
			q->parentSlotIndex = j;
			q->parent = pools->getTask(i, j);
			return true;
		}
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
	pools->setTask(q.childPoolIndex, q.childSlotIndex, q.child);
	pools->unlock(q.childPoolIndex, q.childSlotIndex);
	pools->setTask(q.parentPoolIndex, q.parentSlotIndex, q.parent);
	pools->unlock(q.parentPoolIndex, q.parentSlotIndex);
}
