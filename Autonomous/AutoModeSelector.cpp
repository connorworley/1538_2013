//=============================================================================
// File: AutoModeSelector.cpp
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

#include "AutoModeSelector.h"
#include "../CowConstants.h"
#include <string>

void AutoModeSelector::Increment()
{
	m_Index++;
	if(m_Index == amLast)
		m_Index = amFirst + 1;
	printf("Auto mode selected: %d\r\n",m_Index);
}

string AutoModeSelector::Description()
{
	char str[25];
	memset(str, '.', 25);
	string s = "";

	/*
	amLeft1,
	amLeft2,
	amMiddle1,
	amMiddle2,
	amMiddle3,
	amRight1,
	amRight2,
	
	*/
	
	switch (m_Index)
	{
	case am3DiscHighSide:
		sprintf(str,"3 Disc, High, Side       ");
		s.assign(str);
		break;
	case am3DiskHighCenter:
		sprintf(str,"3 Disc, High, Center     ");
		s.assign(str);
		break;
	case am7DiskFront:
		sprintf(str,"7 Disc Front             ");
		s.assign(str);
		break;
	case amDriveStraight:
		sprintf(str,"Drive Straight (Testing) ");
		s.assign(str);
		break;
	case amDoNothing:
		sprintf(str,"Do Nothing               ");
		s.assign(str);
		break;
	default:
		sprintf(str,"It broke                 ");
		m_Index = amFirst + 1;
		s.assign(str);
		break;
	}

	return s;
}

void AutoModeSelector::WriteToAutoModeController(AutoModeController * autoController)
{
	// addCommand(TYPE, DRIVE COUNTS, HEADING, SHOOTER, ARM PISTON STATE, INTAKE, CHUTE, WANTED # BALLS SHOT, TIMEOUT)
	
	
//	m_Command(CMD_NULL),
//	m_EncoderCount(0),
//	m_Heading(0),
//	m_Shooter(0),
//	m_ArmSetpoint(0),
//	m_Intake(0),
//	m_Timeout(0)
	autoController->reset();
	switch(m_Index)
	{
	case am3DiscHighSide:
		autoController->addCommand(RobotCommand(CMD_DRIVE_DIST, -55, 0, 0.5f, 0, Arm::CRASH_PAD, 0, 0, 0, 2.5));
		autoController->addCommand(RobotCommand(CMD_DRIVE_HOLD_DIST, 24, 0, 0.45f, 0, Arm::CRASH_PAD, 0, 0, 0, 2));
		autoController->addCommand(RobotCommand(CMD_DRIVE_HOLD_DIST, 24, 0, 0.8f, 1, Arm::MIDDLE, 0, 0, 0, 0.75));
		autoController->addCommand(RobotCommand(CMD_DRIVE_DIST, 52, 0, 0.8f, 1, Arm::MIDDLE, 0, 0, 0, 0.5));
		autoController->addCommand(RobotCommand(CMD_SHOOTINPLACE, 52, 0, 0.8f, 1, Arm::MIDDLE, 0, -1, 4, 4));
		//autoController->addCommand(CMD_AUTOAIM, 0, 0, shooterKey, 3);
		break;
	case am7DiskFront:
		autoController->addCommand(RobotCommand(CMD_DRIVE_DIST, -55, 0, 0.5f, 0, Arm::CRASH_PAD, 0, 0, 0, 2.5));
		autoController->addCommand(RobotCommand(CMD_DRIVE_HOLD_DIST, 24, 0, 0.45f, 0, Arm::CRASH_PAD, 0, 0, 0, 2));
		autoController->addCommand(RobotCommand(CMD_DRIVE_HOLD_DIST, 24, 0, 0.8f, 1, Arm::MIDDLE, 0, 0, 0, 0.75));
		autoController->addCommand(RobotCommand(CMD_DRIVE_DIST, 52, 0, 0.8f, 1, Arm::MIDDLE, 0, 0, 0, 0.5));
		autoController->addCommand(RobotCommand(CMD_SHOOTINPLACE, 52, 0, 0.8f, 1, Arm::MIDDLE, 0, -1, 4, 4));
		autoController->addCommand(RobotCommand(CMD_DRIVE_DIST, 12, 0, 0.5f, 0, Arm::CRASH_PAD, 0, 0, 0, 1.5));
		autoController->addCommand(RobotCommand(CMD_DRIVE_DIST, 180, 0, 0.5f, 0, Arm::GROUND, -0.5, 0, 0, 3));
		autoController->addCommand(RobotCommand(CMD_DRIVE_DIST, 80, 0, 0.35f, 1, Arm::FAR, -0.5, 0, 0, 4));
		autoController->addCommand(RobotCommand(CMD_SHOOTINPLACE, 80, 0, 0.8f, 1, Arm::FAR, -0.5, -1, 10, 6));


		//autoController->addCommand(CMD_AUTOAIM, 0, 0, shooterKey, 3);
		break;
	case amDriveStraight:

//		autoController->addCommand(RobotCommand(CMD_ARM, 30, 0, 0, Arm::MIDDLE, 0, 0, 1.5));
//		autoController->addCommand(RobotCommand(CMD_DRIVE_DIST, 65, 0, 1, Arm::MIDDLE, 0, 0, 2));
//		autoController->addCommand(RobotCommand(CMD_DRIVE_DIST, 65, 0, 1, Arm::MIDDLE, 0, 0, 2));
//		autoController->addCommand(RobotCommand(CMD_SHOOTINPLACE, 0, 0, 1, Arm::MIDDLE , 0, 0, 1));
//		autoController->addCommand(RobotCommand(CMD_SHOOTINPLACE, 0, 0, 1, Arm::MIDDLE , 0, -1, 7));		
		break;
	case amDoNothing:

		break;
	default:
		m_Index = amFirst + 1;
		break;
	}
	
	
	//TDO: Make this
}
