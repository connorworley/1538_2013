#ifndef _OPERATOR_CONTROLLER_H
#define _OPERATOR_CONTROLLER_H
//=============================================================================
// File: OperatorController.h
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

#include "../CowRobot.h"
#include "WPILib.h"
#include "../CowControlBoard.h"
#include "../CowConstants.h"

class OperatorController{
	
private:
	CowRobot * bot;
	Joystick * throttle, * wheel;
	bool telescopeExtend;
	bool previousFunnel;
	bool funnelState;
	bool previousHood;
	bool previousRMP;
	bool RMPState;
	int previousShooter;
	float m_PreviousArmStick;
	double shooterSpeedOffset;
	double shooterSpeedOffsetFender;
	double shooterSpeedOffsetFenderFunnel;
	bool previousInc;
	bool previousDec;
	CowConstants* constants;
	bool previousIntake;
	bool previousExhaust;
	Relay::Value intakeState;

public:
	CowControlBoard * cb;
	OperatorController();

	void handle();
	
};

#endif
