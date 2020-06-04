#include "ExampleTask.h"

#include <iostream>

// Includes a pool of 1 for the initial task, generation 0.
// There is no pool for generation 4, which we process and delete immediately.
// It is also implied that gen. 4 has no children.
const size_t ExampleTask::NUM_GENERATIONS = 2;
const vector<size_t> ExampleTask::POOLS_SIZES = { 1, 2, 4, 4 }; // The first element must be one.
const vector<size_t> ExampleTask::CHILDREN_PER_GENERATION = { 2, 5, 5, 2 }; // The last zero saves a line of code.
ProtectedCounter ExampleTask::tasksCreated;
ProtectedCounter ExampleTask::tasksDone;
ProtectedCounter ExampleTask::tasksSaved;

ExampleTask::~ExampleTask()
{
	ExampleTask::tasksDone.inc();
}

ITask* ExampleTask::evolveState()
{
	ITask *child = nullptr;
	state_enum nextState = NO_STATE;
	switch (state) {
	case INITIAL:
		data += "-";
		nextState = (state_childrenLeft) ? CHILDREN : MUST_SAVE;
		break;
	case CHILDREN:
		data += alphabet[state_childrenLeft];
		child = newChild();
		nextState = (state_childrenLeft) ? CHILDREN : DONE;
		break;
	case MUST_SAVE:
		save();
		nextState = DONE;
		break;
	default:
		;
	}
	state = nextState;
	return child;
}

bool ExampleTask::evolveWillCreateAChild() const
{
	return state == CHILDREN;
}

const int ExampleTask::FINAL_TASK_COUNT()
{
	size_t sumprod = 1;
	size_t prod = 1;
	for (size_t i = 0; i < CHILDREN_PER_GENERATION.size(); i++) {
		prod *= CHILDREN_PER_GENERATION[i];
		sumprod += prod;
	}
	return sumprod;
}

size_t ExampleTask::getMaxChildren() const
{
	return ((0 <= generation) && (generation < CHILDREN_PER_GENERATION.size())) ?
			CHILDREN_PER_GENERATION[generation] : 0;
}

const int ExampleTask::GetTasksCreated()
{
	return ExampleTask::tasksCreated.get();
}

const vector<size_t>& ExampleTask::GetPoolsSizes()
{
	return POOLS_SIZES;
}

const int ExampleTask::GetTasksDone()
{
	return ExampleTask::tasksDone.get();
}

const int ExampleTask::GetTasksSaved()
{
	return ExampleTask::tasksSaved.get();
}

bool ExampleTask::isDone() const
{
	return state == DONE;
}

ITask* ExampleTask::newChild()
{
	ExampleTask *c = nullptr;
	if (state_childrenLeft > 0) {
		c = newFromParent(*this); // Use parent as a prototype.
		state_childrenLeft--; // Decrease parent's children count.
	}
	return c; // Return the new child.
}

ExampleTask* ExampleTask::newFromParent(ExampleTask &parent)
{
	ExampleTask *child = new ExampleTask(parent);
	child->generation++; // Adjust child's generation.
	child->state = INITIAL;
	child->state_childrenLeft = child->getMaxChildren(); // Set the number of children to create.
	ExampleTask::tasksCreated.inc();
	return child;
}

void ExampleTask::save()
{
	ExampleTask::ProtectedPrint(this);
	ExampleTask::tasksSaved.inc();
}

void ExampleTask::ProtectedPrint(const ExampleTask *const task)
{
	static mutex mtx;
	const lock_guard<mutex> TEMP_LOCK(mtx);
	cout << "Saving result: " << task->data << endl;
}
