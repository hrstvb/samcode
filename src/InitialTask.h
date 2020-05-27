/*
 * InitialTask (generation 0) sits at the root of the task tree.
 * It serves as a factory for different "types" of tasks.
 */

#ifndef INITIALTASK_H_
#define INITIALTASK_H_

#include "Task.h"

class InitialTask: public Task {
	static InitialTask* NewInitial();
	virtual ITask* newChild();
protected:
	InitialTask();
};

#endif /* INITIALTASK_H_ */
