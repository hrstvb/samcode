#include <iostream>
#include <thread>
#include "Pool.h"

Pool::Pool(size_t poolSize) :
		mutexes(vector<mutex*>(poolSize, nullptr)), tasks(vector<ITask*>(poolSize, nullptr))
{
	for (size_t i = 0; i < mutexes.size(); i++)
		mutexes[i] = new mutex();
	cout << "Created a Pool of size " << poolSize << "(" << tasks.size() << ", " << mutexes.size() << ")." << endl;
}

Pool::~Pool()
{
	for (size_t i = 0; i < mutexes.size(); i++)
		delete mutexes[i];
}

size_t Pool::getSize()
{
	return tasks.size();
}

ITask* Pool::getTask(size_t i)
{
	return tasks[i];
}

void Pool::setTask(size_t i, ITask *task)
{
	tasks[i] = task;
}

bool Pool::tryLockIfEmpty(size_t i)
{
	mutex *m = mutexes[i];
	// See if the slot is empty after it is locked.
	if (m->try_lock()) {
		if (tasks[i] == nullptr)
			return true;
		// In not empty, unlock it.
		m->unlock();
	}

	return false;
}

bool Pool::tryLockIfFull(size_t i)
{
	mutex *m = mutexes[i];
	if (m->try_lock()) {
		// See if the slot is not empty after it is locked.
		if (tasks[i] != nullptr)
			return true;
		// In empty, unlock it.
		m->unlock();
	}
	return false;
}

void Pool::unlock(size_t i)
{
	mutexes[i]->unlock();
}
