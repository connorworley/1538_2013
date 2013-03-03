//=============================================================================
// File: AutoModeController.cpp
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

#include "AutoModeController.h"
#include "../CowRobot.h"
#include "../CowConstants.h"
#include "../accelFilter.h"
#include <math.h>

AutoModeController* AutoModeController::singletonInstance = NULL;

/// Creates (if needed) and returns a sidngleton Control Board instance
AutoModeController* AutoModeController::getInstance()
{
	if( singletonInstance == NULL)
		singletonInstance = new AutoModeController(); 
	return singletonInstance;
}

AutoModeController::AutoModeController()
:
	previousError(0)
{
	bot = CowRobot::GetInstance();
	timer = new Timer();
	curCmd = RobotCommand();
	
	extendArm = false;
	
	timer->Start();
	
	reset();
}

Relay::Value toRelayValue(float val)
{
	if(val == 1.0)
		return Relay::kForward;
	else if(val == -1.0)
		return Relay::kReverse;
	else
		return Relay::kOff;
}

void AutoModeController::addCommand(RobotCommand cmd)
{
	cmdList.push_back(cmd);
}

void AutoModeController::reset()
{
	//CowConstants * rc = CowConstants::getInstance();
	//bot->GetGyro()->Reset();
	//bot->GetEncoder()->Reset();

	cmdList.clear();
	curCmd = RobotCommand();
	bot->AskForShift(CowRobot::SHIFTER_STATE_HIGH);
}

void AutoModeController::handle()
{
	bool result = false;
	bool thisIsNull = false;
	
	// Run the command
	switch(curCmd.m_Command)
	{
		case CMD_DRIVE_DIST:
			result = driveDistanceWithHeading(curCmd.m_EncoderCount, curCmd.m_Heading, curCmd.m_Throttle);
			bot->GetShooter()->SetRaw(curCmd.m_Shooter);
			bot->GetFeeder()->SetRaw(curCmd.m_Feeder);
			bot->GetIntake()->SetRaw(curCmd.m_Intake);
			bot->GetArm()->Lock(true);
			bot->GetArm()->SetState(curCmd.m_ArmSetpoint);
			break;
		case CMD_DRIVE_HOLD_DIST:
			result = driveDistanceHoldWithHeading(curCmd.m_EncoderCount, curCmd.m_Heading, curCmd.m_Throttle);
			bot->GetShooter()->SetRaw(curCmd.m_Shooter);
			bot->GetFeeder()->SetRaw(curCmd.m_Feeder);
			bot->GetIntake()->SetRaw(curCmd.m_Intake);
			bot->GetArm()->Lock(true);
			bot->GetArm()->SetState(curCmd.m_ArmSetpoint);
			break;
		case CMD_TURN:
			result = turnHeading(curCmd.m_Heading);
			bot->AskForShift(CowRobot::SHIFTER_STATE_LOW);
			bot->GetEncoder()->Reset();
			bot->GetShooter()->SetRaw(curCmd.m_Shooter);
			bot->GetFeeder()->SetRaw(curCmd.m_Feeder);
			bot->GetIntake()->SetRaw(curCmd.m_Intake);
			bot->GetArm()->Lock(true);
			bot->GetArm()->SetState(curCmd.m_ArmSetpoint);

			break;
			
		case CMD_SHOOTINPLACE:
			result = driveDistanceHoldWithHeading(curCmd.m_EncoderCount, curCmd.m_Heading, curCmd.m_Throttle);
			bot->GetShooter()->SetRaw(curCmd.m_Shooter);
			bot->GetFeeder()->SetRaw(curCmd.m_Feeder);
			bot->GetIntake()->SetRaw(curCmd.m_Intake);
			bot->GetArm()->Lock(true);
			bot->GetArm()->SetState(curCmd.m_ArmSetpoint);
			
			if(bot->GetFeeder()->GetFiredDisks() == curCmd.m_NumberOfDisk)
			{
				result = true;
				cout << "Shot number of disk " << curCmd.m_NumberOfDisk << endl;
			}
			else
				result = false;
			break;
			
		case CMD_ARM:
			result = false;
			bot->GetShooter()->SetRaw(curCmd.m_Shooter);
			bot->GetFeeder()->SetRaw(curCmd.m_Feeder);
			bot->GetIntake()->SetRaw(curCmd.m_Intake);
			bot->GetArm()->Lock(true);
			bot->GetArm()->SetState(curCmd.m_ArmSetpoint);
			break;
		case CMD_NULL:
			thisIsNull = true;
			doNothing();
			
			result = true;
			break;
			
		case CMD_WAIT:
			doNothing();
			
			result = false;
			break;
		
		default :
			doNothing();
			result = true;
			break;
	}
	
	// Check if this command is done
	if(result == true || thisIsNull || timer->Get() > curCmd.m_Timeout){
		// This command is done, go get the next one
		if(cmdList.size() > 0 )
		{
			curCmd = cmdList.front();
			cmdList.pop_front();
			timer->Reset();
		}
		else curCmd = RobotCommand();
	}
}

