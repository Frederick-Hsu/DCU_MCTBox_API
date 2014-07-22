/*******************************************************************************************
 * File name		: MCTBox_PWM.c
 * Description		: To implement the API functions to access the PWM module of MCTBox.
 * Creator			: XU ZAN	[HSE-OT]
 * Creation date	: Thur.		June 26, 2014
 * Copyright(C)		2014	Hella Shanghai Electronics Co., Ltd.
 * All rights reserved.
 *
 *******************************************************************************************/

//==============================================================================
// Include files
#include "..\MCTBox_API_PWM.h"
#include "..\MCTBox_API.h"

#include <stdio.h>

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions
int API MCTBoxAPI_PWMModule_ConfigPwmOutCh1(int 	iFreq,			// unit : Hz
											float	fDutyCycle,		// range : [0, 1]
											float	fVoltage,		// unit : volt
											char	*sError)
{
	int iError = 0;
	char sCommand[256] = {0}, sRequest[256] = {0},
		 sFreq[32] = {0}, sDuty[32] = {0}, sVolt[32] = {0};
	
	sprintf(sFreq, "FREQ %d", iFreq);
	sprintf(sVolt, "VOLT %.02f", fVoltage);
	if ((fDutyCycle < 0.00) || (fDutyCycle > 1.00))
	{
		sprintf(sError, "%s", "The duty cycle value you entered is wrong.");
		return -1;
	}
	sprintf(sDuty, "DUTY %.01f%", fDutyCycle*100);
	sprintf(sCommand, "$PWMO CONF:OUT1:%s:%s:%s!", sFreq, sDuty, sVolt);
	
	iError = MCTBoxAPI_Request(sCommand, sRequest);
	if (iError)
	{
		iError = MCTBoxAPI_IsCommunicationError(sError);
		return iError;
	}
#if 0
	iError = MCTBoxAPI_IsExecutionError(sError);
#endif		
	
	return iError;
}

int API MCTBoxAPI_PWMModule_StopPwmOutCh1(void)
{
	int iError = 0;
	char sError[256] = {0};
	char sCommand[256] = {0};
	
	return iError;
}


int API MCTBoxAPI_PWMModule_ConfigPwmOutCh2(int 	iFreq,			// unit : Hz
											float	fDutyCycle,		// range : [0, 1]
											float	fVoltage,		// unit : volt
											char	*sError)
{
		int iError = 0;
	char sCommand[256] = {0}, sRequest[256] = {0},
		 sFreq[32] = {0}, sDuty[32] = {0}, sVolt[32] = {0};
	
	sprintf(sFreq, "FREQ %d", iFreq);
	sprintf(sVolt, "VOLT %.02f", fVoltage);
	if ((fDutyCycle < 0.00) || (fDutyCycle > 1.00))
	{
		sprintf(sError, "%s", "The duty cycle value you entered is wrong.");
		return -1;
	}
	sprintf(sDuty, "DUTY %.01f%", fDutyCycle*100);
	sprintf(sCommand, "$PWMO CONF:OUT2:%s:%s:%s!", sFreq, sDuty, sVolt);
	
	iError = MCTBoxAPI_Request(sCommand, sRequest);
	if (iError)
	{
		iError = MCTBoxAPI_IsCommunicationError(sError);
		return iError;
	}
#if 0
	iError = MCTBoxAPI_IsExecutionError(sError);
#endif		
	
	return iError;
}
