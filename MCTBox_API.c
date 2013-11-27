/*****************************************************************************************************************
 * File name	: MCTBox_API.c
 * Description	: To implement the MCTBox API primary functions.
 * Creator		: XU ZAN	[HSE-OT]
 * Creation date: Mon.	Nov. 25, 2013
 * Copyright(C)		2013	Hella Shanghai Electronics Co., Ltd.
 * 
 *****************************************************************************************************************/

//==============================================================================
// Include files
#include <stdio.h>
#include "MCTBox_API.h"
#include "MCTBox_API_Version.h"

#include "MCTBox_communication.h"

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
// Function implementations :
void API MCTBoxAPI_Bio(char *sMCTBox_BioInfo)
{
	char sMCTBox_Bio[] = "Hello, this is MCTBox_API. Welcome to call me!\n\
		MCTBox_API provides you plenty of functions & features to access the MCTBox testing instrument,\n\
		to implement your testing project.";
	
	sprintf(sMCTBox_BioInfo, "%s", sMCTBox_Bio);
	return;
}

/******************************************************************************/
void API MCTBoxAPI_Version(char *sMCTBox_VersionInfo)
{
	sprintf(sMCTBox_VersionInfo, "%s", CURRENT_VERSION);
	return;
}

/******************************************************************************/
int API MCTBoxAPI_Init(int iComPortNr, char *sARGOUT_ComError)
{
	int iResult = 0;														
	iResult = MCTBox_communication_RS232_Init(iComPortNr, sARGOUT_ComError);
	return iResult;
}

/******************************************************************************/
int API MCTBoxAPI_Exit(char *sARGOUT_ComError)
{
	int iResult = 0;
	iResult = MCTBox_communication_RS232_Exit(sARGOUT_ComError);
	return iResult;
}

