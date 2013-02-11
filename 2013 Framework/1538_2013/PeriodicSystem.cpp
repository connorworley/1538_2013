#include "Robot.h"

void* PeriodicSystem::operator new(size_t size)
{
	void* mem = malloc(size);
	Robot::GetInstance()->RegisterPeriodicSystem(mem);
	return mem;
}
