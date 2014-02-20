/*****************************************************************************************************************
 * File name		: MCTBox_TF_AIO.h
 * Description		: This source file will implement the registration test functions for AIO module.
 * Creator			: XU ZAN	[HSE-OT]
 * Creation date	: Tue.	Feb. 11, 2014
 * Copyright(C)		2014	Hella Shanghai Electronics Co., Ltd.
 * All rights reserved.
 *
 *****************************************************************************************************************/

//==============================================================================
// Include files
#include "../MCTBox_API_AIO.h"
#include "SUT Sequenzer Kernel API.h"
#include <utility.h>
#include <stdio.h>

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions
static void MCTBoxAPI_TF_AIOModule_AcquireVoltageOfAdcChannelHelp(void);
static void MCTBoxAPI_TF_AIOMpdule_AcquireCurrentOfAdcChannelHelp(void);
static void MCTBoxAPI_TF_AIOModule_MeasVoltageByTokenHelp(void);

//==============================================================================
// Global variables
extern int __stdcall (*pfTESTER_TestFunctionSetInfoStr)(char sKey[], char sLabel[], char sValue[]);

//==============================================================================
// Functions implementation :
static void MCTBoxAPI_TF_AIOModule_AcquireVoltageOfAdcChannelHelp(void)
{
	char sKeyField[32] = "", sLabelField[32] = "", sValueField[32] = "";
	
	TESTER_TestFunctionRegisterHelp(1, "The channel number of ADC-voltage acquiring",
		"Please enter the channel number which you want to acquire the ADC voltage value, range : [1, 8]");
	
	pfTESTER_TestFunctionSetInfoStr("Param1.Type", "", "3");
	pfTESTER_TestFunctionSetInfoStr("Param1.NumValue", "", "8");
	for (int i=1; i<=8; i++)
	{
		sprintf(sKeyField, "Param1.Value%d", i);
		sprintf(sLabelField, "%d", i);
		sprintf(sValueField, "%d", i);
		pfTESTER_TestFunctionSetInfoStr(sKeyField, sLabelField, sValueField);
	}
}

void API MCTBoxAPI_TF_AIOModule_AcquireVoltageOfAdcChannel(int hThisStep)
{
	int iError = 0;
	char sError[256] = {0};
	double dVoltage = 0.00f;
	
	TEST_PARAM_INT(1, iAdcChannelNr);
	
	TEST_CHECK_CBREAK;
	TEST_STEP_DELAY;
	
	iError = MCTBoxAPI_AIOModule_AcquireVoltageOfAdcChannel(iAdcChannelNr, &dVoltage, sError);
	if (iError)
	{
		TEST_RETURN_TESTERERROR(iError, sError);
		return;
	}
	TEST_RESULT_DBL(dVoltage, "Volt");
	return;
}

/******************************************************************************/
static void MCTBoxAPI_TF_AIOMpdule_AcquireCurrentOfAdcChannelHelp(void)
{
	char sKeyField[32] = "", sLabelField[32] = "", sValueField[32] = "";
	
	TESTER_TestFunctionRegisterHelp(1, "The channel number of ADC-voltage acquiring",
		"Please enter the channel number which you want to acquire the ADC voltage value, range : [1, 8]");
	TESTER_TestFunctionRegisterHelp(2, "The shunt resistor value in unit of Ohm",
		"Please enter the the resistor value of shunt resistor, note : unit is Ohm.");
	
	pfTESTER_TestFunctionSetInfoStr("Param1.Type", "", "3");
	pfTESTER_TestFunctionSetInfoStr("Param1.NumValue", "", "8");
	for (int i=1; i<=8; i++)
	{
		sprintf(sKeyField, "Param1.Value%d", i);
		sprintf(sLabelField, "%d", i);
		sprintf(sValueField, "%d", i);
		pfTESTER_TestFunctionSetInfoStr(sKeyField, sLabelField, sValueField);
	}
}

