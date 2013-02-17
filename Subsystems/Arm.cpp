#include "Arm.h"
#include "../Declarations.h"
#include "../CowLib.h"

using namespace CowLib;

Arm::Arm(int motorApwm, int motorBpwm, int potPwm, int lockSolenoid) :
	PID_P(8),
	PID_D(1),
	m_PreviousError(0),
	m_RawValue(0)
{
	m_MotorA = new Talon(motorApwm);
	m_MotorB = new Talon(motorBpwm);
	m_Pot = new AnalogChannel(potPwm);
	m_Setpoint = ARM_SETPOINT_GROUND;
	m_Lock = new Solenoid(lockSolenoid);
}

void Arm::Handle()
{
	float error = m_Setpoint - m_Pot->GetVoltage();
	float errorChange = error - m_PreviousError;
	float output = (error * PID_P) + (errorChange * PID_D);
	if(output > 0.5)
	{
		output = 0.5;
	}
	if(output < -0.8)
	{
		output = -0.8;
	}
	// 0.15 = -1.2%
	if((m_Setpoint > ARM_SETPOINT_GROUND + 0.01 && output > 0)|| m_Pot->GetVoltage() < 1 || !m_Lock->Get())
	{
		output = 0;
		m_MotorA->Set(m_RawValue);
		m_MotorB->Set(m_RawValue);
	} else {
		m_MotorA->Set(output);
		m_MotorB->Set(output);
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
}

Arm::~Arm()
{
	delete m_MotorA;
	delete m_MotorB;
}
