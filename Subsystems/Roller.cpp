#include "Roller.h"
#include "../Declarations.h"
#include "../CowLib.h"

using namespace CowLib;

Roller::Roller(int motorApwm, int motorBpwm) :
	m_RawValue(0),
	m_LimitSwitch(NULL),
	m_WaitOnTrigger(false),
	m_TriggerTimeout(0),
	m_TriggerTime(0),
	m_DebounceTime(0),
	m_PreviousState(false),
	m_Fired(false),
	m_State(STAGED)
{
	m_MotorA = new Talon(motorApwm);
	m_MotorB = new Talon(motorBpwm);
}

void Roller::Handle()
{
//	switch(m_State)
//	{
//	case STAGING:
//		if(GetLimitSwitch())
//		{
//			m_State = STAGED;
//			m_MotorA->Set(0);
//			m_MotorB->Set(0);
//		} else
//		{
//			m_MotorA->Set(m_RawValue * 0.3);
//			m_MotorB->Set(m_RawValue * 0.3);
//		}
//		break;
//	case STAGED:
//		if(!GetLimitSwitch())
//		{
//			m_State = COOLDOWN;
//			m_MotorA->Set(0);
//			m_MotorB->Set(0);
//			m_TriggerTime = Timer::GetFPGATimestamp();
//		} else
//		{
//			m_MotorA->Set(m_RawValue);
//			m_MotorB->Set(m_RawValue);
//		}
//		break;
//	case COOLDOWN:
//		if(Timer::GetFPGATimestamp() - m_TriggerTime > m_TriggerTimeout)
//		{
//			m_State = STAGING;
//		}
//		else
//		{
//			m_MotorA->Set(0);
//			m_MotorB->Set(0);
//			cout << "Waiting to fire" << endl;
//		}
//		break;
		
	}
	if(m_WaitOnTrigger)
	{
		if(m_Fired)
		{
			if(Timer::GetFPGATimestamp() - m_TriggerTime > m_TriggerTimeout)
			{
				m_Fired = false;
			}
			else
			{
				m_MotorA->Set(0);
				m_MotorB->Set(0);
				cout << "Waiting to fire" << endl;
			}
		}
		else
		{
			cout << "Firing" << endl;
			m_MotorA->Set(m_RawValue);
			m_MotorB->Set(m_RawValue);
			
			if(!GetLimitSwitch() && m_PreviousState == true)
			{
				m_Fired = true;
				m_TriggerTime = Timer::GetFPGATimestamp();
				cout << "fired" << endl;
			}
		}
	}
	else
	{
		m_MotorA->Set(m_RawValue);
		m_MotorB->Set(m_RawValue);
	}
	
	if(m_LimitSwitch)
		m_PreviousState = m_LimitSwitch->Get();
}

void Roller::CreateLimitSwitch(int port, float waittime, float debouncetime)
{
	m_LimitSwitch = new DigitalInput(port);
	
	m_WaitOnTrigger = true;
	
	SetTimeWaitTrigger(waittime);
	SetDebounceTime(debouncetime);
}

bool Roller::GetLimitSwitch()
{
	if(m_LimitSwitch)
	{
		if(m_LimitSwitch->Get())
		{
			if((Timer::GetFPGATimestamp() - m_DebounceTimer) <= m_DebounceTime)
				return false;
			return true;
		}
		else
		{
			m_DebounceTimer = Timer::GetFPGATimestamp();
			return false;
		}
	}
	else
	{
		return false;
	}
}

void Roller::SetRaw(float value)
{
	this->m_RawValue = value;
}

Roller::~Roller()
{
	delete m_MotorA;
	delete m_MotorB;
	if(m_LimitSwitch)
		delete m_LimitSwitch;
}
