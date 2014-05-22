/****************************************************************************************************************
 * File name		: AIO_Channel_LinkNode.c
 * Description		: Define the link list node of AIO channel.
 * Creator			: XU ZAN
 * Creation date	: Mon.	Feb. 17, 2014
 * Copyright(C)		2014	Hella Shanghai Electronics Co., Ltd.
 * All rights reserved.
 *
 ****************************************************************************************************************/

//==============================================================================
// Include files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "AIO_Channel_LinkNode.h"
#include "MCTBox_API_AIO.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
PADC_CH_LinkNode_t pMeasChannelNode = NULL;

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions
int API MCTBoxAPI_AIOModule_MeasChannelListAddEntry(char 	sMeasTokenName[],
													char 	sMeasDescription[],
													char 	sMeasConnector[],
													char 	sMeasDeviceName[],
													int		iMeasChannelNr,
													float	fMeasShuntResistorInOhm)
{
	int iResult = 0;
	PADC_CH_LinkNode_t pTempNode = pMeasChannelNode, pCurrentNode = NULL, pNewNode = NULL;
	
	if (pMeasChannelNode == NULL)
	{
		pMeasChannelNode = (PADC_CH_LinkNode_t)malloc(sizeof(ADC_CH_LinkNode_t));
		if (pMeasChannelNode == NULL)
			return -2;	// Memory overflow
		else
		{
			AssignMeasChannelNode(pMeasChannelNode,
								  sMeasTokenName,
								  sMeasDescription,
								  sMeasConnector,
								  sMeasDeviceName,
								  iMeasChannelNr,
								  fMeasShuntResistorInOhm);
			pMeasChannelNode->next = NULL;
			return 0;
		}
	}
	
	do
	{
		pCurrentNode = pTempNode;
		pTempNode = pTempNode->next;
	}
	while (pTempNode != NULL);
	pNewNode = (PADC_CH_LinkNode_t)malloc(sizeof(ADC_CH_LinkNode_t));
	if (pNewNode == NULL)
		return -2;
	AssignMeasChannelNode(pNewNode, 
						  sMeasTokenName, 
						  sMeasDescription, 
						  sMeasConnector, 
						  sMeasDeviceName, 
						  iMeasChannelNr, 
						  fMeasShuntResistorInOhm);
	pNewNode->next = NULL;
	pCurrentNode->next = pNewNode;
	
	return iResult;
}

/******************************************************************************/
int API MCTBoxAPI_AIOModule_DeleteMeasChannelList(void)
{
	PADC_CH_LinkNode_t pTempNode = pMeasChannelNode;
	
	while (pTempNode != NULL)
	{
		pTempNode = pTempNode->next;
		free(pMeasChannelNode);
		pMeasChannelNode = pTempNode;
	}
	free(pMeasChannelNode);
	
	return 0;
}

/******************************************************************************/
void AssignMeasChannelNode(PADC_CH_LinkNode_t 	pCurrentNode,
						   char 				sMeasTokenName[],
						   char					sMeasDescription[],
						   char					sMeasConnector[],
						   char					sMeasDeviceName[],
						   int					iMeasChannelNr,
						   float				fMeasShuntResistorInOhm)
{
	pCurrentNode->tMeasChannel.sAdcToken = (char *)malloc(sizeof(char)*(strlen(sMeasTokenName)+1));
	pCurrentNode->tMeasChannel.sAdcDescription = (char *)malloc(sizeof(char)*(strlen(sMeasDescription)+1));
	pCurrentNode->tMeasChannel.sAdcConnector = (char *)malloc(sizeof(char)*(strlen(sMeasConnector)+1));
	pCurrentNode->tMeasChannel.sAdcDeviceName = (char *)malloc(sizeof(char)*(strlen(sMeasDeviceName)+1));
	
	sprintf(pCurrentNode->tMeasChannel.sAdcToken, "%s", sMeasTokenName);
	sprintf(pCurrentNode->tMeasChannel.sAdcDescription, "%s", sMeasDescription);
	sprintf(pCurrentNode->tMeasChannel.sAdcConnector, "%s", sMeasConnector);
	sprintf(pCurrentNode->tMeasChannel.sAdcDeviceName, "%s", sMeasDeviceName);
	
	pCurrentNode->tMeasChannel.iAdcChNr = iMeasChannelNr;
	pCurrentNode->tMeasChannel.fAdcShuntResistorInOhm = fMeasShuntResistorInOhm;
	return;
}

/******************************************************************************/
int API MCTBoxAPI_AIOModule_MeasVoltageByToken(char 	sMeasTokenName[], 
											   double 	*dARGOUT_VoltageInV,
											   char 	*sARGOUT_ErrorMesg)
{
	int iResult = 0, iHitTargetFlag = 0;
	char sError[256] = "";
	PADC_CH_LinkNode_t pTemp = pMeasChannelNode;
	
	do
	{
		if (!strcmp(pTemp->tMeasChannel.sAdcToken, sMeasTokenName))
		{
			iHitTargetFlag = 1;
			iResult = MCTBoxAPI_AIOModule_AcquireVoltageOfAdcChannel(pTemp->tMeasChannel.iAdcChNr, 
																	 dARGOUT_VoltageInV, 
																	 sError);
			if (iResult)
			{
				sprintf(sARGOUT_ErrorMesg, "%s", sError);
				return iResult;
			}
			break;
		}
		pTemp = pTemp->next;
	}
	while (pTemp != NULL);
	if (iHitTargetFlag == 0)
	{
		sprintf(sARGOUT_ErrorMesg, "Unknown %s token of ADC measurement channel.", sMeasTokenName);
		return -10;
	}
	
	return iResult;
}
		
/******************************************************************************/
int API MCTBoxAPI_AIOModule_MeasCurrentByToken(char 	sMeasTokenName[], 
											   float 	fMeasShuntResistorInOhm, 
											   double 	*dARGOUT_CurrentInA,
											   char		*sARGOUT_ErrorMesg)
{
	int iResult = 0, iHitTargetFlag = 0;
	char sError[256] = "";
	PADC_CH_LinkNode_t pTemp = pMeasChannelNode;
	
	do
	{
		if (!strcmp(pTemp->tMeasChannel.sAdcToken, sMeasTokenName))
		{
			iHitTargetFlag = 1;
			iResult = MCTBoxAPI_AIOModule_AcquireCurrentOfAdcChannel(pTemp->tMeasChannel.iAdcChNr,
																	 fMeasShuntResistorInOhm,
																	 dARGOUT_CurrentInA, 
																	 sError);
			if (iResult)
			{
				sprintf(sARGOUT_ErrorMesg, "%s", sError);
				return iResult;
			}
			break;
		}
		pTemp = pTemp->next;
	}
	while (pTemp != NULL);
	if (iHitTargetFlag == 0)
	{
		sprintf(sARGOUT_ErrorMesg, "Unknown %s token of ADC measurement channel.", sMeasTokenName);
		return -10;
	}
	
	return iResult;
}

