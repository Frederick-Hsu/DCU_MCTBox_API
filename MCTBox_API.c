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
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <utility.h>

#include "MCTBox_API.h"
#include "MCTBox_communication.h" 
#include "MCTBox_API_Version.h" 

#if defined (SUT_SEQUENZER)
	#include "SUT Sequenzer Kernel API.h"
#endif

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
static char g_sErrorMesg[512] = {0};

//==============================================================================
// Static functions
static int GetErrorCode(char sErrorMesg[]);
static void MCTBoxAPI_TF_InitHelp(void);
static void ExportDllFunc_TESTER_TestFunctionSetInfoStr(void);

//==============================================================================
// Global variables
#if defined (SUT_SEQUENZER)
	int __stdcall (*pfTESTER_TestFunctionSetInfoStr)(char sKey[], char sLabel[], char sValue[]) = NULL;

	//==============================================================================
	// Function implementations :
	static void ExportDllFunc_TESTER_TestFunctionSetInfoStr(void)
	{
		HMODULE hSequenzerKernelDll = NULL;
		if (pfTESTER_TestFunctionSetInfoStr == NULL)
		{
			hSequenzerKernelDll = GetModuleHandle("Sequencer Kernel.dll");
			pfTESTER_TestFunctionSetInfoStr = (void *)GetProcAddress(hSequenzerKernelDll, 
																	 "TESTER_TestFunctionSetInfoStr");
		}
		return;
	}
#endif	/* SUT_SEQUENZER */


void API MCTBoxAPI_Bio(char *sMCTBox_BioInfo)
{
	char sMCTBox_Bio[] = "Hello, this is MCTBox_API. Welcome to call me!\n\
		MCTBox_API provides you plenty of functions & features to access the MCTBox testing instrument,\n\
		to implement your testing project.";
	
	sprintf(sMCTBox_BioInfo, "%s", sMCTBox_Bio);
	return;
}

