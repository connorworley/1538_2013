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
	m_State(FIRING),
	m_FiredDisks(0)
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
			if(GetLimitSwitch() && m_MotorA->Get() != 0)
			{
				//cout << "SWITCHING TO FIRING" << endl;
				m_State = FIRING;
				m_MotorA->Set(0);
				m_MotorB->Set(0);
			} 
			else
			{
//				if(m_TriggerTimeout == 0)
//				{
//					m_MotorA->Set(m_RawValue);
//					m_MotorB->Set(m_RawValue);	
//				} 
//				else
//				{
				SetDebounceTime(m_DebounceTimeIn);
				m_MotorA->Set(m_RawValue * 0.2);
				m_MotorB->Set(m_RawValue * 0.2);
//				}
			}
			
			//cout << "STAGING" << endl;
			break;
		case FIRING:
			if(CowRobot::GetInstance()->GetShooter()->GetRaw() != 0)
			{
				if(!GetLimitSwitch())
				{
//					//cout << "SWITCHING TO FIRED" << endl;
					m_State = FIRED;
					m_MotorA->Set(0);
					m_MotorB->Set(0);
				} 
				else if(Timer::GetFPGATimestamp() - m_TriggerTime > m_TriggerTimeout)
				{
					SetDebounceTime(m_DebounceTimeOut);
					m_MotorA->Set(m_RawValue);
					m_MotorB->Set(m_RawValue);
				}
			}
			//cout << "FIRING" << endl;
			break;
		case FIRED:
			m_DebounceTimer = 0;
			m_TriggerTime = Timer::GetFPGATimestamp();
			// Do any special shot counting code
			m_State = STAGING;
			m_FiredDisks++;
			cout << "DISCS FIRED: " << m_FiredDisks << endl;
			//cout << "FIRED" << endl;
			break;
		}
	} 
	else
	{
		m_MotorA->Set(m_RawValue);
		m_MotorB->Set(m_RawValue);
	}
	
}

void Roller::CreateLimitSwitch(int port, float waittime, float debouncetimein, float debouncetimeout)
{
	m_LimitSwitch = new DigitalInput(port);
	
	m_WaitOnTrigger = true;
	
	if(GetLimitSwitch())
	{
		m_State = FIRING;
	} else
	{
		m_State = STAGING;
	}
	
	SetTimeWaitTrigger(waittime);
	SetDebounceTime(debouncetimein);
	m_DebounceTimeIn = debouncetimein;
	m_DebounceTimeOut = debouncetimeout;
}

bool Roller::GetLimitSwitch()
{
	if(m_LimitSwitch)
	{
		//printf("%d\n", m_LimitSwitch->Get());
		// IF THE SWITCH IS OFF
		if(m_LimitSwitch->Get())
		{
			// BUT WAS ON
			if((Timer::GetFPGATimestamp() - m_DebounceTimer) <= m_DebounceTime)
				return true;
			// OTHERWISE
			return false;
		}
		else
		{
			m_DebounceTimer = Timer::GetFPGATimestamp();
			return true;
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

float Roller::GetRaw()
{
	return m_RawValue;
}

Roller::~Roller()
{
	delete m_MotorA;
	delete m_MotorB;
	if(m_LimitSwitch)
		delete m_LimitSwitch;
}
