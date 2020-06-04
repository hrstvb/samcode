/**
 * Worker starts the main processing loop in a new thread.
 * The dispatcher may be shared with other workers.
 *
 * @param id - An arbitrary int to identify the Worker.
 *             This is not the system thread id.
 * @param dispatcher - A dispatcher object to feed work items
 * 			   to the Wroker or stop it.
 */

#ifndef WORKER_H_
#define WORKER_H_

#include <thread>
using namespace std;

#include "DispatcherBase.h"

class Worker {
public:
	Worker(int id, DispatcherBase *dispatcher);
	virtual ~Worker();

	/**
	 * @return The user-assigned worker's id.
	 *         Note: This is not the system id of the thread.
	 */
	int getWorkerId();

	/**
	 * Joins the worker's thread. Blocking.
	 */
	void join();

	/**
	 * Starts the main loop of the worker.
	 */
	void go();

private:
	DispatcherBase *dispatcher;
	int id;
	thread *thr = nullptr;
};

#endif /* WORKER_H_ */
