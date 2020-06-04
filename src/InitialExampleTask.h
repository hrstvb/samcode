/*
 * InitialTask (generation 0) sits at the root of the task tree.
 * It serves as a factory for different "types" of tasks.
 */

#ifndef INITIALEXAMPLETASK_H_
#define INITIALEXAMPLETASK_H_

#include "ExampleTask.h"

class InitialExampleTask: public ExampleTask {
public:
	static InitialExampleTask* NewInitial();
	virtual ITask* newChild();
private:
	InitialExampleTask();
};

#endif /* INITIALEXAMPLETASK_H_ */
