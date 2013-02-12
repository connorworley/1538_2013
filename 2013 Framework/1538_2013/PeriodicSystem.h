#ifndef PERIODICSYSTEM_H_
#define PERIODICSYSTEM_H_

#include "Utility/Types.h"
#include "ControlBoard.h"

class PeriodicSystem
{
public:
	// Overload the new operator to register PeriodicSystems with the pool
	void* operator new(size_t size);
	
	virtual void HandleOperatorInput(ControlBoard* cb, RobotState* robotState);
	virtual void Handle(RobotState* desiredRobotState);
};

#endif
