#include "Drive.h"

Drive::Drive()
{
	m_Left = new Talon(0); //TODO: GET REAL PORT NUMBER
	m_Right = new Talon(0);
}

void Drive::HandleOperatorInput(ControlBoard* cb, RobotState* robotState)
{
	// TODO: implememt ControlBoard and map inputs to robotState
}

void Drive::Handle(RobotState* desiredRobotState)
{
	m_Left->Set(desiredRobotState->driveLeft);
	m_Right->Set(desiredRobotState->driveRight);
}
