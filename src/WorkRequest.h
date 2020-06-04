/*
 * WorkRequest is a structure used in the calls a Worker makes
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
	 * The dispatcher receives from the worker
	 * a pointer to a new child or
	 * nullptr if there is no child.
	 */
	ITask *child;

	/*
	 * The dispatcher assigns an existing task object to be worked on.
	 * The worker may change this to null if it deletes a completed
	 * task before releasing the slots..
	 */
	ITask *parent; //

	/*
	 * Read-only access to the private fields.
	 */
	int getChildPoolIndex();
	int getChildSlotIndex();
	int getParentPoolIndex();
	int getParentSlotIndex();
	bool hasChildSlot(); // True if both child indices are >= 0.
	bool hasParentSlot(); // True if both parent indices are >= 0.
private:
	/*
	 * The following fields are assigned by the dispatcher to be
	 * used by unlock().  They must not be changed by the worker.
	 */
	int childPoolIndex;
	int childSlotIndex;
	int parentPoolIndex;
	int parentSlotIndex;
};

/*
 * Has the same data members as WrokRequest but all are public.
 * For Dispatcher internal use.
 */
struct WorkReqInternal {
public:
	ITask *&child;
	ITask *&parent; //
	int &childPoolIndex;
	int &childSlotIndex;
	int &parentPoolIndex;
	int &parentSlotIndex;

	WorkReqInternal(WorkRequest &r);
	void clear(); // Sets pointers to nullptr and indices to -1.
	bool hasChildSlot(); // True if both child indices are >= 0.
	bool hasParentSlot(); // True if both parent indices are >= 0.
};

#endif /* WORKREQUEST_H_ */
