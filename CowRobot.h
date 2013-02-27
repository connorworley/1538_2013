#ifndef _Cow_ROBOT_H
#define _Cow_ROBOT_H
//=============================================================================
// File: CowRobot.h
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

#include "WPILib.h"
#include "Vision/RGBImage.h"
#include "Vision/BinaryImage.h"

#include "SmartDashboard/SmartDashboard.h"

#include "CowLib.h"
#include "subsystems/Arm.h"
#include "subsystems/Roller.h"

#include "server/CowServer.h"

#include "taskHookLib.h"
#include "private/rtpLibP.h"

#include "DaisyFilter.h"

/// This class provides core robot functionality and encapsulates 
/// motors, sensors, relays, etc.
///
class CowRobot
{
	public: 
	static CowRobot * m_SingletonInstance;
	
	enum ShifterStates{
		SHIFTER_STATE_HIGH,
		SHIFTER_STATE_LOW
	};
	
	static CowRobot* GetInstance();
	
	void DriveSpeedTurn(float speed, float turn, bool quickTurn);
	void DriveLeftRight(float leftDriveValue, float rightDriveValue);
	void QuickTurn(float turn);
	
	Encoder * GetEncoder();
	
	Gyro * GetGyro();
	Joystick * m_Joystick;

	Solenoid* GetShifter();
	Solenoid* GetArmLock();
	
	Arm* GetArm();
	Roller* GetIntake();
	Roller* GetFeeder();
	Roller* GetShooter();
	
	Timer* velTimer;	
	void Handle();

	
	void AskForShift(ShifterStates shifterState);
	
	bool InHighGear();
	
private:
	SmartDashboard* m_SmartDashboard;
	
	void Shift(ShifterStates shifterState);
	
	// Drive Motors
	Talon *m_RightDrive;
	Talon *m_LeftDrive;
	
	// Drive shifting pistons
	Solenoid *m_Shifter;
		
	//Sensors
	Gyro * m_Gyro;
	Encoder *m_Encoder;
	
	Arm* m_Arm;
	Roller* m_Intake;
	Roller* m_Feeder;
	Roller* m_Shooter;
	
	float m_LeftDriveValue;
	float m_RightDriveValue;
	
	int m_PrintCount;

	int m_ShifterCounts;
	
	ShifterStates m_CurrentShiftState;
	double m_ShifterTimer;
	
	bool m_Reset;
	
	CowRobot();
	
	void SetLeftMotors(float val);
	void SetRightMotors(float val);
};

#endif