/******************************************************************************/
void API MCTBoxAPI_LibraryVersion(char *sMCTBox_LibraryVersionInfo)
{
	sprintf(sMCTBox_LibraryVersionInfo, "%s", CURRENT_VERSION);
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
int API MCTBoxAPI_SayHello2MCTBox(char *sARGOUT_MCTBoxResponse)
{
	int iResult = 0;
	char sResponse[256] = "", sError[256] = "";
	iResult = MCTBox_communication_RS232_Query("$SYSTem:IDN?!", sResponse, sError);
	if (iResult)	// Check the negative error code
	{
		return iResult;
	}
	sprintf(sARGOUT_MCTBoxResponse, "%s", sResponse);
	return iResult;
}

/******************************************************************************/
int API MCTBoxAPI_Exit(char *sARGOUT_ComError)
{
	int iResult = 0;
	iResult = MCTBox_communication_RS232_Exit(sARGOUT_ComError);
	return iResult;
}

/******************************************************************************/
static int GetErrorCode(char sErrorMesg[])
{
	int iErrorCode = 0;
	char sErrorCode[32] = {0};
	int iPosOfKeyword_ErrorCode = strcspn(sErrorMesg, "Error code:"),
		iPosOfComma = strcspn(sErrorMesg, ",");
	
	strncpy(sErrorCode, 
			sErrorMesg+iPosOfKeyword_ErrorCode+12, 
			iPosOfComma-iPosOfKeyword_ErrorCode-12);
	
	iErrorCode = atoi(sErrorCode);
	return iErrorCode;
}

/******************************************************************************/
int API MCTBoxAPI_Transmit(char sARGIN_TxCommand[])
{
	int iResult = 0;
	char sError[512] = "";
	
	iResult = MCTBox_communication_RS232_Write(sARGIN_TxCommand, sError);
	if (0 != strlen(sError))
	{
		sprintf(g_sErrorMesg, "%s", sError);
		iResult = GetErrorCode(sError);
		return iResult;
	}
	
	return 0;
}

/******************************************************************************/
int API MCTBoxAPI_Receive(char *sARGOUT_RxResponse)
{
	int iResult = 0;
	char sError[512] = {0};
	
	iResult = MCTBox_communication_RS232_Read(sARGOUT_RxResponse, sError);
	if (0 != strlen(sError))
	{
		sprintf(g_sErrorMesg, "%s", sError);
		iResult = GetErrorCode(sError);
		return iResult;
	}
	
	return 0;
}

/******************************************************************************/
int API MCTBoxAPI_Request(char sARGIN_TxCommand[], char *sARGOUT_RxResponse)
{
	int iResult = 0;
	char sError[512] = {0};
	
	iResult = MCTBox_communication_RS232_Query(sARGIN_TxCommand, sARGOUT_RxResponse, sError);
	if (0 != strlen(sError))
	{
		sprintf(g_sErrorMesg, "%s", sError);
		iResult = GetErrorCode(sError);
		return iResult;
	}
	
	return 0;
}

/******************************************************************************/
int API MCTBoxAPI_IsCommunicationError(char *sARGOUT_CommunicationError)
{
	int iResult = 0;
	if (0 != strlen(g_sErrorMesg))
	{
		sprintf(sARGOUT_CommunicationError, "%s", g_sErrorMesg);
		iResult = GetErrorCode(sARGOUT_CommunicationError);
	}
	sprintf(g_sErrorMesg, "%s", "");	// Clean the previous error message
	return iResult;
}

/******************************************************************************/
int API MCTBoxAPI_IsExecutionError(char *sARGOUT_ExecutionError)
{
	int iResult = 0, iExecutionErrorCode = 0;
	int iPosOfSharp = 0, iPosOf2ndColon = 0;
	char sExecutionErrorCode[256] = {0}, *sErrorStr = "";
	
	iResult = MCTBoxAPI_Request("$SYSTem:ERRor?!", sARGOUT_ExecutionError);
	if (iResult)
		return iResult;
	
	sErrorStr = strstr(sARGOUT_ExecutionError, "Error code #");
	iPosOfSharp = strcspn(sErrorStr, "#");
	iPosOf2ndColon = strcspn(sErrorStr, ":");
	
	strncpy(sExecutionErrorCode, sErrorStr+iPosOfSharp+1, iPosOf2ndColon-iPosOfSharp-1);
	iExecutionErrorCode = atoi(sExecutionErrorCode);
	iResult = iExecutionErrorCode;
	
	return iResult;
}

/******************************************************************************/
void API MCTBoxAPI_FirmwareVersion(char *sMCTBox_FirmwareVersionInfo)
{
	int iResult = 0;
	
	iResult = MCTBoxAPI_Request("$SYSTem:VERsion?!", sMCTBox_FirmwareVersionInfo);
	return;
}


#if defined (SUT_SEQUENZER)
	//==============================================================================
	// Test Function implementations :
	static void MCTBoxAPI_TF_InitHelp(void)
	{
		TESTER_TestFunctionRegisterHelp(1, "MCTBox serial port number",
			"Please enter the serial port number of communicating with MCTBox test instrument.");
	}

	void API MCTBoxAPI_TF_Init(int hThisStep)
	{
		int iResult = 0;
		char sError[256] = {0};
		TEST_PARAM_INT(1, iComPortNr);
	
		TEST_CHECK_CBREAK;
		TEST_STEP_DELAY;
	
		iResult = MCTBoxAPI_Init(iComPortNr, sError);
		if (iResult != 0)
		{
			TEST_RETURN_TESTERERROR(iResult, sError);
		}
		else
		{
			TEST_RESULT_STR("OK", "");
		}
		return;
	}

	/******************************************************************************/
	void API MCTBoxAPI_TF_Exit(int hThisStep)
	{
		int iError = 0;
		char sError[256] = {0};
	
		TEST_CHECK_CBREAK;
		TEST_STEP_DELAY;
	
		iError = MCTBoxAPI_Exit(sError);
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
	void API MCTBoxAPI_TF_SayHello2MCTBox(int hThisStep)
	{
		int iError = 0;
		char sError[256] = {0};
		char sMCTBoxResponse[512] = {0};
	
		TEST_CHECK_CBREAK;
		TEST_STEP_DELAY;
	
		iError = MCTBoxAPI_SayHello2MCTBox(sMCTBoxResponse);
		if (iError)
		{
			iError = MCTBoxAPI_IsExecutionError(sError);
			TEST_RETURN_TESTERERROR(iError, sError);
		}
		else
		{
			TEST_RESULT_STR(sMCTBoxResponse, "");
		}
		return;
	}

	/******************************************************************************/
	static void MCTBoxAPI_TF_TransmitHelp(void)
	{
		TESTER_TestFunctionRegisterHelp(1, "Command for transmitting to MCTBox",
			"Please edit the command string transmitting to MCTBox. \nYou should obey the MCTBox's command protocol.");
	}

	void API MCTBoxAPI_TF_Transmit(int hThisStep)
	{
		int iError = 0;
		char sError[256] = {0};
	
		TEST_PARAM_STR(1, sTxCommand);
	
		TEST_CHECK_CBREAK;
		TEST_STEP_DELAY;
	
		iError = MCTBoxAPI_Transmit(sTxCommand);
		if (iError)
		{
			iError = MCTBoxAPI_IsCommunicationError(sError);
			TEST_RETURN_TESTERERROR(iError, sError);
		}
		else
		{
			TEST_RESULT_STR("OK", "");
		}
		return;
	} 

	/******************************************************************************/
	void API MCTBoxAPI_TF_Receive(int hThisStep)
	{
		int iError = 0;
		char sError[256] = {0}, sMCTBoxRxResponse[512] = {0};
	
		TEST_CHECK_CBREAK;
		TEST_STEP_DELAY;
	
		iError = MCTBoxAPI_Receive(sMCTBoxRxResponse);
		if (iError)
		{
			iError = MCTBoxAPI_IsCommunicationError(sError);
			TEST_RETURN_TESTERERROR(iError, sError);
		}
		else
		{
			TEST_RESULT_STR(sMCTBoxRxResponse, "");
		}
		return;
	}

	/******************************************************************************/
	void API MCTBoxAPI_TF_Request(int hThisStep)
	{
		int iError = 0;
		char sError[256] = {0}, sMCTBoxRxResponse[512] = {0};
	
		TEST_PARAM_STR(1, sMCTBoxTxCommand);
	
		TEST_CHECK_CBREAK;
		TEST_STEP_DELAY;
	
		iError = MCTBoxAPI_Request(sMCTBoxTxCommand, sMCTBoxRxResponse);
		if (iError)
		{
			iError = MCTBoxAPI_IsCommunicationError(sError);
			TEST_RETURN_TESTERERROR(iError, sError);
		}
		else
		{
			TEST_RESULT_STR(sMCTBoxRxResponse, "");
		}
		return;
	}

	/******************************************************************************/
	void API MCTBoxAPI_TF_IsExecutionError(int hThisStep)
	{
		int iErrorCode = 0;
		char sErrorMesg[256] = {0};
	
		TEST_CHECK_CBREAK;
		TEST_STEP_DELAY;
	
		iErrorCode = MCTBoxAPI_IsExecutionError(sErrorMesg);
		if (iErrorCode == 0)
		{
			TEST_RESULT_STR(sErrorMesg, "");
		}
		else
		{
			TEST_RETURN_TESTERERROR(iErrorCode, sErrorMesg);
		}
		return;  
	}

	/******************************************************************************/
	void API MCTBoxAPI_TF_FirmwareVersion(int hThisStep)
	{
		char sFirmwareVersionInfo[512] = {0};
	
		TEST_CHECK_CBREAK;
		TEST_STEP_DELAY;
	
		MCTBoxAPI_FirmwareVersion(sFirmwareVersionInfo);
		TEST_RESULT_STR(sFirmwareVersionInfo, "");
		return;
	}

	/******************************************************************************/
	void API MCTBoxAPI_RegisterCommonTFSteps(void)
	{
		ExportDllFunc_TESTER_TestFunctionSetInfoStr();
	
		TEST_REGISTER(MCTBoxAPI_TF_Init);
		MCTBoxAPI_TF_InitHelp();
	
		TEST_REGISTER(MCTBoxAPI_TF_Exit);
	
		TEST_REGISTER(MCTBoxAPI_TF_SayHello2MCTBox);
	
		TEST_REGISTER(MCTBoxAPI_TF_Transmit);
		MCTBoxAPI_TF_TransmitHelp();
	
		TEST_REGISTER(MCTBoxAPI_TF_Receive);
	
		TEST_REGISTER(MCTBoxAPI_TF_Request);
		MCTBoxAPI_TF_TransmitHelp();
	
		TEST_REGISTER(MCTBoxAPI_TF_IsExecutionError);
	
		TEST_REGISTER(MCTBoxAPI_TF_FirmwareVersion);
	}
#endif	/* SUT_SEQUENZER */

/*
 * END OF FILE <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 */
