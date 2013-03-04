#include "Arm.h"
#include "../Declarations.h"
#include "../CowLib.h"
#include "../CowConstants.h"

using namespace CowLib;

Arm::Arm(int motorApwm, int motorBpwm, int potPwm, int lockSolenoid) :
	PID_P(8),
	PID_D(1),
	m_PreviousError(0),
	m_RawValue(0),
	m_LockState(LOCKED),
	m_ArmState(STARTING_POS),
	m_ArmSpeed(LOW)
{
	for(int i = 0; i < STATE_COUNT*STATE_COUNT; i++)
	{
		m_ArmSpeedLookup[i / STATE_COUNT][i % STATE_COUNT] = LOW;
	}
	m_MotorA = new Talon(motorApwm);
	m_MotorB = new Talon(motorBpwm);
	m_Pot = new AnalogChannel(potPwm);
	m_Setpoint = CowConstants::getInstance()->getValueForKey("ArmStartingPosition");
	m_Lock = new Solenoid(lockSolenoid);
	m_LockTimer = 0;
}

void Arm::SetupArmSpeed(ArmStates startState, ArmStates endState, ArmSpeeds speed)
{
	m_ArmSpeedLookup[startState][endState] = speed;
}

Arm::ArmSpeeds Arm::GetArmSpeed(ArmStates startState, ArmStates endState)
{
	return m_ArmSpeedLookup[startState][endState];
}

void Arm::Handle()
{
	float error = m_Setpoint - m_Pot->GetVoltage();
	float errorChange = error - m_PreviousError;
	float output = (error * PID_P) + (errorChange * PID_D);
	
	
	if(error < 0.2 && error > -0.2)
	{
		m_ArmState = m_WantedArmState;
		//printf("Arrived at new state\n");
	}
	
	if(m_LockState == UNLOCKING  && (Timer::GetFPGATimestamp() - m_LockTimer) > 0.5)
	{
		m_LockState = UNLOCKED;
	}
	
	// 0.15 = -1.2%
	if(m_LockState == UNLOCKED)
	{
		if(m_ArmSpeed == FULL)
			output = CowLib::LimitMix(output, 1.0);
		else if(m_ArmSpeed == MED)
			output = CowLib::LimitMix(output, 0.8);
		else if(m_ArmSpeed == LOW)
			output = CowLib::LimitMix(output, 0.5);
		else if(m_ArmSpeed == OFF)
			output = CowLib::LimitMix(output, 0);
		
		if((m_Setpoint > CowConstants::getInstance()->getValueForKey("ArmGroundPosition") + 0.01 && output > 0 && m_Setpoint != CowConstants::getInstance()->getValueForKey("ArmFinishHang"))|| m_Pot->GetVoltage() < 1)
		{
			output = 0;
		
			m_MotorA->Set(m_RawValue);
			m_MotorB->Set(m_RawValue);
		} 
		else 
		{
			m_MotorA->Set(output);
			m_MotorB->Set(output);
		}
	}
	else
	{
		m_MotorA->Set(0);
		m_MotorB->Set(0);
	}
	//printf("%f\t\t%f\t\t%f\n", m_Setpoint, m_Pot->GetVoltage(), output);
//	if(m_ArmState == STARTING_POS)
//		cout << "STARTING POS";
//	if(m_ArmState == FAR)
//		cout << "FAR";
//	if(m_ArmState == MIDDLE)
//		cout << "MIDDLE";
//	if(m_ArmState == NEAR)
//		cout << "NEAR";
//	if(m_ArmState == APPROACH)
//		cout << "APPR";
//	if(m_ArmState == HANG)
//		cout << "HANG";
//	if(m_ArmState == GROUND)
//		cout << "GND";
//	if(m_ArmState == CRASH_PAD)
//		cout << "CRASH";
//	
////	if(m_ArmSpeed == FULL)
////		cout << "FULL";
////	else if(m_ArmSpeed == MED)
////		cout << "MED";
////	else if(m_ArmSpeed == LOW)
////		cout << "LOW";
////	
//	cout << endl;
	m_PreviousError = error;
}

float Arm::GetSetpoint()
{
	return m_Setpoint;
}

void Arm::SetSetpoint(float value)
{
	m_Setpoint = value;
} 

void Arm::SetRaw(float value)
{
	m_RawValue = value;
}

void Arm::Lock(bool value)
{
	m_Lock->Set(value);
	//we're unlocking
	if(m_LockState == LOCKED && value == true)
	{
		m_LockState = UNLOCKING;
		m_LockTimer = Timer::GetFPGATimestamp();
	}	
}

