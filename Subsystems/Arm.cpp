#include "Arm.h"
#include "../Declarations.h"
#include "../CowLib.h"
#include "../CowConstants.h"

using namespace CowLib;

Arm::Arm(int motorApwm, int motorBpwm, int potPwm, int lockSolenoid) :
	PID_P(8),
	PID_D(1),
	m_PreviousError(0),
	m_RawValue(0),
	m_LockState(LOCKED)
{
	m_MotorA = new Talon(motorApwm);
	m_MotorB = new Talon(motorBpwm);
	m_Pot = new AnalogChannel(potPwm);
	m_Setpoint = CowConstants::getInstance()->getValueForKey("ArmStartingPosition");
	m_Lock = new Solenoid(lockSolenoid);
	m_LockTimer = 0;
}

void Arm::Handle()
{
	float error = m_Setpoint - m_Pot->GetVoltage();
	float errorChange = error - m_PreviousError;
	float output = (error * PID_P) + (errorChange * PID_D);
	if(output > 0.5 &&
		m_Setpoint >= CowConstants::getInstance()->getValueForKey("ArmGroundPosition"))
	{
		output = 0.5;
	}
	if(output > 0.8)
	{
		output = 0.8;
	}
//	if(output < -0.8)
//	{
//		output = -0.8;
//	}
	
	if(m_LockState == UNLOCKING  && (Timer::GetFPGATimestamp() - m_LockTimer) > 0.5)
	{
		m_LockState = UNLOCKED;
	}
	
	// 0.15 = -1.2%
	if(m_LockState == UNLOCKED)
	{
		if((m_Setpoint > CowConstants::getInstance()->getValueForKey("ArmGroundPosition") + 0.01 && output > 0)|| m_Pot->GetVoltage() < 1)
		{
			output = 0;
		
			m_MotorA->Set(m_RawValue);
			m_MotorB->Set(m_RawValue);
		} 
		else 
		{
			m_MotorA->Set(output);
			m_MotorB->Set(output);
		}
	}
	else
	{
		m_MotorA->Set(0);
		m_MotorB->Set(0);
	}
	printf("%f\t\t%f\t\t%f\n", m_Setpoint, m_Pot->GetVoltage(), output);
	m_PreviousError = error;
}

float Arm::GetSetpoint()
{
	return m_Setpoint;
}

void Arm::SetSetpoint(float value)
{
	m_Setpoint = value;
} 

void Arm::SetRaw(float value)
{
	m_RawValue = value;
}

void Arm::Lock(bool value)
{
	m_Lock->Set(value);
	//we're unlocking
	if(m_LockState == LOCKED && value == true)
	{
		m_LockState = UNLOCKING;
		m_LockTimer = Timer::GetFPGATimestamp();
	}	
}

Arm::~Arm()
{
	delete m_MotorA;
	delete m_MotorB;
}
