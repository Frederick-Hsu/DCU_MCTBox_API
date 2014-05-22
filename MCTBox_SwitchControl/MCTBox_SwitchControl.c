/********************************************************************************************************
 * File name		: MCTBox_SwitchControl.c
 * Description		: To implement the API functions for accessing the SwitchControl module of MCTBox instrument.
 * Creator			: XU ZAN
 * Creation date	: Fri.	Dec. 27, 2013
 * Copyright(C)		2013	Hella Shanghai Electronics Co., Ltd.
 * All rights reserved.
 *
 ********************************************************************************************************/

//==============================================================================
// Include files
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "../MCTBox_API_SwitchControl.h"
#include "../MCTBox_API.h"

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
// Functions implementation :
int API MCTBoxAPI_SwitchModule_OpenCloseSwitch(BYTE 	ucSwitchBoardID, 
											   UINT 	uiSwitchChannelNr, 
											   EState 	eSwitchState,
											   char 	*sErrorMesg)
{
	int iError = 0;
	char sSwitchCtrlCmd[256] = {0}, sSwitchCtrlResponse[256] = {0}, sError[512] = {0};
	
	if (eSwitchState == ON)
	{
		sprintf(sSwitchCtrlCmd, "$SWITch 0x%02X:%02d ON!", ucSwitchBoardID, uiSwitchChannelNr);
	}
	else if (eSwitchState == OFF)
	{
		sprintf(sSwitchCtrlCmd, "$SWITch 0x%02X:%02d OFF!", ucSwitchBoardID, uiSwitchChannelNr);
	}
	
	iError = MCTBoxAPI_Request(sSwitchCtrlCmd, sSwitchCtrlResponse);
	if (strlen(sSwitchCtrlResponse) == 0)
	{
		sprintf(sErrorMesg, "%s", "MCTBox has not responded to the switch control.");
		return -100;
	}
	if (iError)
	{
		iError = MCTBoxAPI_IsCommunicationError(sError);
		sprintf(sErrorMesg, "%s", sError);
		return iError;
	}
#if 0
	iError = MCTBoxAPI_IsExecutionError(sError);
	if (iError != 0)
	{
		sprintf(sErrorMesg, "%s", sError);
	}
#endif
	
	return iError;
}

/******************************************************************************/
int API MCTBoxAPI_SwitchModule_ClearAllSwitches(BYTE ucSwitchBoardID, char *sErrorMesg)
{
	int iError = 0;
	char sError[512] = {0};
	char sSwitchCtrlCmd[256] = {0}, sSwitchCtrlResponse[256] = {0};
	
	sprintf(sSwitchCtrlCmd, "$SWITch 0x%02X:000000000000000000000000!", ucSwitchBoardID);
	iError = MCTBoxAPI_Request(sSwitchCtrlCmd, sSwitchCtrlResponse);
	if (iError)
	{
		iError = MCTBoxAPI_IsCommunicationError(sError);
		sprintf(sErrorMesg, "%s", sError);
	}
#if 0
	iError = MCTBoxAPI_IsExecutionError(sError);
	if (iError!= 0)
	{
		sprintf(sErrorMesg, "%s", sError);
	}
#endif
	
	return iError;
}

/******************************************************************************/
int API MCTBoxAPI_SwitchModule_SetAllSwitches(BYTE ucSwitchBoardID, char *sErrorMesg)
{
	int iError = 0;
	char sError[512] = {0};
	char sSwitchCtrlCmd[256] = {0}, sSwitchCtrlResponse[256] = {0};
	
	sprintf(sSwitchCtrlCmd, "$SWITch 0x%02X:111111111111111111111111!", ucSwitchBoardID);
	iError = MCTBoxAPI_Request(sSwitchCtrlCmd, sSwitchCtrlResponse);
	if (iError)
	{
		iError = MCTBoxAPI_IsCommunicationError(sError);
		sprintf(sErrorMesg, "%s", sError);
	}
#if 0
	iError = MCTBoxAPI_IsExecutionError(sError);
	if (iError!= 0)
	{
		sprintf(sErrorMesg, "%s", sError);
	}
#endif
	
	return iError;
}

/******************************************************************************/
int API MCTBoxAPI_SwitchModule_OpenCloseMultiSwitches(PSwitch_t ptSwitch1, ...)
{
	int iError = 0;
	char sError[512] = {0}, sSwitchCtrlCmd[512] = "$", sTempSwitchCtrlCmd[64] = {0}, sSwitchCtrlResponse[512] = {0};
	
	va_list marker;
	PSwitch_t next = ptSwitch1;
	va_start(marker, ptSwitch1);
	while (next != NULL)
	{
		if (next->eSwitchState == ON)
			sprintf(sTempSwitchCtrlCmd, "SWITch 0x%02X:%02d ON", next->ucSwitchBoardID, next->uiSwitchChannelNr);
		else if (next->eSwitchState == OFF)
			sprintf(sTempSwitchCtrlCmd, "SWITch 0x%02X:%02d OFF", next->ucSwitchBoardID, next->uiSwitchChannelNr);
		
		strcat(sSwitchCtrlCmd, sTempSwitchCtrlCmd);
		
		next = va_arg(marker, PSwitch_t);
		if (next != NULL)
		{
			strcat(sSwitchCtrlCmd, ";");
		}
	}
	va_end(marker);
	strcat(sSwitchCtrlCmd, "!");
	
	iError = MCTBoxAPI_Request(sSwitchCtrlCmd, sSwitchCtrlResponse);
#if 0
	iError = MCTBoxAPI_IsExecutionError(sError);
#endif
	
	return iError;
}
