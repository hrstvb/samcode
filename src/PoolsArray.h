/*
 * The PoolArray is the storage for all tasks present in the workflow.
 * It comprises a fixed number of pools of fixed but possibly different sizes.
 * The pools are ordered by task generation.
 * The 0-th pool is of size one and is reserved for the initial task.
 *
 * The pool array provides access methods to all underlying slots and locks.
 *
 * The pool array is a singleton. The number of pools and each pool size
 * can be initialized once.
 */
#ifndef POOLSARRAY_H_
#define POOLSARRAY_H_

#include "Pool.h"

using namespace std;

class PoolsArray {
public:
	/*
	 * Returns the signleton PoolArray object.
	 */
	static PoolsArray& GetSingleton();

	/*
	 * Initializes the number of pools and individual sizes on the first call.
	 * Subsequent calls have no effect.
	 */
	void initOnce(const vector<const size_t> poolSizes);

	/*
	 * Returns the number of pools in the pool array.
	 */
	size_t getSize();

	/*
	 * Returns the size of the i-th pool.
	 */
	size_t getSize(size_t poolIndex);

	/*
	 * Returns a pointer to the task at the specified pool/slot.
	 * Can return null.
	 */
	ITask* getTask(size_t poolIndex, size_t slotIndex);

	/*
	 * Sets the pointer at the specified pool/slot.
	 * Can be null.
	 */
	void setTask(size_t poolIndex, size_t slotIndex, ITask* task);

	/*
	 * A non-blocking attempt to lock the specified slot only if empty.
	 * Returns true if successful.
	 * false otherwise, i.e. the slot is already locked or there is a task in it.
	 */
	bool tryLockIfEmpty(size_t poolIndex, size_t slotIndex);

	/*
	 * A non-blocking attempt lock the specified slot only if has a task.
	 * Returns true if successful.
	 * false otherwise, i.e. the slot is already locked or is empty.
	 */
	bool tryLockIfFull(size_t poolIndex, size_t slotIndex);

	/*
	 * Unlocks the specified slot.
	 */
	void unlock(size_t poolIndex, size_t slotIndex);

	virtual ~PoolsArray();

private:
	vector<Pool*> pools;
};

#endif /* POOLSARRAY_H_ */
