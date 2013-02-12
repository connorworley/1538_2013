//=============================================================================
// File: OperatorController.cpp
//
// COPYRIGHT 2012 Robotics Alliance of the West Coast(Cow)
// All rights reserved.  Cow proprietary and confidential.
//             
// The party receiving this software directly from Cow (the "Recipient")
// may use this software and make copies thereof as reasonably necessary solely
// for the purposes set forth in the agreement between the Recipient and
// Cow(the "Agreement").  The software may be used in source code form
// solely by the Recipient's employees/volunteers.  The Recipient shall have 
// no right to sublicense, assign, transfer or otherwise provide the source
// code to any third party. Subject to the terms and conditions set forth in
// the Agreement, this software, in binary form only, may be distributed by
// the Recipient to its users. Cow retains all ownership rights in and to
// the software.
//
// This notice shall supercede any other notices contained within the software.
//=============================================================================
#include "OperatorController.h"
#include "WPILib.h"
#include "../CowLib.h"
#include "../CowControlBoard.h"
#include "../CowRobot.h"
#include "../Declarations.h"
#include "../CowConstants.h"

// Constructor
// TODO: We might not need to pass in Joysticks, if they come from the ControlBoard
OperatorController::OperatorController()
{
	constants = CowConstants::getInstance();
	bot = CowRobot::GetInstance();
	cb = CowControlBoard::getInstance();
}

// call this when you want to update the bot from a driver
void OperatorController::handle()
{
//	// Drive shifting
//	if( cb->getButtonShifter() )
//		bot->AskForShift(CowRobot::SHIFTER_STATE_HIGH);
//	else
//		bot->AskForShift(CowRobot::SHIFTER_STATE_LOW);
	
	//bot->DriveSpeedTurn(cb->getDriveStickY(), cb->getSteeringX(), cb->getSteeringButton(FAST_TURN));
	bot->GetArm()->SetRaw(-cb->getDriveStickY());
	
	if(cb->getOperatorButton(2))
	{
		bot->GetIntake()->SetRaw(-1);
	} 
	else 
	{
		bot->GetIntake()->SetRaw(0);
	}
	
	if(!cb->getOperatorButton(10))
	{
		bot->GetShooter()->SetRaw(1);
	} 
	else 
	{
		bot->GetShooter()->SetRaw(0);
	}
	
	if(cb->getOperatorButton(5))
	{
		bot->GetFeeder()->SetRaw(-0.5);
	} 
	else 
	{
		bot->GetFeeder()->SetRaw(0);
	}
}

