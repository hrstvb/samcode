#include <iostream>
#include "PoolsArray.h"

PoolsArray& PoolsArray::GetSingleton()
{
	static PoolsArray singleton;
	return singleton;
}

PoolsArray::PoolsArray() :
		pools(vector<Pool*>(0))
{
}

PoolsArray::~PoolsArray()
{
	for (size_t i = 0; i < pools.size(); i++)
		delete pools[i];
}

size_t PoolsArray::getSize()
{
	return pools.size();
}

size_t PoolsArray::getSize(size_t poolIndex)
{
	return pools[poolIndex]->getSize();
}

ITask* PoolsArray::getTask(size_t poolIndex, size_t slotIndex)
{
	return pools[poolIndex]->getTask(slotIndex);
}

void PoolsArray::setTask(size_t poolIndex, size_t slotIndex, ITask *task)
{
	pools[poolIndex]->setTask(slotIndex, task);
}

void PoolsArray::initOnce(const vector<size_t> &poolSizes)
{
	static bool initDone = false;
	if (initDone)
		return;

	size_t n = poolSizes.size();
	pools.resize(n);
	cout << "PoolArray extended to " << n << " pools." << endl;
	for (size_t i = 0; i < n; i++) {
		pools[i] = new Pool(poolSizes[i]);
	}
	initDone = true;
}

bool PoolsArray::tryLockIfEmpty(size_t poolIndex, size_t slotIndex)
{
	return pools[poolIndex]->tryLockIfEmpty(slotIndex);
}

bool PoolsArray::tryLockIfFull(size_t poolIndex, size_t slotIndex)
{
	return pools[poolIndex]->tryLockIfFull(slotIndex);
}

void PoolsArray::unlock(size_t poolIndex, size_t slotIndex)
{
	return pools[poolIndex]->unlock(slotIndex);
}
