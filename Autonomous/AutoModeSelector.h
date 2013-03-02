//=============================================================================
// File: AutoModeSelector.h
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

#ifndef _AUTO_SELECTOR_H
#define _AUTO_SELECTOR_H

#include <string>
#include "../Controllers/AutoModeController.h"

using namespace std;


// Note:
// This all sucks.
// I want to change it

class AutoModeSelector
{
	
public:
	enum AutoModes{
		amFirst = 0,
		am3DiscHighSide,
		am3DiskHighCenter,
		am7DiskFront,
		amDriveStraight,
		amDoNothing,
		amLast
	};	
	
	void Increment();
	
	// Get a description of this auto mode
	string Description();
	void WriteToAutoModeController(AutoModeController * ac);
	
	
private:
	int m_Index;
	int m_SecIndex;
};

#endif
