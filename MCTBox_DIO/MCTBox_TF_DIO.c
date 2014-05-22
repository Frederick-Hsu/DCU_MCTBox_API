/***********************************************************************************************************
 * File name		: MCTBox_TF_DIO.c
 * Description		: This file will implement the DIO-module TF step functions.
 * Creator			: XU ZAN	[HSE-OT]
 * Creation date	: Fri.	Jan. 03, 2014
 * Copyright(C)		2014	Hella Shanghai Electronics Co., Ltd.
 * All rights reserved.
 *
 ***********************************************************************************************************/

//==============================================================================
// Include files
#include <windows.h>
#include <utility.h>
#include <stdio.h>
#include "MCTBox_API_DIO.h"
#include "../user_utility.h"
#include "SUT Sequenzer Kernel API.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
static void MCTBOxAPI_TF_DIOModule_SetDoutPortHighLowHelp(void);
static void MCTBoxAPI_TF_DIOModule_GetDinPortStateHelp(void);
static void MCTBoxAPI_TF_DIOModule_ParallelGetDin24PortsStatesHelp(void);
static void MCTBoxAPI_TF_DIOModule_SetDoutPortHighLowByTokensHelp(void);
static void MCTBoxAPI_TF_DIOModule_GetDinPortStateByTokenHelp(void);

//==============================================================================
// Static functions

//==============================================================================
// Global variables
extern int __stdcall (*pfTESTER_TestFunctionSetInfoStr)(char sKey[], char sLabel[], char sValue[]);

//==============================================================================
// Test Functions implementation : 
static void MCTBOxAPI_TF_DIOModule_SetDoutPortHighLowHelp(void)
{
	int iCnt = 0;
	char sKey[32] = {0}, sLabel[32] = {0}, sValue[32] = {0};
	
	TESTER_TestFunctionRegisterHelp(1, "Digital-OUT Board ID", 
		"Edit the ID number of Digital-OUT board.\nRange: [0x00, 0xFF]");
	TESTER_TestFunctionRegisterHelp(2, "Digital-OUT port number",
		"Choose the port number of Digital-OUT board from the list box.\nRange: [1, 24]");
	TESTER_TestFunctionRegisterHelp(3, "The output state of Digital-OUT port",
		"Choose the output state of Digital-OUT port from the list box.\nRange: [LOW, HIGH]");
		 
	pfTESTER_TestFunctionSetInfoStr("Param2.Type", "", "3");
	pfTESTER_TestFunctionSetInfoStr("Param2.NumValue", "", "24");
	for (iCnt=1; iCnt<=24; iCnt++)
	{
		sprintf(sKey, "Param2.Value%d", iCnt);
		sprintf(sLabel, "%d", iCnt);
		sprintf(sValue, "%d", iCnt);
		pfTESTER_TestFunctionSetInfoStr(sKey, sLabel, sValue);
	}
	
	pfTESTER_TestFunctionSetInfoStr("Param3.Type", "", "3");
	pfTESTER_TestFunctionSetInfoStr("Param3.NumValue", "", "2");
	pfTESTER_TestFunctionSetInfoStr("Param3.Value1", "LOW", "LOW");
	pfTESTER_TestFunctionSetInfoStr("Param3.Value2", "HIGH", "HIGH");
}

void API MCTBOxAPI_TF_DIOModule_SetDoutPortHighLow(int hThisStep)
{
	int iError = 0;
	char sError[256] = {0};
	EState eDoutPortState = 0;
	
	TEST_PARAM_INT(1, iDoutBoardID);
	TEST_PARAM_INT(2, iDoutPortNr);
	TEST_PARAM_STR(3, sDoutPortState);
	
	TEST_CHECK_CBREAK;
	TEST_STEP_DELAY;
	
	if (!strcmp(sDoutPortState, "HIGH"))
		eDoutPortState = HIGH;
	else if (!strcmp(sDoutPortState, "LOW"))
		eDoutPortState = LOW;
	
	iError = MCTBoxAPI_DIOModule_SetDoutPortHighLow(iDoutBoardID, iDoutPortNr, eDoutPortState, sError);
	if (iError)
	{
		TEST_RETURN_TESTERERROR(iError, sError);
		return;
	}
	TEST_RESULT_STR("OK", "");
	return;
}
	
