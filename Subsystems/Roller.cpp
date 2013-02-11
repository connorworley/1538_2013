#include "Roller.h"
#include "../Declarations.h"
#include "../CowLib.h"

using namespace CowLib;

Roller::Roller(int motorApwm, int motorBpwm)
{
	motorA = new Victor(motorApwm);
	motorB = new Victor(motorBpwm);
}

void Roller::Handle()
{
	motorA->Set(rawValue);
	motorB->Set(rawValue);
}

void Roller::SetRaw(float value)
{
	this->rawValue = value;
}

Roller::~Roller()
{
	delete motorA;
	delete motorB;
}
