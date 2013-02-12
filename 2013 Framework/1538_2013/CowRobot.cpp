#include "CowRobot.h"

CowRobot* CowRobot::m_SingletonInstance = NULL;

CowRobot* CowRobot::GetInstance()
{
	if(m_SingletonInstance == NULL)
	{
		m_SingletonInstance = new CowRobot();
	}
	return m_SingletonInstance;
}

CowRobot::CowRobot()
{
	m_ControlBoard = new ControlBoard();
}

void CowRobot::TeleopPeriodic()
{
	// Allow systems to change desired robot state
	for(m_CurrentPeriodicTask = m_PeriodicTaskPool.begin();
		m_CurrentPeriodicTask != m_PeriodicTaskPool.end();
		m_CurrentPeriodicTask++)
	{
		(*m_CurrentPeriodicTask)->HandleOperatorInput(m_ControlBoard, m_DesiredRobotState);
		(*m_CurrentPeriodicTask)->Handle(m_DesiredRobotState);
	}
}

void CowRobot::RegisterPeriodicSystem(void* systemPtr)
{
	// Warning: systemPtr is only the memory allocated for the system
	// It has not been constructed, so just add it to the pool and leave
	m_PeriodicTaskPool.push_back((PeriodicSystem*)systemPtr);
}

START_ROBOT_CLASS(CowRobot);
