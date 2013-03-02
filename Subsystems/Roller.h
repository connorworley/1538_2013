#ifndef __Roller_H__
#define __Roller_H__

#include "WPILib.h"

typedef enum {
	STAGING,
	STAGED,
	COOLDOWN,
	OFF
} FeederStates;

class Roller
{
	private:
		Talon* m_MotorA;
		Talon* m_MotorB;
		float m_RawValue;
		DigitalInput* m_LimitSwitch;
		
		bool m_WaitOnTrigger;
		float m_TriggerTimeout;
		float m_TriggerTime;
		float m_DebounceTimer;
		float m_DebounceTime;
		bool m_PreviousState;
		
		bool m_Fired;
		
		ReederStates m_State;
	
	public:
		Roller(int motorApwm, int motorBpwm);
		void Handle();
		void SetRaw(float value);
		void SetTimeWaitTrigger(float time)
		{
			m_TriggerTimeout = time;
		}
		void SetDebounceTime(float time)
		{
			m_DebounceTime = time;
		}
		
		void CreateLimitSwitch(int port, float waittime, float debouncetime);
		bool GetLimitSwitch();
		
		~Roller();
};
#endif
