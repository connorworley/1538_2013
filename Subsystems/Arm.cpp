#include "Arm.h"
#include "../Declarations.h"
#include "../CowLib.h"

using namespace CowLib;

Arm::Arm(int motorApwm, int motorBpwm)
{
	motorA = new Victor(motorApwm);
	motorB = new Victor(motorBpwm);
}

void Arm::Handle()
{
	motorA->Set(rawValue);
	motorB->Set(rawValue);
}

void Arm::SetRaw(float value)
{
	//if(value < 0)
	//	value = 0;
	this->rawValue = value;
}

Arm::~Arm()
{
	delete motorA;
	delete motorB;
}
