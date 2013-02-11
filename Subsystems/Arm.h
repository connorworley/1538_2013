#ifndef __ARM_H__
#define __ARM_H__

#include "WPILib.h"

class Arm
{
	private:
		Victor* motorA;
		Victor* motorB;
		float rawValue;
	
	public:
		Arm(int motorApwm, int motorBpwm);
		void Handle();
		void SetRaw(float value);
		
		~Arm();
};
#endif
