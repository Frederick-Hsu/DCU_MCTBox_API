/*********************************************************************************************************************
 * File name		: MCTBox_TF_SwitchControl.c
 * Description		: To exclusively implement the Test Step Functions for SwitchControl module.
 * Creator			: XU ZAN	[HSE-OT]
 * Creation date	: Sun.	Dec. 29, 2013
 * Copyright(C)		2013	Hella Shanghai Electronics Co., Ltd.
 *
 *********************************************************************************************************************/

//==============================================================================
// Include files
#include <stdio.h>
#include <windows.h>
#include <utility.h>
#include "../MCTBox_API_SwitchControl.h"
#include "../user_utility.h"

#include "SUT Sequenzer Kernel API.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions
static void MCTBoxAPI_TF_Switch_OpenCloseSwitchHelp(void);
static void MCTBoxAPI_TF_SwitchModule_ClearAllSwitchesHelp(void);
static void MCTBoxAPI_TF_SwitchModule_SetResetSwitchHelp(void);

//==============================================================================
// Global variables
extern int __stdcall (*pfTESTER_TestFunctionSetInfoStr)(char sKey[], char sLabel[], char sValue[]);

//==============================================================================
// Test Functions implementation :
static void MCTBoxAPI_TF_SwitchModule_OpenCloseSwitchHelp(void)
{
	int i = 0;
	char sParamKey[64] = {0}, sParamLabel[64] = {0}, sParamValue[64] = {0};
	
	TESTER_TestFunctionRegisterHelp(1, "Switch Board ID", 
		"Edit the ID of switch matrix board.\nRange : [0x00, 0xFF]");
	TESTER_TestFunctionRegisterHelp(2, "Channel number of Switch matrix board",
		"Choose the channel number from the list.\nRange : [1, 24]");
	TESTER_TestFunctionRegisterHelp(3, "Open / Close state",
		"Choose the state from the list.");
	
	pfTESTER_TestFunctionSetInfoStr("Param2.Type", "", "3");
	pfTESTER_TestFunctionSetInfoStr("Param2.NumValue", "", "24");
	for (i=1; i<=24; i++)
	{
		sprintf(sParamKey, "Param2.Value%d", i);
		sprintf(sParamLabel, "%d", i);
		sprintf(sParamValue, "%d", i);
		pfTESTER_TestFunctionSetInfoStr(sParamKey, sParamLabel, sParamValue);
	}
	
	pfTESTER_TestFunctionSetInfoStr("Param3.Type", "", "3");
	pfTESTER_TestFunctionSetInfoStr("Param3.NumValue", "", "2");
	pfTESTER_TestFunctionSetInfoStr("Param3.Value1", "OPEN", "OPEN");
	pfTESTER_TestFunctionSetInfoStr("Param3.Value2", "CLOSE", "CLOSE");
}

void API MCTBoxAPI_TF_SwitchModule_OpenCloseSwitch(int hThisStep)
{
	int iError = 0;
	char sError[512] = {0};
	EState eSwitchState = OFF;
	
	TEST_PARAM_INT(1, byteSwitchBoardID);
	TEST_PARAM_INT(2, uiSwitchChannelNr);
	TEST_PARAM_STR(3, sSwitchState);
	
	TEST_CHECK_CBREAK;
	TEST_STEP_DELAY;
	
	if (!stricmp(sSwitchState, "OPEN"))
		eSwitchState = OPEN;
	else if (!stricmp(sSwitchState, "CLOSE"))
		eSwitchState = CLOSE;
	
	iError = MCTBoxAPI_SwitchModule_OpenCloseSwitch(byteSwitchBoardID, uiSwitchChannelNr, eSwitchState, sError);
	if (iError)
	{
		TEST_RETURN_TESTERERROR(iError, sError);
	}
	else
	{
		TEST_RESULT_STR("OK", "");
	}
	return;
}

/******************************************************************************/
static void MCTBoxAPI_TF_SwitchModule_ClearAllSwitchesHelp(void)
{
	TESTER_TestFunctionRegisterHelp(1, "Switch Board ID", 
		"Edit the ID of switch matrix board.\nRange : [0x00, 0xFF]");
}

