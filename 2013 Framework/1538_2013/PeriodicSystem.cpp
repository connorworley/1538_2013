#include "CowRobot.h"

void* PeriodicSystem::operator new(size_t size)
{
	void* mem = malloc(size);
	CowRobot::GetInstance()->RegisterPeriodicSystem(mem);
	return mem;
}