void API MCTBoxAPI_TF_AIOMpdule_AcquireCurrentOfAdcChannel(int hThisStep)
{
	int iError = 0;
	char sError[256] = "";
	double dCurrent = 0.00f;
	
	TEST_PARAM_INT(1, iAdcChannelNr);
	TEST_PARAM_DBL(2, dShuntResistor);
	
	TEST_CHECK_CBREAK;
	TEST_STEP_DELAY;  
	
	iError = MCTBoxAPI_AIOModule_AcquireCurrentOfAdcChannel(iAdcChannelNr, 
															dShuntResistor,
															&dCurrent,
															sError);
	if (iError)
	{
		TEST_RETURN_TESTERERROR(iError, sError);
		return;
	}
	TEST_RESULT_DBL(dCurrent, "A");
	return;
}

/******************************************************************************/
static void MCTBoxAPI_TF_AIOModule_MeasVoltageByTokenHelp(void)
{
	TESTER_TestFunctionRegisterHelp(1, "The token name of voltage measurement channel",
		"Please edit the token name, it was defined in function 'MCTBoxAPI_AIOModule_MeasChannelListAddEntry'.");
}

void API MCTBoxAPI_TF_AIOModule_MeasVoltageByToken(int hThisStep)
{
	int iError = 0;
	char sError[256] = "";
	double dVoltage = 0.00f;
	
	TEST_PARAM_STR(1, sVoltageMeasTokenName);
	
	TEST_CHECK_CBREAK;
	TEST_STEP_DELAY;
	
	iError = MCTBoxAPI_AIOModule_MeasVoltageByToken(sVoltageMeasTokenName, &dVoltage, sError);
	if (iError)
	{
		TEST_RETURN_TESTERERROR(iError, sError);
		return;
	}
	TEST_RESULT_DBL(dVoltage, "V");
	return;
}

/******************************************************************************/
static void MCTBoxAPI_TF_AIOModule_MeasCurrentByTokenHelp(void)
{
	TESTER_TestFunctionRegisterHelp(1, "The token name of voltage measurement channel",
		"Please edit the token name, it was defined in function 'MCTBoxAPI_AIOModule_MeasChannelListAddEntry'.");
	TESTER_TestFunctionRegisterHelp(2, "Shunt resistor value in unit of Ohm", 
		"Please edit the value of shunt resistor which you connected into the measurement circuit.");
}

void API MCTBoxAPI_TF_AIOModule_MeasCurrentByToken(int hThisStep)
{
	int iError = 0;
	char sError[256] = "";
	double dCurrent = 0.00f;
	
	TEST_PARAM_STR(1, sCurrentMeasTokenName);
	TEST_PARAM_DBL(2, dShuntResistorValueInOhm);
	
	TEST_CHECK_CBREAK;
	TEST_STEP_DELAY;
	
	iError = MCTBoxAPI_AIOModule_MeasCurrentByToken(sCurrentMeasTokenName,
													dShuntResistorValueInOhm,
													&dCurrent, 
													sError);
	if (iError)
	{
		TEST_RETURN_TESTERERROR(iError, sError);
		return;
	}
	TEST_RESULT_DBL(dCurrent, "A");
	return;
}

/******************************************************************************/
void API MCTBoxAPI_RegisterAIOModuleTFSteps(void)
{
	TEST_REGISTER(MCTBoxAPI_TF_AIOModule_AcquireVoltageOfAdcChannel);
	MCTBoxAPI_TF_AIOModule_AcquireVoltageOfAdcChannelHelp();
	
	TEST_REGISTER(MCTBoxAPI_TF_AIOMpdule_AcquireCurrentOfAdcChannel);
	MCTBoxAPI_TF_AIOMpdule_AcquireCurrentOfAdcChannelHelp();
	
	TEST_REGISTER(MCTBoxAPI_TF_AIOModule_MeasVoltageByToken);
	MCTBoxAPI_TF_AIOModule_MeasVoltageByTokenHelp(); 
	
	TEST_REGISTER(MCTBoxAPI_TF_AIOModule_MeasCurrentByToken);
	MCTBoxAPI_TF_AIOModule_MeasCurrentByTokenHelp();
}

