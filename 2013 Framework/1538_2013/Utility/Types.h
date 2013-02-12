#ifndef TYPES_H_
#define TYPES_H_

typedef struct {
	double driveLeft;
	double driveRight;
	double armPos; // Potentiometer value of arm
	double gyroAngle;
	double intakeRoller;
	double shooterRoller;
	double shooterOutput;
} RobotState;

#endif
