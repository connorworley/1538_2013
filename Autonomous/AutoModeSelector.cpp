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
	
	switch (m_Index)
	{
	case am3DiskNear:
		sprintf(str,"3 Disc, High, Near       ");
		s.assign(str);
		break;
	case am7Disk:
		sprintf(str,"7 Disc                   ");
		s.assign(str);
		break;
	case amTesting:
		sprintf(str,"(Testing)                ");
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
	cout << "Writing auto controller" << endl;
	autoController->reset();
	switch(m_Index)
	{
	case am3DiskNear:
		autoController->addCommand(RobotCommand(CMD_DRIVE_DIST, -55, 0, 0.5f, 0, Arm::CRASH_PAD, 0, 0, 0, 2.5));
		autoController->addCommand(RobotCommand(CMD_DRIVE_HOLD_DIST, 24, 0, 0.45f, 0, Arm::CRASH_PAD, 0, 0, 0, 2));
		autoController->addCommand(RobotCommand(CMD_DRIVE_HOLD_DIST, 24, 0, 0.8f, 1, Arm::MIDDLE, 0, 0, 0, 0.75));
		autoController->addCommand(RobotCommand(CMD_DRIVE_DIST, 52, 0, 0.8f, 1, Arm::MIDDLE, 0, 0, 0, 0.5));
		autoController->addCommand(RobotCommand(CMD_SHOOTINPLACE, 52, 0, 0.8f, 1, Arm::MIDDLE, 0, -1, 4, 4));
		break;
	case am7Disk:
		autoController->addCommand(RobotCommand(CMD_DRIVE_DIST,     -55, 0, 0.8f, 0.5f, Arm::CRASH_PAD, 0, 0, 0, 1));
		autoController->addCommand(RobotCommand(CMD_DRIVE_DIST,      33, 0, 1.0f, 0.5f, Arm::CRASH_PAD, 0, 0, 0, 1));
		autoController->addCommand(RobotCommand(CMD_DRIVE_HOLD_DIST, 33, 0, 1.0f, 1.0f, Arm::MIDDLE,    0, 0, 0, 0.25));
		autoController->addCommand(RobotCommand(CMD_DRIVE_DIST,      48, 0, 0.8f, 1.0f, Arm::MIDDLE,    0, 0, 0, 2));
		autoController->addCommand(RobotCommand(CMD_SHOOTINPLACE,    48, 0, 1.0f, 1.0f, Arm::MIDDLE,    0, -1, 3, 4.625));
		autoController->addCommand(RobotCommand(CMD_DRIVE_DIST,      12, 0, 1.0f, 0.0f, Arm::CRASH_PAD, 0, 0, 0, 1));
		autoController->addCommand(RobotCommand(CMD_DRIVE_DIST,     190, 0, 1.0f, 0.0f, Arm::GROUND,   -1, 0, 0, 3));
		autoController->addCommand(RobotCommand(CMD_DRIVE_DIST,      96, 0, 1.0f, 0.0f, Arm::GROUND,      0.5, 0, 0, 0.25));
		autoController->addCommand(RobotCommand(CMD_DRIVE_DIST,      96, 0, 1.0f, 0.0f, Arm::GROUND,      -1, 0, 0, 0.75));
		autoController->addCommand(RobotCommand(CMD_DRIVE_DIST,      96, 0, 1.0f, 1.0f, Arm::FAR,      -1, 0, 0, 1.75));
		autoController->addCommand(RobotCommand(CMD_SHOOTINPLACE,    96, 0, 1.0f, 1.0f, Arm::FAR,      -1, -1, 4, 10));
		break;
	case amTesting:		
		break;
	case amDoNothing:
		break;
	default:
		m_Index = amFirst + 1;
		break;
	}
	
	
	//TDO: Make this
}
