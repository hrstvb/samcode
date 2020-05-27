#include <iostream>
#include "Worker.h"

Worker::Worker(int id, DispatcherBase *dispatcher) :
		id(id), dispatcher(dispatcher)
{
}

void Worker::go()
{
	WorkRequest r;

	// Log output
	cout << "Worker  " << id << " started.";

	// Request work from the dispatcher synchronously.
	// The worker thread runs until the dispatcher returns false.
	while (dispatcher->acquireWork(&r)) {
		// Note: Do not change the "Index" variables in the request.

		// Some more log output.
		cout << "Worker " << id << " acquired a task at (" << r.parentPoolIndex << "," << r.parentSlotIndex
				<< " and a child slot at (" << r.childPoolIndex << "," << r.childSlotIndex << ")" << endl;

		ITask *p = r.parent;
		ITask *c = nullptr;

		// Create a child task if any are left.
		if (p->getChildrenLeft() > 0)
			c = p->newChild();

		if(c != nullptr){
			c->evolveState();

			//If the child shall have no children tasks, save() and delete it.
			if (c->getChildrenLeft() == 0)
			{
				c->save();
				delete c;
				c = nullptr;
			}
		}

		// If a child was created above the number children left to create has decreased.
		// So check again. If there is no children left to create, delete the parent.
		if (p->getChildrenLeft() == 0) {
			delete p;
			p = nullptr;
		}

		// Update the parent and child tasks in the request.
		r.child = c;
		r.parent = p;

		//Let the dispatcher update the PoolArray and release the slots.
		dispatcher->releaseWork(&r);

		// More log output
		cout << "Worker " << id << " released slots (" << r.parentPoolIndex << "," << r.parentSlotIndex << " and ("
				<< r.childPoolIndex << "," << r.childSlotIndex << ")" << endl;
	}

	// More log output.
	cout << "Worker  " << id << " stopping...";
}
