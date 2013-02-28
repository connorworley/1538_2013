//=============================================================================
// File: CowRobot.cpp
//
// COPYRIGHT 2013 The Holy Cows (1538)
// All rights reserved.  1538 proprietary and confidential.
//             
// The party receiving this software directly from 1538 (the "Recipient")
// may use this software and make copies thereof as reasonably necessary solely
// for the purposes set forth in the agreement between the Recipient and
// 1538 (the "Agreement").  The software may be used in source code form
// solely by the Recipient's employees/volunteers.  The Recipient shall have 
// no right to sublicense, assign, transfer or otherwise provide the source
// code to any third party. Subject to the terms and conditions set forth in
// the Agreement, this software, in binary form only, may be distributed by
// the Recipient to its users. 1538 retains all ownership rights in and to
// the software.
//
// This notice shall supercede any other notices contained within the software.
//=============================================================================

#include "CowRobot.h"
#include <math.h>
#include "CowConstants.h"
#include "CowControlBoard.h"
CowRobot* CowRobot::m_SingletonInstance = NULL;
#include "CounterBase.h"
#include "CowLib.h"

#define DRIVECODELCDDEBUGER 1

using namespace CowLib;

/// Creates (if needed) and returns a singleton instance of the CowRobot
CowRobot * CowRobot::GetInstance()
{
	// If we have not created a robot yet, do so.
	// If we have created a robot, skip this
	if (m_SingletonInstance == NULL)
	{
		m_SingletonInstance = new CowRobot();
	}
	return m_SingletonInstance;
}

/// Constructor for CowRobot
CowRobot::CowRobot()
{	
	// Set up drive motors
	m_RightDrive = new Talon(RIGHT_DRIVE);
	m_LeftDrive = new Talon(LEFT_DRIVE);
	
	m_Arm = new Arm(ARM_A, ARM_B, ARM_POT, ARMLOCK_SOLENOID_CHAN);
	m_Intake = new Roller(INTAKE_A, INTAKE_B);
	m_Feeder = new Roller(FEEDER_A, FEEDER_B);
	m_Shooter = new Roller(SHOOTER_A, SHOOTER_B);

	//Solenoids
	m_Shifter = new Solenoid(SHIFTER_SOLENOID_CHAN);

	// Set up encoders
	m_Encoder = new Encoder(LEFT_ENCODER_A_CHAN, LEFT_ENCODER_B_CHAN, true, CounterBase::k1X);
	m_Encoder->SetDistancePerPulse(0.1007081038552321);
	m_Encoder->SetReverseDirection(false);
	m_Encoder->Start();

	m_Gyro = new Gyro(2);
	m_Gyro->SetSensitivity(0.0005); //Kiets
	m_Gyro->Reset();

	velTimer = new Timer();
	velTimer->Start();

	m_ShifterCounts = 0;
	m_CurrentShiftState = SHIFTER_STATE_HIGH;
	m_ShifterTimer = 0;

	m_LeftDriveValue = 0;
	m_RightDriveValue = 0;
	
	m_Reset = false;
}

/// Used to handle the recurring logic funtions inside the robot.
/// Please call this once per update cycle.
void CowRobot::Handle()
{		
	m_PrintCount++;

	// Default drive
	float tmpLeftMotor = m_LeftDriveValue;
	float tmpRightMotor = m_RightDriveValue;

	SetLeftMotors(tmpLeftMotor);
	SetRightMotors(tmpRightMotor);
	m_Arm->Handle();
	m_Intake->Handle();
	m_Feeder->Handle();
	m_Shooter->Handle();
}

/// Allows skid steer robot to be driven using tank drive style inputs
/// @param leftDriveValue
/// @param rightDriveValue
///
void CowRobot::DriveLeftRight(float leftDriveValue, float rightDriveValue)
{
	m_LeftDriveValue = leftDriveValue;
	m_RightDriveValue = rightDriveValue;
}

void CowRobot::DriveSpeedTurn(float speed, float turn, bool quickTurn)
{
	//Linear degredation of steeering based off of velocity
	//	velocity *= 0.003;
	float temp_vel = speed;
	float sensitivity = 0;
	float unscaled_turn = 0;

	if (temp_vel < 0)
		temp_vel = -temp_vel;

	//printf("Velocity: %f, stick: %f\r\n", velocity, temp_vel);
	
	if(speed < 0.10 && speed > -0.10)
		speed = 0;
	if (turn < 0.10 && turn > -0.10 || (speed == 0 && !quickTurn))
		turn = 0;

	unscaled_turn = turn;

	if(quickTurn)
		sensitivity = 1;
	else
		sensitivity = 0.2;

	turn *= sensitivity;
	turn = -turn;
	

	float left_power = LimitMix(speed + turn);
	float right_power = LimitMix(speed - turn);

	DriveLeftRight(left_power, right_power);
}

/// Allows robot to spin in place
/// @param turnRate
///
void CowRobot::QuickTurn(float turnRate)
{
	//when provided with + turn, quick turn right

	float left = -1 * turnRate;
	float right = turnRate;

	DriveLeftRight(left, right);
}

/// Returns the value of the drive's left side encoder
Encoder * CowRobot::GetEncoder()
{
	return m_Encoder;
}

Gyro * CowRobot::GetGyro()
{
	return m_Gyro;
}

void CowRobot::AskForShift(ShifterStates shifterState)
{
	if(shifterState != m_CurrentShiftState)
	{
		m_ShifterTimer = Timer::GetFPGATimestamp();
		m_Shifter->Set(shifterState);
		m_CurrentShiftState = shifterState;
	}
}

/// sets the left side motors
void CowRobot::SetLeftMotors(float val)
{
	if (val > 1.0)
		val = 1.0;
	if (val < -1.0)
		val = -1.0;

	if((Timer::GetFPGATimestamp() - m_ShifterTimer) <= 0.125)
		val = 0;

	m_LeftDrive->SetSpeed(-val);
}

/// sets the left side motors
void CowRobot::SetRightMotors(float val)
{
	if (val > 1.0)
		val = 1.0;
	if (val < -1.0)
		val = -1.0;

	if((Timer::GetFPGATimestamp() - m_ShifterTimer) <= 0.125)
		val = 0;

	m_RightDrive->SetSpeed(val);
}

bool CowRobot::InHighGear()
{
	return (m_CurrentShiftState == SHIFTER_STATE_HIGH);
}


Arm* CowRobot::GetArm()
{
	return m_Arm;
}

Roller* CowRobot::GetIntake()
{
	return m_Intake;
}

Roller* CowRobot::GetFeeder()
{
	return m_Feeder;
}

Roller* CowRobot::GetShooter()
{
	return m_Shooter;
}
