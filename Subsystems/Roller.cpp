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
	m_State(FIRING)
{
	m_MotorA = new Talon(motorApwm);
	m_MotorB = new Talon(motorBpwm);
}

void Roller::Handle()
{
	if(m_LimitSwitch)
	{
		switch(m_State)
		{
		case STAGING:
			if(GetLimitSwitch())
			{
				m_State = FIRING;
				m_MotorA->Set(0);
				m_MotorB->Set(0);
			} 
			else
			{
				m_MotorA->Set(m_RawValue * 0.3);
				m_MotorB->Set(m_RawValue * 0.3);
			}
			break;
		case FIRING:
			if(!GetLimitSwitch())
			{
				m_State = FIRED;
				m_MotorA->Set(0);
				m_MotorB->Set(0);
				m_TriggerTime = Timer::GetFPGATimestamp();
			} 
			else if(Timer::GetFPGATimestamp() - m_TriggerTime > m_TriggerTimeout)
			{
				m_MotorA->Set(m_RawValue);
				m_MotorB->Set(m_RawValue);
			}
			break;
		case FIRED:
			// Do any special shot counting code
			m_State = STAGING;
			break;
		}
	} 
	else
	{
		m_MotorA->Set(m_RawValue);
		m_MotorB->Set(m_RawValue);
	}
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
			SetDebounceTime(Timer::GetFPGATimestamp());
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
