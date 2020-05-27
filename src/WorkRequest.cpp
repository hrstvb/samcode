#include "WorkRequest.h"

size_t WorkRequest::getChildPoolIndex() { return childPoolIndex; }
size_t WorkRequest::getChildSlotIndex() { return childSlotIndex; }
size_t WorkRequest::getParentPoolIndex() { return parentPoolIndex; }
size_t WorkRequest::getParentSlotIndex() { return parentSlotIndex; }

WorkReqInternal::WorkReqInternal(WorkRequest &r):
	child(r.child), parent(r.parent),
	childPoolIndex(r.childPoolIndex), childSlotIndex(r.childSlotIndex),
	parentPoolIndex(r.parentPoolIndex), parentSlotIndex(r.parentSlotIndex)
{
}