void Arm::SetState(ArmStates armState)
{
	/*
	 * SetupArmSpeed(FAR, MIDDLE, MED);
	 * SetupArmSpeed(FAR, NEAR, MED);
	 * SetupArmSpeed(FAR, FEEDER, MED);
	 * SetupArmSpeed(MIDDLE, FAR, MED);
	 * SetupArmSpeed(MIDDLE, NEAR, MED);
	 * SetupArmSpeed(MIDDLE, FEEDER, MED);
	 * SetupArmSpeed(NEAR, FAR, MED);
	 * SetupArmSpeed(NEAR, MIDDLE, MED);
	 * SetupArmSpeed(NEAR, FEEDER, MED);
	 * SetupArmSpeed(GROUND, FAR, FULL);
	 * SetupArmSpeed(GROUND, MIDDLE, FULL);
	 * SetupArmSpeed(GROUND, NEAR, FULL);
	 * SetupArmSpeed(GROUND, FEEDER, FULL);
	 * SetupArmSpeed(CRASH_PAD, FAR, FULL);
	 * SetupArmSpeed(CRASH_PAD, MIDDLE, FULL);
	 * SetupArmSpeed(CRASH_PAD, NEAR, FULL);
	 * SetupArmSpeed(CRASH_PAD, FEEDER, FULL);
	 * SetupArmSpeed(STARTING_POS, APPROACH, FULL);
	 * SetupArmSpeed(STARTING_POS, GROUND, FULL);
	 * SetupArmSpeed(STARTING_POS, CRASH_PAD, FULL);
	 * 
	 */
	if(armState == STARTING_POS)
	{
		m_ArmSpeed = MED;
	}
	else if(armState == FAR || armState == MIDDLE || armState == NEAR || armState == FEEDER)
	{
		if(m_ArmState == STARTING_POS)
			m_ArmSpeed = LOW;
		else if(m_ArmState == FAR || m_ArmState == MIDDLE || m_ArmState == NEAR)
			m_ArmSpeed = MED;
		else if(m_ArmState == GROUND || m_ArmState == CRASH_PAD)
			m_ArmSpeed = FULL;
		else
			m_ArmSpeed = MED;
	}
	else if(armState == APPROACH)
	{
		if(m_ArmState == FAR || m_ArmState == MIDDLE || m_ArmState == NEAR || m_ArmState == STARTING_POS)
		{
			m_ArmSpeed = MED;
		}
		else if(m_ArmState == GROUND || m_ArmState == CRASH_PAD)
		{
			m_ArmSpeed = FULL;
		}
	}
	else if(armState == HANG)
	{
		m_ArmSpeed = FULL;
	}
	else if(armState == GROUND || armState == CRASH_PAD)
	{
		if(m_ArmState == GROUND || m_ArmState == CRASH_PAD || m_ArmState == APPROACH)
			m_ArmSpeed = FULL;
		else if(m_ArmState == FAR || m_ArmState == MIDDLE || m_ArmState == NEAR)
			m_ArmSpeed = MED;
		else if(m_ArmState == STARTING_POS)
			m_ArmSpeed = FULL;
		else
			m_ArmSpeed = LOW;
	}
	else if(armState == CRASH_PAD)
	{
		if(m_ArmState == GROUND)
			m_ArmSpeed = FULL;
	}
	m_WantedArmState = armState;
	
	
	
//	if(cb->getOperatorButton(9))
//		bot->GetArm()->SetSetpoint(CowConstants::getInstance()->getValueForKey("ArmMidPosition"));
//	if(cb->getOperatorButton(7))
//		bot->GetArm()->SetSetpoint(CowConstants::getInstance()->getValueForKey("ArmLowPosition"));
//	if(cb->getSteeringButton(3))
//		bot->GetArm()->SetSetpoint(CowConstants::getInstance()->getValueForKey("ArmGroundPosition") - 0.19);
//	if(cb->getSteeringButton(1))
//		bot->GetArm()->SetSetpoint(CowConstants::getInstance()->getValueForKey("ArmApproachHang"));
//	if(cb->getSteeringButton(4))
//		bot->GetArm()->SetSetpoint(CowConstants::getInstance()->getValueForKey("ArmGroundPosition"));
//	if(cb->getDriveButton(1))
//		bot->GetArm()->SetSetpoint(CowConstants::getInstance()->getValueForKey("ArmStartingPosition"));
//	
	if(armState == STARTING_POS)
		SetSetpoint(CowConstants::getInstance()->getValueForKey("ArmStartingPosition"));
	else if(armState == FAR)
		SetSetpoint(CowConstants::getInstance()->getValueForKey("ArmHighPosition"));
	else if(armState == MIDDLE)
		SetSetpoint(CowConstants::getInstance()->getValueForKey("ArmMidPosition"));
	else if(armState == NEAR)
		SetSetpoint(CowConstants::getInstance()->getValueForKey("ArmLowPosition"));
	else if(armState == FEEDER)
		SetSetpoint(CowConstants::getInstance()->getValueForKey("ArmFeederPosition"));
	else if(armState == GROUND)
		SetSetpoint(CowConstants::getInstance()->getValueForKey("ArmGroundPosition"));
	else if(armState == CRASH_PAD)
		SetSetpoint(CowConstants::getInstance()->getValueForKey("ArmCrashPadPosition"));
	else if(armState == APPROACH)
		SetSetpoint(CowConstants::getInstance()->getValueForKey("ArmApproachHang"));
	else if(armState == HANG)
		SetSetpoint(CowConstants::getInstance()->getValueForKey("ArmGroundPosition"));
}

Arm::~Arm()
{
	delete m_MotorA;
	delete m_MotorB;
}
