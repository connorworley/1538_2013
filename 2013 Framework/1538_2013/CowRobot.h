#ifndef COWROBOT_H_
#define COWROBOT_H_

#include <WPILib.h>
#include <vector>

#include "Utility/Types.h"
#include "PeriodicSystem.h"
#include "ControlBoard.h"

class CowRobot : public IterativeRobot
{
private:
	std::vector<PeriodicSystem*> m_PeriodicTaskPool;
	std::vector<PeriodicSystem*>::iterator m_CurrentPeriodicTask;
	
	RobotState* m_DesiredRobotState;
	
	ControlBoard* m_ControlBoard;
	
public:
	static CowRobot* m_SingletonInstance;
	static CowRobot* GetInstance();
	
	CowRobot();
	
	void RegisterPeriodicSystem(void* systemPtr);
	
	void RobotInit();
	void DisabledInit();
	void AutonomousInit();
    void TeleopInit();
    void TestInit();

	void DisabledPeriodic();
	void AutonomousPeriodic();
    void TeleopPeriodic();
    void TestPeriodic();
};

#endif
