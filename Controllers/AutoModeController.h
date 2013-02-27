//=============================================================================
// File: AutoModeController.h
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

#ifndef _AUTO_CONTROLLER_H
#define _AUTO_CONTROLLER_H
#include "../CowRobot.h"
#include "../CowLib.h"
#include "../CowConstants.h"

using namespace CowLib;

// What type of argument?
typedef float cmdArg;

typedef enum RobotCommandNames_e
{
	CMD_NULL = 0,
	CMD_AUTOAIM,
	CMD_DRIVE,
	CMD_DRIVE_DIST,
	CMD_WAIT,
	CMD_TURN
}RobotCommandNames_e;

class RobotCommand
{
public:
	RobotCommand():
	m_Command(CMD_NULL),
	m_EncoderCount(0),
	m_Heading(0),
	m_Shooter(0),
	m_ArmSetpoint(0),
	m_Intake(0),
	m_Timeout(0)
	{
		
	}
	
	RobotCommand(RobotCommandNames_e cmd, long encoder, float heading, float shooter, float armsetpoint, float intake, float timeout):
	m_Command(cmd),
	m_EncoderCount(encoder),
	m_Heading(heading),
	m_Shooter(shooter),
	m_ArmSetpoint(armsetpoint),
	m_Intake(intake),
	m_Timeout(timeout)
	{
		
	}
	
	
	
	RobotCommandNames_e m_Command;
	long m_EncoderCount;
	float m_Heading;
	float m_Shooter;
	float m_ArmSetpoint;
	float m_Intake;
	float m_Timeout;
};

class AutoModeController
{
private:
	
	static AutoModeController *singletonInstance;
	
	Timer * timer;
	CowRobot *bot;
	deque<RobotCommand> cmdList;
	RobotCommand curCmd;
	
	bool extendArm;
	
	float previousError;
	
	// do nothing
	void doNothing();
	bool driveDistanceWithHeading(cmdArg distance, cmdArg heading);
	bool driveDistancePWithHeading(cmdArg distance, cmdArg heading);
	bool turnHeading(cmdArg heading);
public:
	AutoModeController();
	static AutoModeController* getInstance();
	
	void addCommand(RobotCommand cmd);

	bool handle();
	void reset();
	
};


#endif