// Drive Functions
void AutoModeController::doNothing()
{
	bot->DriveLeftRight(0,0);
	bot->GetShooter()->SetRaw(0);
	bot->GetFeeder()->SetRaw(0);
	bot->GetIntake()->SetRaw(0);
	//bot->getArm()->SetMotor(0);
	//bot->getArm()->
}

bool AutoModeController::turnHeading(float heading)
{
	float pGain = CowConstants::getInstance()->getValueForKey("turnP");
	
	float currentHeading = bot->GetGyro()->GetAngle();
	float turn = heading - currentHeading;
	
	bot->GetEncoder()->Reset();
	
	previousError = turn;
		
	float output = (LimitMix(turn) * pGain) + (LimitMix(previousError - turn) * CowConstants::getInstance()->getValueForKey("turnD"));
	
	bot->DriveLeftRight(output, -output);
	
	if((currentHeading < heading + 1 && currentHeading > heading - 1))
	{
		printf("Done with distance\r\n");
		return false;
	}	
	else
		return false;
}

bool AutoModeController::driveDistanceWithHeading(float distance, float heading, float throttle)
{
	float distanceP = distance - bot->GetEncoder()->GetDistance();
	float currentDistance = bot->GetEncoder()->GetDistance();
	float currentHeading = bot->GetGyro()->GetAngle();
	//float currentHeading = 0;
	float turn = heading - bot->GetGyro()->GetAngle();
		
	distanceP *= 0.03;
	turn /= 100.0;
	
	distanceP = LimitMix(-distanceP)* 0.5;
	turn = LimitMix(turn*9);
	//printf("%f, %f, %f\r\n", distanceP, bot->GetEncoder()->GetDistance(), turn);
		
	bot->DriveSpeedTurn(distanceP, turn , true);
//	bot->driveSpeedTurn(LimitMix(-distanceP) * 1, 0, true);

	if((currentDistance < distance + 0.25 && currentDistance > distance - 0.25) &&
		bot->GetEncoder()->GetRate() < 15 &&
	   (currentHeading < heading + 1 && currentHeading > heading -1))
	{
		printf("Done with distance\r\n");
		return true;
	}	
	else
		return false;
}

bool AutoModeController::driveDistanceHoldWithHeading(float distance, float heading, float throttle)
{
	float distanceP = distance - bot->GetEncoder()->GetDistance();
	float currentDistance = bot->GetEncoder()->GetDistance();
	float currentHeading = bot->GetGyro()->GetAngle();
	//float currentHeading = 0;
	float turn = heading - bot->GetGyro()->GetAngle();
		
	distanceP *= 0.03;
	turn /= 100.0;
	
	distanceP = LimitMix(-distanceP) * throttle;
	turn = LimitMix(turn*9);
	//printf("%f, %f, %f\r\n", throttle, bot->GetEncoder()->GetDistance(), turn);
		
	bot->DriveSpeedTurn(distanceP, turn , true);
	return false;
}



