#include "InitialTask.h"

InitialTask* InitialTask::NewInitial()
{
	return new InitialTask();
}

InitialTask::InitialTask():
				alphabet(""), childrenLeft(2), generation(0), state(">")
{
}

ITask* InitialTask::newChild()
{
	// We set the alphabet since children are created
	// using the parent as a prototype.
	switch (childrenLeft) {
	case 2:
		alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		break;
	case 1:
		alphabet = "zyxwvutsrqponmlkjihgfedcba";
		break;
	default:
		return nullptr;
	}

	// The rest is takencare of the super-class method.
	return Task::newChild();
}

