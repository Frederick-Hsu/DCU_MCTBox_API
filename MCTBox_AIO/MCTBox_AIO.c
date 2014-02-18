/********************************************************************************************************
 * File name		: MCTBox_AIO.c
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

#include "../MCTBox_API_AIO.h"
#include "../MCTBox_API.h"
#include "../user_utility.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions
static int FetchAdcValuesArray(char sResponseMesg[], char *sAdcValuesArray[]);

//==============================================================================
// Global variables

//==============================================================================
// Functions implementation :

int API MCTBoxAPI_AIOModule_AcquireVoltageOfAdcChannel(EAdcChannel_t 	eMCTBox_ADC_ChannelNr,
													   double 			*dARGOUT_AcquiredVoltageOfCurrentChannel,	// unit : Volt
													   char 			*sARGOUT_ErrorMesg)
{
	int iResult = 0;
	char sMCTBoxCmd[64] = "", sMCTBoxResponse[64] = "", sError[256] = "";
	char sVoltageValueStr[64] = {0}, *sTemp = NULL;
	double dVoltage = 0.00f;
	
	if ( (eMCTBox_ADC_ChannelNr<MCTBox_ADC_CH1) || (eMCTBox_ADC_ChannelNr>MCTBox_ADC_CH8) )
	{
		sprintf(sARGOUT_ErrorMesg, "%s", "The ADC channel number is wrong. Range : [1, 8].");
		return -1;
	}
	
	sprintf(sMCTBoxCmd, "$ADC %d:VOLT?!", eMCTBox_ADC_ChannelNr);
	iResult = MCTBoxAPI_Request(sMCTBoxCmd, sMCTBoxResponse);
	if (iResult)
	{
		iResult = MCTBoxAPI_IsCommunicationError(sError);
		sprintf(sARGOUT_ErrorMesg, "%s", sError);
		return iResult;
	}
	
	/* Parse the response and 
	 * retrieve the voltage value
	 */   
	sTemp = strstr(sMCTBoxResponse, "VOLT ");
	if (!sTemp)
	{
		sprintf(sARGOUT_ErrorMesg, "%s", "Failed to retrieve the ADC voltage value.");
		return -10;
	}
	strncpy(sVoltageValueStr, sTemp+5, strlen(sTemp)-5-1);
	dVoltage = atof(sVoltageValueStr);
	memcpy(dARGOUT_AcquiredVoltageOfCurrentChannel, &dVoltage, sizeof(double));
	
	return iResult;
}

static int FetchAdcValuesArray(char sResponseMesg[], char *sAdcValuesArray[])
{
	unsigned int uiPosOfDollar 	= strcspn(sResponseMesg, "$"),
				 uiPosOfSigh	= strcspn(sResponseMesg, "!"),
				 uiPosOfColon   = 0;
	char sTargetResponseStr[512] = {0}, sRestStr[512] = {0}, sAdcVoltage1Unit[64] = {0}, sTemp[512] = {0};
	int iCnt = 0;
	
	if ( (uiPosOfDollar != 1) || (uiPosOfSigh != strlen(sResponseMesg)) )
		return -1;
	
	strncpy(sTargetResponseStr, sResponseMesg+1, strlen(sResponseMesg)-2);
	strcpy(sRestStr, sTargetResponseStr);
	do
	{   
		uiPosOfColon = strcspn(sRestStr, ";");
		strncpy(sAdcVoltage1Unit, sRestStr, uiPosOfColon-1);
		
		sAdcValuesArray[iCnt] = malloc(strlen(sAdcVoltage1Unit)+1);
		strcpy(sAdcValuesArray[iCnt], sAdcVoltage1Unit);
		iCnt++;
		memset(sAdcVoltage1Unit, 0, sizeof(sAdcVoltage1Unit));
		
		strncpy(sTemp, sRestStr+uiPosOfColon+1, strlen(sRestStr)-uiPosOfColon-1);
		memset(sRestStr, 0, sizeof(sRestStr));
		strcpy(sRestStr, sTemp);
		memset(sTemp, 0, sizeof(sTemp));
	}
	while (strstr(sRestStr, ";"));
	strcpy(sAdcValuesArray[iCnt], sRestStr);
	
	return 0;
}

int API MCTBoxAPI_AIOModule_AcquireVoltagesOfAll8Channels(double *dARGOUT_VoltagesOfAll8Channels[8],		// 8 voltage values of 8 ADC channels, unit : Volt 
														  char 	 *sARGOUT_ErrorMesg)
{
	int iResult = 0;
	char sCmd[256] = {0}, sResponse[512] = {0}, sError[256] = {0};
	double dVoltageArray[8] = {0.00f};
	char  *sVoltageArray[8] = {0};
	
	sprintf(sCmd, "%s", "$ADC *:VOLT?!");
	iResult = MCTBoxAPI_Request(sCmd, sResponse);
	if (iResult)
	{
		iResult = MCTBoxAPI_IsCommunicationError(sError);
		sprintf(sARGOUT_ErrorMesg, "%s", sError);
		return iResult;
	}
	
	iResult = FetchAdcValuesArray(sResponse, sVoltageArray);
	if (iResult)
		return iResult;
	
	for (int i=0; i<8; i++)
	{
		iResult = RetrieveAdcVoltageValueFrom1unitOfAdcResponse(sVoltageArray[i], &(dVoltageArray[i]), sError);
		if (iResult)
		{
			sprintf(sARGOUT_ErrorMesg, "%s", sError);
			return iResult;
		}
		
		memcpy(dARGOUT_VoltagesOfAll8Channels[i], &(dVoltageArray[i]), sizeof(double));
	}	   
	
	return iResult;
}

int API MCTBoxAPI_AIOModule_AcquireCurrentOfAdcChannel(EAdcChannel_t 	eMCTBox_ADC_CurrentChannelNr,
													   float 			fShuntResistorInOhm,					// unit : Ohm
													   double 			*dARGOUT_AcquiredCurrentOfAdcChannel,	// unit : Ampere
													   char 			*sARGOUT_ErrorMesg)
{
	int iResult = 0;
	char sCmd[64] = {0}, sResponse[128] = {0}, sCurrentValue[64] = {0}, *sTemp = NULL;
	double dCurrentValue = 0.00f;
	
	if ((eMCTBox_ADC_CurrentChannelNr < MCTBox_ADC_CH1) || 
		(eMCTBox_ADC_CurrentChannelNr > MCTBox_ADC_CH1) )
		return -1;
	
	sprintf(sCmd, "$ADC %d:CURR %.04f?!", eMCTBox_ADC_CurrentChannelNr, fShuntResistorInOhm);
	iResult = MCTBoxAPI_Request(sCmd, sResponse);
	if (iResult)
	{
		iResult = MCTBoxAPI_IsCommunicationError(sARGOUT_ErrorMesg);
		return iResult;
	}
	
	sTemp = strstr(sResponse, "CURR ");
	if (!sTemp)
	{
		sprintf(sARGOUT_ErrorMesg, "%s", "Failed to retrieve the ADC current value.");
		return -10;
	}
	strncpy(sCurrentValue, sTemp+5, strlen(sTemp)-5-1);
	dCurrentValue = atof(sCurrentValue);
	memcpy(dARGOUT_AcquiredCurrentOfAdcChannel, &dCurrentValue, sizeof(double)); 
	
	return iResult;
}

