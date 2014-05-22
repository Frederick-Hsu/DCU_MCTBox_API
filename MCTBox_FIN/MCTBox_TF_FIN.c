/******************************************************************************************************************************
 * File name		: MCTBox_TF_FIN.c
 * Description		: Implement the TF step functions for FIN module.
 * Creator			: XU ZAN	[HSE-OT]
 * Creation date	: Wed.	Apr. 02, 2014
 * Copyright(C)		2014	Hella Shanghai Electronics Co., Ltd.
 * All rights reserved.
 *
 ******************************************************************************************************************************/

//==============================================================================
// Include files
#include <windows.h>
#include <utility.h>
#include <stdio.h>

#include "../MCTBox_API_FIN.h"
#include "../MCTBox_DIO/DIO_Link_Node.h"
#include "SUT Sequenzer Kernel API.h"

//==============================================================================
// Constants

//==============================================================================
// Macros :
 #undef AUTO_DISPLAY_TOKENS

//==============================================================================
// Static global variables

//==============================================================================
// Static functions
static void MCTBoxAPI_TF_FINModule_QueryFinPortStateHelp(void);
static void MCTBoxAPI_TF_FINModule_ParallelQueryFinBoard24PortsStateHelp(void);
#if defined (AUTO_DISPLAY_TOKENS)
	static void MCTBoxAPI_TF_FINModule_QueryFinPortStateByAutoTokenHelp(void);
#else
	static void MCTBoxAPI_TF_FINModule_QueryFinPortStateByTokenHelp(void);
#endif

//==============================================================================
// Global variables
#if defined (AUTO_DISPLAY_TOKENS)
	extern PDioPortNode_t pDioPortNode;    
#endif

extern int __stdcall (*pfTESTER_TestFunctionSetInfoStr)(char sKey[], char sLabel[], char sValue[]);

//==============================================================================
// Global functions
static void MCTBoxAPI_TF_FINModule_QueryFinPortStateHelp(void)
{
	char sKey[32] = {0}, sLabel[32] = {0}, sValue[32] = {0};

	TESTER_TestFunctionRegisterHelp(1, "Optical-couple Input Board ID", 
		"Enter the Board ID of Optical-couple Input board. \nRange : [0x00, 0xFF]");
	TESTER_TestFunctionRegisterHelp(2, "Channel number of Optical-couple Input board port", 
		"Choose the channel number of Optical-couple Input Board, from the list box. \nRange : [1, 24]");

	pfTESTER_TestFunctionSetInfoStr("Param1.Type", "", "5");
	pfTESTER_TestFunctionSetInfoStr("Param1.ViewValue", "", "1");
	pfTESTER_TestFunctionSetInfoStr("Param1.DataType", "", "0");
	pfTESTER_TestFunctionSetInfoStr("Param1.Min", "", "0");
	pfTESTER_TestFunctionSetInfoStr("Param1.Max", "", "255");


	pfTESTER_TestFunctionSetInfoStr("Param2.Type", "", "3");	// Combo list
	pfTESTER_TestFunctionSetInfoStr("Param2.NumValue", "", "24");
	for (int iCnt=1; iCnt<=24; iCnt++)
	{
		sprintf(sKey, "Param2.Value%d", iCnt);
		sprintf(sLabel, "%d", iCnt);
		sprintf(sValue, "%d", iCnt);
		pfTESTER_TestFunctionSetInfoStr(sKey, sLabel, sValue);
	}

	return;
}

void API MCTBoxAPI_TF_FINModule_QueryFinPortState(int hThisStep)
{
	int iError = 0;
	char sError[256] = {0};
	EState eFinPortState = LOW;

	TEST_PARAM_INT(1, iFinBoardID);
	TEST_PARAM_INT(2, iFinPortNr);

	TEST_CHECK_CBREAK;
	TEST_STEP_DELAY;

	iError = MCTBoxAPI_FINModule_QueryFinPortState(iFinBoardID, iFinPortNr, &eFinPortState, sError);
	if (iError)
	{
		TEST_RETURN_TESTERERROR(iError, sError);
		return;
	}
	if (HIGH == eFinPortState)
	{
		TEST_RESULT_STR("HIGH", "");
	}
	else if (LOW == eFinPortState)
	{
		TEST_RESULT_STR("LOW", "");
	}

	return;
}

/******************************************************************************/
static void MCTBoxAPI_TF_FINModule_ParallelQueryFinBoard24PortsStateHelp(void)
{
	TESTER_TestFunctionRegisterHelp(1, "Optical-couple Input Board ID", 
		"Enter the Board ID of Optical-couple Input board. \nRange : [0x00, 0xFF]");

	pfTESTER_TestFunctionSetInfoStr("Param1.Type", "", "5");	// Slide effect
	pfTESTER_TestFunctionSetInfoStr("Param1.ViewValue", "", "1");
	pfTESTER_TestFunctionSetInfoStr("Param1.DataType", "", "0");
	pfTESTER_TestFunctionSetInfoStr("Param1.Min", "", "0");
	pfTESTER_TestFunctionSetInfoStr("Param1.Max", "", "255");
}

