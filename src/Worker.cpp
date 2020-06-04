#include <iostream>
#include "Worker.h"

Worker::Worker(int id, DispatcherBase *dispatcher) :
		dispatcher(dispatcher), id(id)
{
	thr = new thread(&Worker::go, this);
}

Worker::~Worker()
{
	delete thr;
}

/**
 * @return The user-assigned worker's id.
 */
int Worker::getWorkerId()
{
	return id;
}

void Worker::join()
{
	if (thr != nullptr)
		thr->join();
}

void Worker::go()
{
	// Log output
	cout << "Worker  " << id << " started." << endl;

	WorkRequest r;

	// Request work from the dispatcher synchronously.
	// The worker thread runs until the dispatcher returns false.
	while (dispatcher->acquireWork(&r)) {
		ITask *p = r.parent;
		ITask *c = nullptr;

		// Create a child task if any are left.
		// (Shortcutting matters here.)
		if ((p) && (!p->isDone()) && (c = p->evolveState()) && (!r.hasChildSlot())) {
			// If no slot is reserved for th echild,
			// evolve it until done and delete.
			while (!c->isDone())
				c->evolveState();

			delete c;
			c = nullptr;
		}

		// If a child was created above the number children left to create has decreased.
		// So check again. If there is no children left to create, delete the parent.
		// (Shortcutting matters here.)
		if ((p) && p->isDone()) {
			delete p;
			p = nullptr;
		}

		// Update the parent and child tasks in the request.
		r.child = c;
		r.parent = p;

		//Let the dispatcher update the PoolArray and release the slots.
		dispatcher->releaseWork(&r);
	}

	// More log output.
	cout << "Worker  " << id << " stopping..." << endl;
}
