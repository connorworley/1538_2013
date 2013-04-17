//=============================================================================
// File: CowLib.cpp
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

#include "CowLib.h"

extern DriverStationLCD * m_dsLCD;


float CowLib::AnalogInScale(float oldx, double center)
{
	const double min = 0 - center;
	const double max = 3.25 - center;
	const double deadband = .05;
	
	float x = oldx - center;

	if ((x <= (center*deadband)) && (x >= (-1*center*deadband)))
	{
		x = 0;
	}
	else if (x > (max - center*deadband))
	{
		x = 1;
	}
	else if (x < (min + center*deadband))
	{
		x = -1;
	}
	else if (x > 0)
	{
		x = ((x - (center*deadband))/((max - center*deadband) - (center
				*deadband)));
	}
	else if (x < 0)
	{
		x = ((x + (center*deadband))/(-1*((min + center*deadband) + (center
				*deadband))));
	}
	return x;
}

void CowLib::PrintToLCD::print(bool enabled, int lineNumber, int startChar, const char * text){
	PrintToLCD::print(enabled, lineNumber, startChar, text, 0.0, 0.0);
}
void CowLib::PrintToLCD::print(bool enabled, int lineNumber, int startChar, const char * text, float var1){
	PrintToLCD::print(enabled, lineNumber, startChar, text, var1, 0.0);
}	
void CowLib::PrintToLCD::print(bool enabled, int lineNumber, int startChar, const char * text, float var1, float var2){
	if(!enabled)
		return;
	switch(lineNumber){
		case 1:
			m_dsLCD->Printf(DriverStationLCD::kUser_Line1,startChar,text, var1, var2);
			break;
		case 2:
			m_dsLCD->Printf(DriverStationLCD::kUser_Line2,startChar,text, var1, var2);	
			break;
		case 3:
			m_dsLCD->Printf(DriverStationLCD::kUser_Line3,startChar,text, var1, var2);	
			break;
		case 4:
			m_dsLCD->Printf(DriverStationLCD::kUser_Line4,startChar,text, var1, var2);				
			break;
		case 5:
			m_dsLCD->Printf(DriverStationLCD::kUser_Line5,startChar,text, var1, var2);
			break;
		case 6:
			m_dsLCD->Printf(DriverStationLCD::kUser_Line6,startChar,text, var1, var2);				
			break;
	}
}
void CowLib::PrintToLCD::finalizeUpdate(){
		m_dsLCD->UpdateLCD();
		
}

float CowLib::LimitMix(float value, float maxValue)
{
	float limited_value = 0;
	
	if(value < -maxValue)
	{
		limited_value = -maxValue;
	}
	else if(value > maxValue)
	{
		limited_value = maxValue;
	}
	else
	{
		limited_value = value;
	}
	
	return limited_value;
}

float CowLib::LimitMix(float value)
{
	float limited_value = 0;
	
	if(value < -1.0)
	{
		limited_value = -1.0;
	}
	else if(value > 1.0)
	{
		limited_value = 1.0;
	}
	else
	{
		limited_value = value;
	}
	
	return limited_value;
}
