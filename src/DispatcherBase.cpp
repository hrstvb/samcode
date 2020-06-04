#include "DispatcherBase.h"

bool DispatcherBase::MustStop = false;

DispatcherBase::DispatcherBase(PoolsArray *poolsArray) :
		pools(poolsArray)
{
}

bool DispatcherBase::MustWorkersStop()
{
	return MustStop;
}

void DispatcherBase::StopWorkers()
{
	MustStop = true;
}
