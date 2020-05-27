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
	/*
	 * Returns the number of children left to create.
	 * Should decrease by one after each call to newChild().
	 */
	virtual size_t getChildrenLeft() const = 0;

	/*
	 * A factory method for creating children tasks.
	 */
	virtual ITask* newChild() = 0; // Factory method

	/*
	 * This is the essential computation.
	 */
	virtual void evolveState() = 0;

	/*
	 * save() the essential result.
	 */
	virtual void save() = 0;

	virtual ~ITask() = 0;
protected:
	ITask(); // Use public factory methods.
};

#endif /* ITASK_H_ */
