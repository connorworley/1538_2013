//=============================================================================
// File: OperatorController.cpp
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

#include "OperatorController.h"
#include "WPILib.h"
#include "../CowLib.h"
#include "../CowControlBoard.h"
#include "../CowRobot.h"
#include "../Declarations.h"
#include "../CowConstants.h"

// Constructor
// TODO: We might not need to pass in Joysticks, if they come from the ControlBoard
OperatorController::OperatorController() :
	m_PreviousArmStick(0)
{
	constants = CowConstants::getInstance();
	bot = CowRobot::GetInstance();
	cb = CowControlBoard::getInstance();
}

// call this when you want to update the bot from a driver
void OperatorController::handle()
{
	// Drive shifting
	if( cb->getButtonShifter() )
		bot->AskForShift(CowRobot::SHIFTER_STATE_HIGH);
	else
		bot->AskForShift(CowRobot::SHIFTER_STATE_LOW);
	
	bot->DriveSpeedTurn(cb->getDriveStickY(), cb->getSteeringX(), cb->getSteeringButton(FAST_TURN));
	
	bot->GetArm()->SetRaw( -cb->GetOperatorArmY());
	float armStick = -cb->GetOperatorArmY();//-cb->getOperatorY();
	if(armStick < 0.05 && armStick > -0.05)
	{
		armStick = 0;
	}
	armStick /= 100.0f;
	float armValue = armStick - (m_PreviousArmStick - armStick);
	bot->GetArm()->SetSetpoint(bot->GetArm()->GetSetpoint() + armValue);
	
	if(cb->getOperatorButton(2))
	{
		bot->GetArm()->SetSetpoint(CowConstants::getInstance()->getValueForKey("ArmGroundPosition"));
		bot->GetIntake()->SetRaw(-1);
	}
	else if(cb->getOperatorButton(1))
	{
		bot->GetIntake()->SetRaw(-1);
	}
	else if(cb->GetOperatorArmButton(6))
	{
		bot->GetIntake()->SetRaw(1);
	}
	else
	{
		bot->GetIntake()->SetRaw(0);
	}
	
	if(!cb->getOperatorButton(10))
		bot->GetShooter()->SetRaw(1);
	else 
		bot->GetShooter()->SetRaw(0);
	
	if(cb->getOperatorButton(5))
		bot->GetFeeder()->SetRaw(-1);
	else 
		bot->GetFeeder()->SetRaw(0);
	
	if(cb->getOperatorButton(8))
		bot->GetArm()->SetSetpoint(CowConstants::getInstance()->getValueForKey("ArmHighPosition"));
	if(cb->getOperatorButton(9))
		bot->GetArm()->SetSetpoint(CowConstants::getInstance()->getValueForKey("ArmMidPosition"));
	if(cb->getOperatorButton(7))
		bot->GetArm()->SetSetpoint(CowConstants::getInstance()->getValueForKey("ArmLowPosition"));
	if(cb->getSteeringButton(3))
		bot->GetArm()->SetSetpoint(CowConstants::getInstance()->getValueForKey("ArmGroundPosition") - 0.19);
	if(cb->getSteeringButton(1))
		bot->GetArm()->SetSetpoint(CowConstants::getInstance()->getValueForKey("ArmApproachHang"));
	if(cb->getSteeringButton(4))
		bot->GetArm()->SetSetpoint(CowConstants::getInstance()->getValueForKey("ArmGroundPosition"));
	if(cb->getDriveButton(1))
		bot->GetArm()->SetSetpoint(CowConstants::getInstance()->getValueForKey("ArmStartingPosition"));
	
	if(!cb->getOperatorButton(3) && !cb->getOperatorButton(4))
		bot->GetArm()->Lock(0);
	else
		bot->GetArm()->Lock(1);
}

