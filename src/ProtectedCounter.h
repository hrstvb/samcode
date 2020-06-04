/**
 * A thread-safe counter.
 */
#ifndef PROTECTEDCOUNTER_H_
#define PROTECTEDCOUNTER_H_

#include <mutex>
using namespace std;

class ProtectedCounter {
public:
	ProtectedCounter() = default;
	int get();
	void inc();

private:
	mutex mtx;
	int n = 0;
};

#endif /* PROTECTEDCOUNTER_H_ */
