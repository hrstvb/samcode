#include <iostream>
#include <array>
#include <thread>
#include <vector>
using namespace std;

#include "Dispatcher.h"
#include "Task.h"
#include "Worker.h"

void f(int i, DispatcherBase *d)
{
	Worker worker = new Worker(i, d);
	worker.go();
	delete worker;
}

int main()
{
	PoolsArray pools = PoolsArray::GetSingleton();
	pools.initOnce(Task::GetPoolsSizes());
	pools.setTask(0, 0, InitialTask.NewInitial());
	Dispatcher dispatcher = Dispatcher(&pools);

	const size_t NUM_THREADS = 5;
	array<thread, NUM_THREADS> threads;
	for (int i = 0; i <= threads.size(); i++)
		threads[i] = new thread(f, i, dispatcher);

	for (int i = 0; i <= threads.size(); i++)
		threads[i].join();

	return 0;
}
