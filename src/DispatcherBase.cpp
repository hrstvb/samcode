/*
 * DispatcherBase.cpp
 *
 *  Created on: May 25, 2020
 *      Author: cdev
 */

#include "DispatcherBase.h"

bool DispatcherBase::MustStop = false;

DispatcherBase::DispatcherBase(PoolsArray *poolsArray) :
		pools(poolsArray)
{
}

void DispatcherBase::StopWorkers()
{
	MustStop = true;
}

bool DispatcherBase::MustWorkersStop()
{
	return MustStop;
}

DispatcherBase::~DispatcherBase()
{
}

