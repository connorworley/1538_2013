#include "Robot.h"

Robot* Robot::m_SingletonInstance = NULL;

Robot* Robot::GetInstance()
{
	if(m_SingletonInstance == NULL)
	{
		m_SingletonInstance = new Robot();
	}
	return m_SingletonInstance;
}

Robot::Robot()
{
	
}

Robot::~Robot()
{
}

void Robot::RegisterPeriodicSystem(void* systemPtr)
{
	// Warning: systemPtr is only the memory allocated for the system
	// It has not been constructed, so just add it to the pool and leave
	m_PeriodicTaskPool.push_back((PeriodicSystem*)systemPtr);
}
