#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include <vector>
using namespace std;

#include "Dispatcher.h"
#include "ExampleTask.h"
#include "Worker.h"
#include "InitialExampleTask.h"

int main()
{
	cout << ExampleTask::FINAL_TASK_COUNT() << " tasks expected." << endl;

	// Initialize the PoolArray singleton with the
	// pools sizes given by the ExampleTask object.
	// Put an InitialTask in the first pool.
	PoolsArray pools = PoolsArray::GetSingleton();
	pools.initOnce(ExampleTask::GetPoolsSizes());
	pools.setTask(0, 0, InitialExampleTask::NewInitial());

	// Create a Dispatcher associated with the PoolArray.
	Dispatcher dispatcher = Dispatcher(&pools);

	// Create a few Workers using dispatcher.
	const size_t NUM_THREADS = 5;
	cout << "Starting " << NUM_THREADS << " workers/threads." << endl;
	array<Worker*, NUM_THREADS> workers;
	for (size_t i = 0; i < workers.size(); i++)
		workers[i] = new Worker(i, &dispatcher);

	while (ExampleTask::GetTasksDone() < ExampleTask::FINAL_TASK_COUNT()) {
		this_thread::sleep_for(chrono::milliseconds(100));
		cout << "... done " << ExampleTask::GetTasksDone() << " of " << ExampleTask::FINAL_TASK_COUNT() << endl;
	}

	// Stop and delete workers.
	dispatcher.StopWorkers();
	for (size_t i = 0; i < workers.size(); i++) {
		workers[i]->join();
		delete workers[i];
		workers[i] = nullptr;
	}

	//Print a summary
	cout << "SUMMARY:" << endl;

	cout << ExampleTask::GetTasksSaved() << " tasks \"saved\"." << endl;

	cout << ExampleTask::GetTasksCreated() << " / " << ExampleTask::GetTasksDone() << " / "
			<< ExampleTask::FINAL_TASK_COUNT() << " tasks created/completed/expected." << endl;

	cout << "Done." << endl;
	return 0;
}
