/********************************************************************************************************
 * File name		: MCTBox_DIO.c
 * Description		: To implement the API functions for accessing the DIO module of MCTBox instrument.
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
#include <stdlib.h>
#include "../MCTBox_API_DIO.h"
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
// Global functions
int API MCTBoxAPI_DIOModule_SetDoutPortHighLow(BYTE 	ucDoutBoardID,			  
											   UINT 	uiDoutPortNr,
											   EState 	eDoutPortState,
											   char 	*sErrorMesg)
{
	int iResult = 0;
	char sDoutCmd[256] = {0}, sDoutResponse[256] = {0}, sError[512] = {0};
	
	if (eDoutPortState == HIGH)
	{
		sprintf(sDoutCmd, "$DOUT 0x%02X:%02d HIGH!", ucDoutBoardID, uiDoutPortNr);
	}
	else if (eDoutPortState == LOW)
	{
		sprintf(sDoutCmd, "$DOUT 0x%02X:%02d LOW!", ucDoutBoardID, uiDoutPortNr);
	}
	iResult = MCTBoxAPI_Request(sDoutCmd, sDoutResponse);
	if (iResult)
	{
		iResult = MCTBoxAPI_IsCommunicationError(sError);
		sprintf(sErrorMesg, "%s", sError);
		return iResult;
	}
#if 0
	iResult = MCTBoxAPI_IsExecutionError(sError);
	if (iResult != 0)
	{
		sprintf(sErrorMesg, "%s", sError);
	}
#endif
	
	return iResult;
}

int API MCTBoxAPI_DIOModule_QueryDinPortState(UINT 		uiDinPortNr,
											  EState 	*eDinPortState,
											  char 		*sErrorMesg)
{
	int iResult = 0;
	char sDinCmd[256] = {0}, sDinResponse[256] = {0}, sError[512] = {0};
	char *sState = "", sStateResult[16] = {0};
	
	sprintf(sDinCmd, "$DIN %02d:STATe?!", uiDinPortNr);
	// sprintf(sDinCmd, "$DIN 0x%02X:%02d STATe?!", ucDinBoardID, uiDinPortNr);
	iResult = MCTBoxAPI_Request(sDinCmd, sDinResponse);
	/* 
	 * Check the RS232 communication error
	 */
	if (iResult)
	{
		iResult = MCTBoxAPI_IsCommunicationError(sError);	
		sprintf(sErrorMesg, "%s", sError);
		return iResult;
	}
	/*
	 * Parse the MCU response, get the state
	 */
	sState = strstr(sDinResponse, "State ");
	if (!sState)
	{
		/*
		 * Check the MCU execution error
		 */
		#if 0
			iResult = MCTBoxAPI_IsExecutionError(sError);
			if (iResult != 0)
			{
				sprintf(sErrorMesg, "%s", sError);
				return iResult;
			}
		#else
			sprintf(sErrorMesg, "%s", "MCTBox not response.");
			return -10;		// No response
		#endif
	}
	strncpy(sStateResult, sState+6, strlen(sState)-1-6);
	if (!stricmp(sStateResult, "LOW"))
	{
		*eDinPortState = LOW;
	}
	else if (!stricmp(sStateResult, "HIGH"))
	{
		*eDinPortState = HIGH;
	}
	else
	{
		sprintf(sErrorMesg, "%s", "Unknown Digital-IN state");
		return -1;	// Unknown DIN state
	}									
	
	return iResult;
}

int API MCTBoxAPI_DIOModule_ParallelQueryDin24PortsState(EState eDin24PortsState[24],	// 24 ports' state
														 char 	*sErrorMesg)
{
	int iResult = 0;
	char sDinCmd[256] = {0}, sDinResponse[256] = {0}, sError[256] = {0};
	char *sState = "", sDin24PortsState[32] = "", sDinSinglePortState[4] = {0};
	
	sprintf(sDinCmd, "%s", "$DIN *:STATe?!");
	// sprintf(sDinCmd, "$DIN 0x%02X:* STATe?!", ucDinBoardID);
	iResult = MCTBoxAPI_Request(sDinCmd, sDinResponse);
	if (iResult)
	{
		iResult = MCTBoxAPI_IsCommunicationError(sError);
		sprintf(sErrorMesg, "%s", sError);
		return iResult;
	}
	   
	sState = strstr(sDinResponse, "State ");
	if (!sState)
	{
		sprintf(sErrorMesg, "%s", "MCTBox not response.");
		return -10;
	}
	strncpy(sDin24PortsState, sState+6, 24);
	
	for (int i=0; i<24; i++)
	{
		strncpy(sDinSinglePortState, sDin24PortsState+i, 1);
		eDin24PortsState[23-i] = atoi(sDinSinglePortState);
	}
	
	return iResult;
}
