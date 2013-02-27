#ifndef _Cow_CONTROL_BOARD_H
#define _Cow_CONTROL_BOARD_H
//=============================================================================
// File: CowControlBoard.h
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
#include "CowRobot.h"

#define SHIFTER_BUTTON			4
#define AUTON_BUTTON			1
#define PID_BUTTON				3

#define LEFT_GAMEPAD_X			1
#define LEFT_GAMEPAD_Y			2
#define RIGHT_GAMEPAD_X			3
#define RIGHT_GAMEPAD_Y			4
#define STEERING_X				1

#define FAST_TURN				6 

/// This class offers access to the 2010 specific Cow Control Board
///
class CowControlBoard
{
private:
	DriverStationEnhancedIO * ds;
	static CowControlBoard *singletonInstance;
	bool autoLatch;
	bool alignLatch;
	bool rampLatch;
	bool telescopeLatch;
	
	Joystick* driveStick;
	Joystick* steeringWheel;
	Joystick* operatorPanel;
	Joystick* m_OperatorArm;
	
	// Construction
	CowControlBoard();
	
public:
	
	static CowControlBoard* getInstance();
	bool getQuickTurn();
	bool getButtonShifter();
	bool getButtonAutoSelect();
	
	float getDriveStickY();
	float getSteeringX();
	float getOperatorY();
	float getOperatorDpadX();
	float getOperatorDpadY();
	float GetOperatorArmY();
	
	bool getDriveButton(int button);
	bool getSteeringButton(int button);
	bool getOperatorButton(int button);
	bool GetOperatorArmButton(int button);
};

#endif