/******************************************************************************/
static void MCTBoxAPI_TF_DIOModule_GetDinPortStateHelp(void)
{
	char sKey[32] = {0}, sLabel[32] = {0}, sValue[32] = {0};
	
	TESTER_TestFunctionRegisterHelp(1, "Digital-IN Board ID",
		"Edit the ID number of Digital-IN Board.\nRange: [0x00, 0xFF]");
	TESTER_TestFunctionRegisterHelp(2, "Digital-IN port number",
		"Choose the port number of Digital-IN board from the list box.\nRange: [1, 24]");
	
	pfTESTER_TestFunctionSetInfoStr("Param2.Type", "", "3");
	pfTESTER_TestFunctionSetInfoStr("Param2.NumValue", "", "24");
	for (int iCnt=1; iCnt<=24; iCnt++)
	{
		sprintf(sKey, "Param2.Value%d", iCnt);
		sprintf(sLabel, "%d", iCnt);
		sprintf(sValue, "%d", iCnt);
		pfTESTER_TestFunctionSetInfoStr(sKey, sLabel, sValue);
	}
}

void API MCTBoxAPI_TF_DIOModule_GetDinPortState(int hThisStep)
{
	int iError = 0;
	char sError[256] = {0};
	EState eDinPortState = 0;
	
	TEST_PARAM_INT(1, iDinBoardID);
	TEST_PARAM_INT(2, iDinPortNr);
	
	TEST_CHECK_CBREAK;
	TEST_STEP_DELAY; 
	
	iError = MCTBoxAPI_DIOModule_QueryDinPortState(iDinPortNr, &eDinPortState, sError);
	if (iError)
	{
		TEST_RETURN_TESTERERROR(iError, sError);
		return;
	}
	if (eDinPortState == HIGH)
	{
		TEST_RESULT_STR("HIGH", "");
	}
	else if (eDinPortState == LOW)
	{
		TEST_RESULT_STR("LOW", "");
	}
	return;
}

/******************************************************************************/
static void MCTBoxAPI_TF_DIOModule_ParallelGetDin24PortsStatesHelp(void)
{
	TESTER_TestFunctionRegisterHelp(1, "Digital-IN Board ID",
		"Edit the ID number of Digital-IN Board.\nRange: [0x00, 0xFF]");
}

void API MCTBoxAPI_TF_DIOModule_ParallelGetDin24PortsStates(int hThisStep)
{	  
	int iError = 0;
	char sError[256] = "";
	EState eDin24PortsStateArray[24] = {OFF};
	char sDin24PortsStateArray[32] = {0}, sTemp[4] = {0};
	
	TEST_PARAM_INT(1, ucDinBoardID);
	
	TEST_CHECK_CBREAK;
	TEST_STEP_DELAY;
	
	iError = MCTBoxAPI_DIOModule_ParallelQueryDin24PortsState(eDin24PortsStateArray, sError);
	if (iError)
	{
		TEST_RETURN_TESTERERROR(iError, sError);
		return;
	}
	for (int i=23; i>=0; i--)
	{
		if (eDin24PortsStateArray[i] == OFF)
			sprintf(sTemp, "%s", "0");
		else if (eDin24PortsStateArray[i] == ON)
			sprintf(sTemp, "%s", "1");
		
		strcat(sDin24PortsStateArray, sTemp);
	}
	
	TEST_RESULT_STR(sDin24PortsStateArray, "");
	return;
}

/******************************************************************************/
static void MCTBoxAPI_TF_DIOModule_SetDoutPortHighLowByTokensHelp(void)
{
	TESTER_TestFunctionRegisterHelp(1, "Digital-OUT port tokens list which you want to set HIGH", 
		"Please separate these DIO port tokens by comma ','.\nOther signs or space are not supported now.");
	
	TESTER_TestFunctionRegisterHelp(2, "Digital-OUT port tokens list which you want to set LOW",
		"Please separate these DIO port tokens by comma ','.\nOther signs or space are not supported now.");
}

