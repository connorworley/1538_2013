#ifndef __ARM_H__
#define __ARM_H__

#include "WPILib.h"

class Arm
{
	public:
		enum ArmStates
		{
			STARTING_POS = 0,
			FAR,
			MIDDLE,
			NEAR,
			FEEDER,
			APPROACH,
			HANG,
			GROUND,
			CRASH_PAD,
			ThreePointDiagonal,
			STATE_COUNT // Make sure this is always last
		};
		Arm(int motorApwm, int motorBpwm, int potPwm, int lockSolenoid);
		void Handle();
		float Arm::GetSetpoint();
		void SetSetpoint(float value);
		void SetRaw(float value);
		void SetState(ArmStates armState);
		void Lock(bool value);
		
		~Arm();
	private:
		enum LockStates
		{
			UNLOCKED = 0,
			UNLOCKING,
			LOCKED,
		};
		

		
		enum ArmSpeeds
		{
			FULL = 0,
			MED,
			LOW,
			OFF
		};
		
		const float PID_P;
		const float PID_D;
	
		Talon* m_MotorA;
		Talon* m_MotorB;
		AnalogChannel* m_Pot;
		Solenoid* m_Lock;
		
		ArmSpeeds m_ArmSpeedLookup[STATE_COUNT][STATE_COUNT];
		void SetupArmSpeed(ArmStates startState, ArmStates endState, ArmSpeeds speed);
		ArmSpeeds GetArmSpeed(ArmStates startState, ArmStates endState);
			
		float m_Setpoint;
		float m_PreviousError;
		float m_RawValue;
		
		double m_LockTimer;
		
		LockStates m_LockState;
		ArmStates m_WantedArmState;
		ArmStates m_ArmState;
		ArmSpeeds m_ArmSpeed;
		
};
#endif
