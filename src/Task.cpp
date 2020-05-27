#include <iostream>
#include "Task.h"

// Includes a pool of 1 for the initial task, gen. 0 and its
// number of children, 2.
// Note that there is no pool for gen=4, which we `save` and delete immediately.
static const size_t Task::NUM_GENERATIONS = 4;
const vector<const size_t> Task::POOLS_SIZES = { 1, 2, 4, 4 }; // The first element must be one.
const vector<const size_t> Task::CHILDREN_PER_GENERATION = { 2, 5, 5, 2 };

Task::Task() :
		alphabet(""), childrenLeft(0), generation(0), state("")
{
	// Specific values are set by the InitialTask constructor or newChild.
}

size_t Task::getChildrenLeft() const
{
	return childrenLeft;
}

const vector<const size_t>& Task::GetPoolsSizes()
{
	return POOLS_SIZES;
}

ITask* Task::newChild()
{
	if (childrenLeft <= 0)
		return nullptr;

	Task *c = new Task(*this); // Copy parent to child.
	c->generation++; // Adjust child's generation.
	const size_t NG = CHILDREN_PER_GENERATION.size(); // A convenience variable.
	const size_t g = c->generation; // A convenience variable.
	c->childrenLeft = (g < NG) ? CHILDREN_PER_GENERATION[g] : 0; // Set the number of children to create.

	childrenLeft--; // Dec parent's children count.
	return c; // Return the new child.
}

void Task::evolveState()
{
	state += alphabet[childrenLeft];
}

void Task::save()
{
	cout << "Result: " << state << endl;
}

