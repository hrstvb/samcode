/**
 * Task.h
 *
 *   An example implementation of ITask.
 *
 *   Each task has a state inherited its parent.
 *   The state should be evolved upon creation by a Worker.
 *   The task further creates children tasks an passes to them
 *   its state, evolved for each child accordingly.
 *   If the task is last generation, it prints its state.
 */

#ifndef TASK_H_
#define TASK_H_

#include <string>
#include "ITask.h"

class Task: public ITask {
public:
	// The interface methods, implemented:
	virtual size_t getChildrenLeft() const;
	virtual ITask* newChild();
	void evolveState();
	virtual void save();

	// Methods, new for this class
	/**
	 * This is a static method used for initialization of the PoolsArray.
	 *
	 * @return - a vector reference with the pools' sizes
	 * and implicit number of pools.
	 */
	static const vector<const size_t>& GetPoolsSizes();

protected:
	// Hide the constructors in favor of factory methods.
	Task();
	Task(const Task& task) = default; // A copy constructor for prototype creation.

	// Some constants determining this example workflow:
	static const size_t NUM_GENERATIONS = 4; // Includes the initial tasks, gen. 0
	static const vector<const size_t> POOLS_SIZES;
	static const vector<const size_t> CHILDREN_PER_GENERATION;

	string alphabet;   // Distinguishes different "types" of tasks.
	int childrenLeft;  // Number of children left.
	size_t generation; // The generation/pool of this task.
	string state;      // The "payload".
};

#endif /* TASK_H_ */
