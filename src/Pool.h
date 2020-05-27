/*
 * Pool is a collection of slots where tasks can stay while waiting to be completed.
 * Tasks of the same generation go in the same pool.
 * A pool has a fixed number of slots for tasks to occupy. Slots are indexed however
 * a pool doesn't imply an order unlike a stack or a queue for example.
 * It provides a mechanism for locking tasks or empty spots.
 * Pools live in a pool array and not by themselves.
 */
#ifndef POOL_H_
#define POOL_H_

#include <mutex>
#include <thread>
#include <vector>

using namespace std;

#include "ITask.h"

class Pool {
public:
	/*
	 * Creates a pool of a given size with all slots empty and unlocked.
	 */
	Pool(size_t poolSize);
	virtual ~Pool();

	/*
	 * A non-blocking attempt to lock the i-th slot only if empty.
	 * Returns true if successful.
	 * false otherwise, i.e. the slot is already locked or there is a task in it.
	 */
	bool tryLockIfEmpty(size_t i);

	/*
	 * A non-blocking attempt to lock the i-th slot only if has a task.
	 * Returns true if successful.
	 * false otherwise, i.e. the slot is already locked or is empty.
	 */
	bool tryLockIfFull(size_t i);

	/*
	 * Unlocks the i-th slot.
	 */
	void unlock(size_t i);

	/*
	 * Retruns the pool capacity.
	 */
	size_t getSize();

	/*
	 * Retruns a pointer to the task in the i-th slot
	 * or null if the slot is empty
	 */
	ITask* getTask(size_t i);

	/*
	 * Sets the pointer in the i-th slot ignoring the old value.
	 * Both the old and the new pointers can be either null or not.
	 */
	void setTask(size_t i, ITask* task);

private:
	vector<mutex> mutexes; // Slot locks.
	vector<ITask*> tasks;  // Pointers to tasks.
};

#endif /* POOL_H_ */