void API MCTBoxAPI_TF_FINModule_ParallelQueryFinBoard24PortsState(int hThisStep)
{
	int iError = 0;
	char sError[256] = {0};
	EState e24PortsState[24] = {0};
	char sFin24PortsStateArray[32] = {0}, sTemp[4] = {0};

	TEST_PARAM_INT(1, iFinBoardID);

	TEST_CHECK_CBREAK;
	TEST_STEP_DELAY;

	iError = MCTBoxAPI_FINModule_ParallelQueryFinBoard24PortsState(iFinBoardID, e24PortsState, sError);
	if (iError)
	{
		TEST_RETURN_TESTERERROR(iError, sError);
		return;
	}

	for (int i=23; i>=0; i--)
	{
		if (OFF == e24PortsState[i])
			sprintf(sTemp, "%s", "0");
		else if (ON == e24PortsState[i])
			sprintf(sTemp, "%s", "1");

		strcat(sFin24PortsStateArray, sTemp);
	}
	TEST_RESULT_STR(sFin24PortsStateArray, "");

	return;
}

/******************************************************************************/
#if defined (AUTO_DISPLAY_TOKENS)
	static void MCTBoxAPI_TF_FINModule_QueryFinPortStateByAutoTokenHelp(void)
	{
		PDioPortNode_t pTempNode = pDioPortNode, pCntOfNode = pDioPortNode;
		int iCntOfNode = 0, nCnt = 0;
		char sCntOfNode[8] = "", snCnt[8] = "";

		TESTER_TestFunctionRegisterHelp(1, "FIN port token name", 
			"Please choose the token of FIN port from the dropdown list.");

		pfTESTER_TestFunctionSetInfoStr("Param1.Type", "", "3");
		while (pCntOfNode != NULL)
		{
			iCntOfNode++;
			pCntOfNode = pCntOfNode->next;
		}
		sprintf(sCntOfNode, "%d", iCntOfNode);
		pfTESTER_TestFunctionSetInfoStr("Param1.NumValue", "", sCntOfNode);
		
		while (pTempNode != NULL)
		{
			nCnt++;
			sprintf(snCnt, "Param1.Value%d", nCnt);
			pfTESTER_TestFunctionSetInfoStr(snCnt, pTempNode->stDioPortToken.sDioPortTokenName, pTempNode->stDioPortToken.sDioPortTokenName);
		}

		return;
	}
#else
	static void MCTBoxAPI_TF_FINModule_QueryFinPortStateByTokenHelp(void)
	{
		TESTER_TestFunctionRegisterHelp(1, "FIN port token name", 
			"Please edit the token name of Fin port you want, which is defined in function 'MCTBoxAPI_FINModule_FinPortListAddEntry'.");
	}
#endif	/*  AUTO_DISPLAY_TOKENS  */

void API MCTBoxAPI_TF_FINModule_QueryFinPortStateByToken(int hThisStep)
{
	int iError;
	char sError[256] = {0};
	EState eFinPortState = LOW;

	TEST_PARAM_STR(1, sIndividualFinPortToken);

	TEST_CHECK_CBREAK;
	TEST_STEP_DELAY;

	iError = MCTBoxAPI_FINModule_QueryFinPortStateByToken(sIndividualFinPortToken, &eFinPortState, sError);
	if (iError)
	{
		TEST_RETURN_TESTERERROR(iError, sError);
		return;
	}
	if (HIGH == eFinPortState)
	{
		TEST_RESULT_STR("HIGH", "");
	}
	else if (LOW == eFinPortState)
	{
		TEST_RESULT_STR("LOW", "");
	}
	return;
}

/******************************************************************************/
void API MCTBoxAPI_RegisterFINModuleTFSteps(void)
{
	TEST_REGISTER(MCTBoxAPI_TF_FINModule_QueryFinPortState);
	MCTBoxAPI_TF_FINModule_QueryFinPortStateHelp();	

	TEST_REGISTER(MCTBoxAPI_TF_FINModule_ParallelQueryFinBoard24PortsState);
	MCTBoxAPI_TF_FINModule_ParallelQueryFinBoard24PortsStateHelp();

	TEST_REGISTER(MCTBoxAPI_TF_FINModule_QueryFinPortStateByToken);
	#if defined (AUTO_DISPLAY_TOKENS)
		MCTBoxAPI_TF_FINModule_QueryFinPortStateByAutoTokenHelp();
	#else
		MCTBoxAPI_TF_FINModule_QueryFinPortStateByTokenHelp();
	#endif
}
