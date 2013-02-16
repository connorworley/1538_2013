#include "Arm.h"
#include "../Declarations.h"
#include "../CowLib.h"

using namespace CowLib;

Arm::Arm(int motorApwm, int motorBpwm, int potPwm) :
	PID_P(14),
	PID_D(0),
	m_PreviousError(0),
	m_RawValue(0)
{
	m_MotorA = new Talon(motorApwm);
	m_MotorB = new Talon(motorBpwm);
	m_Pot = new AnalogChannel(potPwm);
	m_Setpoint = m_Pot->GetVoltage();
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
	if(m_Setpoint > 3.441)
	{
		output = 0;
	}
	m_PreviousError = error;
	m_MotorA->Set(output);
	m_MotorB->Set(output);
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
	//if(value < 0)
	//	value = 0;
	this->m_RawValue = value;
}

Arm::~Arm()
{
	delete m_MotorA;
	delete m_MotorB;
}
