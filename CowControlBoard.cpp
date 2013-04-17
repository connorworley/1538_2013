//=============================================================================
// File: CowControlBoard.cpp
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
#include "CowControlBoard.h"
#include "WPILib.h"
#include "CowRobot.h"

// Initialize the Singleton instance
CowControlBoard* CowControlBoard::singletonInstance = NULL;

/// Creates (if needed) and returns a singleton Control Board instance
CowControlBoard* CowControlBoard::getInstance()
{
	if( singletonInstance == NULL)
		singletonInstance = new CowControlBoard(); 
	return singletonInstance;
}

/// Constructor for Cow Control Board
CowControlBoard::CowControlBoard()
{
	ds = & DriverStation::GetInstance()->GetEnhancedIO();
	driveStick = new Joystick(1);
	steeringWheel = new Joystick(2);
	operatorPanel = new Joystick(3);
	m_OperatorArm = new Joystick(4);
	autoLatch = false;
	alignLatch = false;
	rampLatch = false;
	telescopeLatch = false;
}

/// Returns state of shifter switch
bool CowControlBoard::getButtonShifter()
{
	return getDriveButton(SHIFTER_BUTTON);
}

/// Returns state of autonomous select button
bool CowControlBoard::getButtonAutoSelect()
{
	// This will latch on a press and only return true once per press
	// Active Low signal
	if(getDriveButton(AUTON_BUTTON))
	{
		if(!autoLatch)
		{
			autoLatch = true;
			return true;
		}
	}
	else
		autoLatch = false;
	return false;
}


/// Returns the state of the quick turn
bool CowControlBoard::getQuickTurn()
{
	return !getDriveButton(8);
}

float CowControlBoard::getDriveStickY()
{
	return driveStick->GetRawAxis(LEFT_GAMEPAD_Y);
}

float CowControlBoard::getSteeringX()
{
	return steeringWheel->GetRawAxis(STEERING_X);
}

float CowControlBoard::getOperatorY()
{
	return operatorPanel->GetRawAxis(LEFT_GAMEPAD_Y);
}

float CowControlBoard::getOperatorDpadX()
{
	return operatorPanel->GetRawAxis(5);
}

float CowControlBoard::getOperatorDpadY()
{
	return operatorPanel->GetRawAxis(6);
}
float CowControlBoard::GetOperatorArmY()
{
	return m_OperatorArm->GetRawAxis(LEFT_GAMEPAD_Y);
}

bool CowControlBoard::GetOperatorArmButton(const int button)
{
	return m_OperatorArm->GetRawButton(button);
}

bool CowControlBoard::getDriveButton(const int button)
{
	return driveStick->GetRawButton(button);
}

bool CowControlBoard::getOperatorButton(const int button)
{
	return operatorPanel->GetRawButton(button);
}

bool CowControlBoard::getSteeringButton(const int button)
{
	return steeringWheel->GetRawButton(button);
}


