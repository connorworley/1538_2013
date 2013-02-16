#ifndef __ARM_H__
#define __ARM_H__

#include "WPILib.h"

class Arm
{
	private:
		const float PID_P;
		const float PID_D;
	
		Talon* m_MotorA;
		Talon* m_MotorB;
		AnalogChannel* m_Pot;
		Solenoid* m_Lock;
			
		float m_Setpoint;
		float m_PreviousError;
		float m_RawValue;
	
	public:
		Arm(int motorApwm, int motorBpwm, int potPwm, int lockSolenoid);
		void Handle();
		float Arm::GetSetpoint();
		void SetSetpoint(float value);
		void SetRaw(float value);
		void Lock(bool value);
		
		~Arm();
};
#endif
