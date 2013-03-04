#ifndef __Roller_H__
#define __Roller_H__

#include "WPILib.h"

typedef enum {
	STAGING,
	FIRING,
	FIRED
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
		FeederStates m_State;
		unsigned int m_FiredDisks;
	
	public:
		Roller(int motorApwm, int motorBpwm);
		void Handle();
		void SetRaw(float value);
		float GetRaw();
		void SetTimeWaitTrigger(float time)
		{
			m_TriggerTimeout = time;
		}
		void SetDebounceTime(float time)
		{
			m_DebounceTime = time;
		}
		
		unsigned int GetFiredDisks()
		{
			return m_FiredDisks;
		}
		
		void CreateLimitSwitch(int port, float waittime, float debouncetime);
		bool GetLimitSwitch();
		
		~Roller();
};
#endif
