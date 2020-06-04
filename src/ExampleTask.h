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

#ifndef EXAMPLETASK_H_
#define EXAMPLETASK_H_

#include <string>
#include "ITask.h"
#include "ProtectedCounter.h"

class ExampleTask: public ITask {
public:
	virtual ~ExampleTask();

	// The interface methods, implemented:
	virtual ITask* evolveState();
	virtual bool evolveWillCreateAChild() const;
	virtual bool isDone() const;

	/**
	 * This is a static method used for initialization of the PoolsArray.
	 *
	 * @return - a vector reference with the pools' sizes
	 * 			 and implicit number of pools.
	 */
	static const vector<size_t> &GetPoolsSizes();

	static const int FINAL_TASK_COUNT();
	//Facade methods for the ProtectedCounters
	static const int GetTasksCreated();
	static const int GetTasksDone();
	static const int GetTasksSaved();
protected:
	enum state_enum	{ NO_STATE, INITIAL, CHILDREN, MUST_SAVE, DONE };

	// Some constants determining this example workflow:
	static const vector<size_t> CHILDREN_PER_GENERATION;
	static const size_t NUM_GENERATIONS; // Must include the InitialTask, gen. 0
	static const vector<size_t> POOLS_SIZES;
	// Shared counters
	static ProtectedCounter tasksCreated;
	static ProtectedCounter tasksDone;
	static ProtectedCounter tasksSaved;

	// Hide the constructors. Only the InitialExampleTask has a public factory.
	static ExampleTask* newFromParent(ExampleTask &parent);
	ExampleTask() = default;
	ExampleTask(const ExampleTask& task) = default;

	// Methods, new for this class
	virtual size_t getMaxChildren() const; // A convenience method
	virtual ITask* newChild(); // A convenience method
	virtual void save(); // A convenience method
	static void ProtectedPrint(const ExampleTask* const task); // A convenience method

	string alphabet = "";        // Distinguishes different "types" of tasks.
	string data = "";            // The "payload".
	size_t generation = 0;       // The generation/pool of this task.
	state_enum state = NO_STATE; // state of the "state machine"
	int state_childrenLeft = 0;  // Number of children left (part of the state)
};

#endif /* EXAMPLETASK_H_ */
