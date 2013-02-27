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

void AutoModeSelector::increment()
{
	index++;
	if(index == amLast)
		index = amFirst + 1;
	printf("Auto mode selected: %d\r\n",index);
}

string AutoModeSelector::description()
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
	
	switch (index)
	{
	case am3Disc:
		sprintf(str,"3 Disc                   ");
		s.assign(str);
		break;
	case am7DiskFront:
		sprintf(str,"7 Disc Front             ");
		s.assign(str);
		break;
	case amDoNothing:
		sprintf(str,"Do Nothing               ");
		s.assign(str);
		break;
	default:
		sprintf(str,"It broke                 ");
		index = amFirst + 1;
		s.assign(str);
		break;
	}

	return s;
}

void AutoModeSelector::writeToAutoModeController(AutoModeController * autoController)
{
	// addCommand(TYPE, DRIVE COUNTS, HEADING, SHOOTER, ARM PISTON STATE, INTAKE, CHUTE, WANTED # BALLS SHOT, TIMEOUT)
	
	autoController->reset();
	switch(index)
	{
	case am3Disc:
		//autoController->addCommand(CMD_AUTOAIM, 0, 0, shooterKey, 3);
		break;
	case am7DiskFront:
		//autoController->addCommand(CMD_AUTOAIM, 0, 0, shooterKey, 3);
		break;
	case amDoNothing:

		break;
	default:
		index = amFirst + 1;
		break;
	}
	
	
	//TDO: Make this
}
