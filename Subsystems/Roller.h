#ifndef __Roller_H__
#define __Roller_H__

#include "WPILib.h"

class Roller
{
	private:
		Talon* m_MotorA;
		Talon* m_MotorB;
		float m_RawValue;
	
	public:
		Roller(int motorApwm, int motorBpwm);
		void Handle();
		void SetRaw(float value);
		
		~Roller();
};
#endif
