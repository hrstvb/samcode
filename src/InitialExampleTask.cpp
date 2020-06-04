#include "InitialExampleTask.h"

InitialExampleTask* InitialExampleTask::NewInitial()
{
	return new InitialExampleTask();
}

InitialExampleTask::InitialExampleTask()
{
	alphabet = "1234567890";
	data = ">";
	generation = 0;
	state = INITIAL;
	state_childrenLeft = getMaxChildren();
	ExampleTask::tasksCreated.inc();
}

ITask* InitialExampleTask::newChild()
{
	// We set the alphabet since children are created
	// using the parent as a prototype.
	switch (state_childrenLeft) {
	case 2:
		alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		break;
	case 1:
		alphabet = "zyxwvutsrqponmlkjihgfedcba";
		break;
	default:
		return nullptr;
	}

	// The rest is taken care by the base class method.
	return ExampleTask::newChild();
}

