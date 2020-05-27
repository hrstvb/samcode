/*
 * The DispatcherBase provides a facade of the pools array
 * for use by workers. It also implements a 'stop' flag.
 *
 * When a request for work is made, the dispatcher finds
 * an available task, an available empty slot in the
 * next pool and locks them.
 *
 * The worker passes back a new child if any and null
 * if the parent has been deleted. Then the dispatcher
 * updates the pools and releases the locks.
 */

#ifndef DISPATCHERBASE_H_
#define DISPATCHERBASE_H_

#include "PoolsArray.h"
#include "WorkRequest.h"

class DispatcherBase {
public:
	/*
	 * Returns true if StopWrokers() had been called.
	 */
	static bool MustWorkersStop();

	/*
	 * A call to this method will make MustWorkersStop() return true.
	 */
	static void StopWorkers();

	DispatcherBase(PoolsArray *poolsArray);
	virtual ~DispatcherBase();

	/*
	 * For communication with worker(s).
	 * Locks a task object and an empty slot for a new child task.
	 * Should return true for real work items and
	 * false when workers need to quit.
	 */
	virtual bool acquireWork(WorkRequest *r) = 0;

	/*
	 * For communication with worker(s).
	 * Stores the new child task in the reserved slot.
	 * Updates the parent slot with null if necessary.
	 * Releases the locks of both slots.
	 */
	virtual void releaseWork(WorkRequest *r) = 0;

protected:
	PoolsArray *pools;

private:
	/*
	 * Initialized with false.
	 * Call StopWrokers to set to true.
	 */
	static bool MustStop;
};

#endif /* DISPATCHERBASE_H_ */
