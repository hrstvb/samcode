#include "WorkRequest.h"

int WorkRequest::getChildPoolIndex() { return childPoolIndex; }
int WorkRequest::getChildSlotIndex() { return childSlotIndex; }
int WorkRequest::getParentPoolIndex() { return parentPoolIndex; }
int WorkRequest::getParentSlotIndex() { return parentSlotIndex; }
bool WorkRequest::hasChildSlot() { return (childPoolIndex >= 0) && (childSlotIndex >= 0); }
bool WorkRequest::hasParentSlot() { return (parentPoolIndex >= 0) && (parentSlotIndex >= 0); }

WorkReqInternal::WorkReqInternal(WorkRequest &r):
	child(r.child), parent(r.parent),
	childPoolIndex(r.childPoolIndex), childSlotIndex(r.childSlotIndex),
	parentPoolIndex(r.parentPoolIndex), parentSlotIndex(r.parentSlotIndex)
{
}

void WorkReqInternal::clear()
{
	child = parent = nullptr;
	childPoolIndex = childSlotIndex = parentPoolIndex = parentSlotIndex = -1;
}

bool WorkReqInternal::hasChildSlot() { return (childPoolIndex >= 0) && (childSlotIndex >= 0); }
bool WorkReqInternal::hasParentSlot() {	return (parentPoolIndex >= 0) && (parentSlotIndex >= 0); }
