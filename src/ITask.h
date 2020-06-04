/*
 * ITask.h
 *
 *  Interface shared by all tasks.
 */

#ifndef ITASK_H_
#define ITASK_H_

#include <vector>
using namespace std;

class ITask {
public:
	/**
	 * This is the essential computation.
	 * @return A pointer to a new child or null.
	 */
	virtual ITask* evolveState() = 0;

	/**
	 * @return true if the next call to evolveState will return a child.
	 *         This is used by the dispatcher when acquiring a work item.
	 */
	virtual bool evolveWillCreateAChild() const = 0;

	/**
	 * true if the Task is completed and should be deleted.
	 */
	virtual bool isDone() const = 0;

	virtual ~ITask() = default;
protected:
	ITask() = default; // Use public factory methods.
};

#endif /* ITASK_H_ */
