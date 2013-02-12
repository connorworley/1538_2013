#ifndef DRIVE_H_
#define DRIVE_H_

#include "../CowRobot.h"

class Drive : public PeriodicSystem
{
private:
	Talon* m_Left;
	Talon* m_Right;
public:
	Drive();
	
	void HandleOperatorInput(ControlBoard* cb, RobotState* robotState);
	void Handle(RobotState* desiredRobotState);
};

#endif