void API MCTBoxAPI_TF_SwitchModule_ClearAllSwitches(int hThisStep)
{
	int iError = 0;
	char sError[512] = {0};
	
	TEST_PARAM_INT(1, byteSwitchBoardID);
	
	TEST_CHECK_CBREAK;
	TEST_STEP_DELAY;
	
	iError = MCTBoxAPI_SwitchModule_ClearAllSwitches(byteSwitchBoardID, sError);
	if (iError)
	{
		TEST_RETURN_TESTERERROR(iError, sError);
	}
	else
	{
		TEST_RESULT_STR("OK", "");
	}
	return;
}

/******************************************************************************/
void API MCTBoxAPI_TF_SwitchModule_SetAllSwitches(int hThisStep)
{
	int iError = 0;
	char sError[512] = {0};
	
	TEST_PARAM_INT(1, byteSwitchBoardID);
	
	TEST_CHECK_CBREAK;
	TEST_STEP_DELAY;
	
	iError = MCTBoxAPI_SwitchModule_SetAllSwitches(byteSwitchBoardID, sError);
	if (iError)
	{
		TEST_RETURN_TESTERERROR(iError, sError);
	}
	else
	{
		TEST_RESULT_STR("OK", "");
	}
	return;
}

/******************************************************************************/
static void MCTBoxAPI_TF_SwitchModule_SetResetSwitchHelp(void)
{
	TESTER_TestFunctionRegisterHelp(1, "Switch tokens list you want to close",
		"Please separate these switch tokens with comma ','. \nOther signs or space are not supported now.");
	
	TESTER_TestFunctionRegisterHelp(2, "Switch tokens list you want to open",
		"Please separate these switch tokens with comma ','. \nOther signs or space are not supported now.");
}

void API MCTBoxAPI_TF_SwitchModule_SetResetSwitch(int hThisStep)
{
	int iError = 0;
	char sError[256] = {0};
	char *SwitchTokenArray2Close[64] = {0}, *SwitchTokenArray2Open[64] = {0};
	int  iNumOfToken2Close = 0, iNumOfToken2Open = 0, i = 0;
	
	TEST_PARAM_STR(1, sSwitchTokenList2Close);
	TEST_PARAM_STR(2, sSwitchTokenList2Open);
	
	TEST_CHECK_CBREAK;
	TEST_STEP_DELAY;
	
	if ( (strlen(sSwitchTokenList2Close) == 0) && (strlen(sSwitchTokenList2Open) == 0) )
	{
		TEST_RETURN_TESTERERROR(-1, "Parameter list is empty!");
		return;
	}
	
	if (strlen(sSwitchTokenList2Close) != 0)
	{
		ParseTokenList(sSwitchTokenList2Close, SwitchTokenArray2Close, &iNumOfToken2Close);
		for (i=0; i<iNumOfToken2Close; i++)
		{
			iError = MCTBoxAPI_SwitchModule_SetSwitch(SwitchTokenArray2Close[i], sError);
			if (iError)
			{
				TEST_RETURN_TESTERERROR(iError, sError);
				return;
			}
		}
	}
	if (strlen(sSwitchTokenList2Open) != 0)
	{
		ParseTokenList(sSwitchTokenList2Open, SwitchTokenArray2Open, &iNumOfToken2Open);
		for (i=0; i<iNumOfToken2Open; i++)
		{
			iError = MCTBoxAPI_SwitchModule_ResetSwitch(SwitchTokenArray2Open[i], sError);
			if (iError)
			{
				TEST_RETURN_TESTERERROR(iError, sError);
				return;
			}
		}
	}
	if (!iError)
		TEST_RESULT_STR("OK", "");
	
	return;
}

/******************************************************************************/
void API MCTBoxAPI_RegisterSwitchModuleTFSteps(void)
{
	TEST_REGISTER(MCTBoxAPI_TF_SwitchModule_OpenCloseSwitch);
	MCTBoxAPI_TF_SwitchModule_OpenCloseSwitchHelp();
	
	TEST_REGISTER(MCTBoxAPI_TF_SwitchModule_ClearAllSwitches);
	MCTBoxAPI_TF_SwitchModule_ClearAllSwitchesHelp();
	
	TEST_REGISTER(MCTBoxAPI_TF_SwitchModule_SetAllSwitches);
	MCTBoxAPI_TF_SwitchModule_ClearAllSwitchesHelp();
	
	TEST_REGISTER(MCTBoxAPI_TF_SwitchModule_SetResetSwitch);
	MCTBoxAPI_TF_SwitchModule_SetResetSwitchHelp();
}