void API MCTBoxAPI_TF_DIOModule_SetDoutPortHighLowByTokens(int hThisStep)
{
	int iError = 0;
	char sError[256] = {0};
	char *sDioPortTokensArray2SetHigh[64] = {0}, *sDioPortTokensArray2SetLow[64] = {0};
	int iNumOfTokens2SetHigh = 0, iNumOfTokens2SetLow = 0, i = 0;
	
	TEST_PARAM_STR(1, sDioPortTokensList2SetHigh);
	TEST_PARAM_STR(2, sDioPortTokensList2SetLow);
	
	TEST_CHECK_CBREAK;
	TEST_STEP_DELAY;
	
	if ( (strlen(sDioPortTokensList2SetHigh) == 0) && 
		 (strlen(sDioPortTokensList2SetLow)  == 0) )
	{
		TEST_RETURN_TESTERERROR(-1, "Error : Parameter list is empty.");
		return;
	}
	if (0 != strlen(sDioPortTokensList2SetHigh))
	{
		ParseTokenList(sDioPortTokensList2SetHigh, sDioPortTokensArray2SetHigh, &iNumOfTokens2SetHigh);
		for (i=0; i<iNumOfTokens2SetHigh; i++)
		{
			iError = MCTBoxAPI_DIOModule_SetDoutPortHighLowByToken(sDioPortTokensArray2SetHigh[i], HIGH, sError);
			if (iError)
			{
				TEST_RETURN_TESTERERROR(iError, sError);
				return;
			}
		}
	}
	if (0 != strlen(sDioPortTokensList2SetLow))
	{
		ParseTokenList(sDioPortTokensList2SetLow, sDioPortTokensArray2SetLow, &iNumOfTokens2SetLow);
		for (i=0; i<iNumOfTokens2SetLow; i++)
		{
			iError = MCTBoxAPI_DIOModule_SetDoutPortHighLowByToken(sDioPortTokensArray2SetLow[i], LOW, sError); 
			if (iError)
			{
				TEST_RETURN_TESTERERROR(iError, sError);
				return;
			}
		}
	}
	TEST_RESULT_STR("OK", "");
	return;
}

/******************************************************************************/
static void MCTBoxAPI_TF_DIOModule_GetDinPortStateByTokenHelp(void)
{
	TESTER_TestFunctionRegisterHelp(1, "Digital-IN port token which you want to query", 
		"Note : only 1 token can be accepted and supported currently.\nNeither need the comma ',' separator nor other signs.");
}

void API MCTBoxAPI_TF_DIOModule_GetDinPortStateByToken(int hThisStep)
{
	int iError = 0;
	char sError[256] = {0};
	EState eDinPortState = 0;
	
	TEST_PARAM_STR(1, sOnly1DinPortToken);
	
	TEST_CHECK_CBREAK;
	TEST_STEP_DELAY;
	
	iError = MCTBoxAPI_DIOModule_QueryDinPortStateByToken(sOnly1DinPortToken, &eDinPortState, sError);
	if (iError)
	{
		TEST_RETURN_TESTERERROR(iError, sError);
		return;
	}
	if (eDinPortState == HIGH)
	{
		TEST_RESULT_STR("HIGH", "");
	}
	else if (eDinPortState == LOW)
	{
		TEST_RESULT_STR("LOW", "");
	}
	return;
}

/******************************************************************************/
void API MCTBoxAPI_RegisterDIOModuleTFSteps(void)
{
	TEST_REGISTER(MCTBOxAPI_TF_DIOModule_SetDoutPortHighLow);
	MCTBOxAPI_TF_DIOModule_SetDoutPortHighLowHelp();
	
	TEST_REGISTER(MCTBoxAPI_TF_DIOModule_GetDinPortState);
	MCTBoxAPI_TF_DIOModule_GetDinPortStateHelp();
	
	TEST_REGISTER(MCTBoxAPI_TF_DIOModule_ParallelGetDin24PortsStates);
	MCTBoxAPI_TF_DIOModule_ParallelGetDin24PortsStatesHelp();
	
	TEST_REGISTER(MCTBoxAPI_TF_DIOModule_SetDoutPortHighLowByTokens);
	MCTBoxAPI_TF_DIOModule_SetDoutPortHighLowByTokensHelp();
	
	TEST_REGISTER(MCTBoxAPI_TF_DIOModule_GetDinPortStateByToken);
	MCTBoxAPI_TF_DIOModule_GetDinPortStateByTokenHelp();
}
