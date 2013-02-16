#include "Roller.h"
#include "../Declarations.h"
#include "../CowLib.h"

using namespace CowLib;

Roller::Roller(int motorApwm, int motorBpwm) :
	m_RawValue(0)
{
	m_MotorA = new Talon(motorApwm);
	m_MotorB = new Talon(motorBpwm);
}

void Roller::Handle()
{
	m_MotorA->Set(m_RawValue);
	m_MotorB->Set(m_RawValue);
}

void Roller::SetRaw(float value)
{
	this->m_RawValue = value;
}

Roller::~Roller()
{
	delete m_MotorA;
	delete m_MotorB;
}
