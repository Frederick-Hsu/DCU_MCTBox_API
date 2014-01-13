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
	int iError = 0, iComWrtLen = 0;
	char sError[256] = "";
	
	FlushInQ(g_iMCTBox_ComPortNr);
	FlushOutQ(g_iMCTBox_ComPortNr);
	
	iComWrtLen = ComWrt(g_iMCTBox_ComPortNr, sARGIN_ComCmd2Write, strlen(sARGIN_ComCmd2Write));
	if (iComWrtLen != strlen(sARGIN_ComCmd2Write))
	{
		iError = ReturnRS232Err();
		strcpy(sError, GetRS232ErrorString(iError));
		sprintf(sARGOUT_ComError, "Error code: %d, Error message: %s", iError, sError);
		return iError;
	}
	
	return iComWrtLen;
}

/******************************************************************************/
int MCTBox_communication_RS232_Read(char *sARGOUT_ComResponse, char *sARGOUT_ComError)
{
	int iResult = 0, iCnt = 0, iError = 0;
	char sResponse[256] = "", sError[256] = "";
	
#if 0
	do
	{
		iResult = ComRd(g_iMCTBox_ComPortNr, sResponse+iCnt, 1);
		if (iResult < 0)	// Eror occurs
			break;
		iCnt++;
	}
	while (sResponse[iCnt-1] != 0);	// Check until the NULL terminate char.
#else
	iResult = ComRd(g_iMCTBox_ComPortNr, sResponse, 256);
#endif
	if (iResult < 0)
	{  
		iError = ReturnRS232Err();
		strcpy(sError, GetRS232ErrorString(iError));
		sprintf(sARGOUT_ComError, "Error code: %d, Error message: %s", iError, sError);
		
		iResult = iError;
	}
	sprintf(sARGOUT_ComResponse, "%s", sResponse);
	
	return iResult;
}

/******************************************************************************/
int MCTBox_communication_RS232_Query(char sARGIN_ComCmd2Write[], char *sARGOUT_ComResponse, char *sARGOUT_ComError)
{
	int iResult = 0, iLen = 0;
	char sError[256] = "", sResponse[256] = "";
	
	iLen = MCTBox_communication_RS232_Write(sARGIN_ComCmd2Write, sError);
	if (0 != strlen(sError))
	{
		sprintf(sARGOUT_ComError, "%s", sError);
		return iLen;	// Negative error code
	}
	iLen = MCTBox_communication_RS232_Read(sResponse, sError);
	if (0 != strlen(sError))
	{
		sprintf(sARGOUT_ComError, "%s", sError);
		return iLen;	// Negative error code
	}
	sprintf(sARGOUT_ComResponse, "%s", sResponse);	// Output the response
	
	return iResult;
}
