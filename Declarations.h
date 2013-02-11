//=============================================================================
// File: Declarations.h
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

#ifndef DECLARATIONS_H_
#define DECLARATIONS_H_

#define THROTTLE_CENTER_VALUE 1.605
#define WHEEL_CENTER_VALUE 1.536

// PWM PORTS
#define LEFT_DRIVE				1
#define RIGHT_DRIVE				2
#define ARM_A					3
#define ARM_B					4
#define SHOOTER_A				5
#define SHOOTER_B				6
#define FEEDER_A				7
#define FEEDER_B				8
#define INTAKE_A				9
#define INTAKE_B				10


//DIGITAL IN
#define LEFT_ENCODER_A_CHAN		1
#define LEFT_ENCODER_B_CHAN		2


//RELAY
#define CHUTE_RELAY_A			4
#define CHUTE_RELAY_B			5
#define COMPRESSOR_RELAY 		3
#define INTAKE_RELAY_A			1
#define INTAKE_RELAY_B			2

//SOLENOID
#define SHIFTER_SOLENOID_CHAN	1
#define ARMLOCK_SOLENOID_CHAN	2


//ANALOG IN
#define GYRO_CHAN				1
#define ARM_POT_CHAN			2

// Driver Controller
#define PORT_THROTTLE	1
#define PORT_WHEEL		2


#endif