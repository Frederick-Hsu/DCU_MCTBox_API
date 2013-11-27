/****************************************************************************************************************
 * File name	: MCTBox_communication.c
 * Description	: The MCTBox_communication module will implement the RS232 communicating & accessing between
 *				  host PC and MCTBox test instrument.
 * Creator		: XU ZAN	[HSE-OT]
 * Creation date: Wed.	Nov. 27, 2013
 * Copyright(C)		2013	Hella Shanghai Electronics Co., Ltd.
 *
 ****************************************************************************************************************/

//==============================================================================
// Include files
#include <rs232.h>
#include <stdio.h>
#include <string.h>
#include "MCTBox_communication.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
static int g_iMCTBox_ComPortNr = 0;

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Functions implementation :
int MCTBox_communication_RS232_Init(int iComPortNr, char *sARGOUT_ComError)
{
	int iErrorCode = 0, iResult = 0;
	char sError[512] = {0};
	
	// Open COM port, baud rate is fixed 38400bps
	iResult = OpenComConfig(iComPortNr, NULL, 38400, 0, 8, 1, 512, 512);	
	if (iResult >= 0)
	{
		g_iMCTBox_ComPortNr = iComPortNr;
	}
	else
	{
		iErrorCode = ReturnRS232Err();
		strcpy(sError, GetRS232ErrorString(iErrorCode));
		sprintf(sARGOUT_ComError, "Error code: %d, Error message: %s", iErrorCode, sError);
		
		return iErrorCode;
	}		
	
	iResult = SetComTime(iComPortNr, 0.05);	// Set timeout = 50ms
	if (iResult <= 0)
	{
		iErrorCode = ReturnRS232Err();
		strcpy(sError, GetRS232ErrorString(iErrorCode));
		sprintf(sARGOUT_ComError, "Error code: %d, Error message: %s", iErrorCode, sError);
		
		return iErrorCode;
	}
	return iErrorCode;
}

/******************************************************************************/
int MCTBox_communication_RS232_Exit(char *sARGOUT_ComError)
{
	int iErrorCode = 0, iResult = 0;
	char sError[512] = "";
	
	iResult = CloseCom(g_iMCTBox_ComPortNr);
	if (iResult <= 0)
	{
		iErrorCode = ReturnRS232Err();
		strcpy(sError, GetRS232ErrorString(iErrorCode));
		sprintf(sARGOUT_ComError, "Error code: %d, Error message: %s", iErrorCode, sError);
		
		return iErrorCode; 
	}
	return iErrorCode;
}

/******************************************************************************/
int MCTBox_communication_RS232_Write(char sARGIN_ComCmd2Write[], char *sARGOUT_ComError)
{
	int iError = 0;
	return iError;
}
