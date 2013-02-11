#ifndef __Roller_H__
#define __Roller_H__

#include "WPILib.h"

class Roller
{
	private:
		Victor* motorA;
		Victor* motorB;
		float rawValue;
	
	public:
		Roller(int motorApwm, int motorBpwm);
		void Handle();
		void SetRaw(float value);
		
		~Roller();
};
#endif
