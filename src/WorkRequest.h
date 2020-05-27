/*
 * WorkRequest is a structure used in the calls a Wroker makes
 * to the dispatcher's acquireWork(...) and releaseWork(...).
 *
 * WorkReqInternal is for Dispatcher internal use.
 */
#ifndef WORKREQUEST_H_
#define WORKREQUEST_H_

#include "ITask.h"

struct WorkReqInternal;

/*
 * This structure is for dispatcher-worker communication.
 */
struct WorkRequest {
	friend struct WorkReqInternal;
public:
	/*
	 * The dispatcher receives from the worker a pointer to a new child
	 * or null if no more children.
	 */
	ITask *child; // A new child returned by the worker.

	/*
	 * The dispatcher assigns an existing task object to be worked on.
	 * The worker may change this to null if had deleted the task.
	 * It also has the option to replace it entirely.
	 */
	ITask *parent; //
private:
	/*
	 * The following fields are assigned by the dispatcher for
	 * use in unlock(). They must not be changed by the worker.
	 */
	size_t childPoolIndex;
	size_t childSlotIndex;
	size_t parentPoolIndex;
	size_t parentSlotIndex;
public:
	/*
	 * The following getters provide read-only access to the private fields.
	 */
	size_t getChildPoolIndex();
	size_t getChildSlotIndex();
	size_t getParentPoolIndex();
	size_t getParentSlotIndex();
};

/*
 * An access adapter for WrokRequest for use internally by Dispatcher.
 * The usage looks as if one has WrokRequest with all fields public.
 */
struct WorkReqInternal {
public:
	ITask *&child; // A new child returned by the worker.
	ITask *&parent; //
	size_t &childPoolIndex;
	size_t &childSlotIndex;
	size_t &parentPoolIndex;
	size_t &parentSlotIndex;

	WorkReqInternal(WorkRequest &r);
};


#endif /* WORKREQUEST_H_ */
