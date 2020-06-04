#include "ProtectedCounter.h"

int ProtectedCounter::get()
{
	const lock_guard<mutex> TEMP_LOCK(mtx);
	return n;
}

void ProtectedCounter::inc()
{
	const lock_guard<mutex> TEMP_LOCK(mtx);
	n++;
}

