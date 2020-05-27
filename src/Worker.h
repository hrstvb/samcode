/*
 * A worker should be instantiated with an ID and a dispatcher.
 * The dispatcher may or may not be shared with other workers.
 */

#ifndef WORKER_H_
#define WORKER_H_

#include "DispatcherBase.h"

class Worker {
public:
	Worker(int id, DispatcherBase *dispatcher);

	/*
	 * Starts the main loop of the worker - processing work items
	 * received by the dispatcher.
	 */
	void go();

private:
	int id;
	DispatcherBase *dispatcher;
};

#endif /* WORKER_H_ */
