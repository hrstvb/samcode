/*
 * This implementation of DispatcherBase searches the pool array
 * sequentially starting from the latest generation of tasks.
 */

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include "DispatcherBase.h"
#include "WorkRequest.h"

class Dispatcher: public DispatcherBase {
public:
	Dispatcher(PoolsArray *poolsArray);
	// Abstract base methods, implemented:
	virtual bool acquireWork(WorkRequest *r);
	virtual void releaseWork(WorkRequest *r);
private:
	/*
	 * A convenience method. Tries to reserve an empty available slot
	 * and saves the indices in the work request.
	 * Returns true if successful.
	 */
	bool acquireChildSlot(WorkReqInternal *q);
	/*
	 * A convenience method. Tries to reserve an available task
	 * and saves a pointer to it and its indices in the work request.
	 * Return true if successful.
	 */
	bool acquireParent(WorkReqInternal *q);
};

#endif /* DISPATCHER_H_ */
