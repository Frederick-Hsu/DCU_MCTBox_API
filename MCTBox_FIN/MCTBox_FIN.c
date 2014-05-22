/*****************************************************************************************************************
 * File name		: MCTBox_FIN.c
 * Description		: To rpovide the APIs for accessing the Optical-couple Input board of MCTBox instrument.
 * Creator			: XU ZAN
 * Creation date	: Tue.	Apr. 01, 2014
 * Copyright(C)		2014	Hella Shanghai Electronics Co., Ltd.
 * All rights reserved.
 *
 *****************************************************************************************************************/

//==============================================================================
// Include files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../MCTBox_API_FIN.h"
#include "../MCTBox_API.h"
#include "../MCTBox_API_DIO.h"
#include "../MCTBox_DIO/DIO_Link_Node.h"

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
extern PDioPortNode_t pDioPortNode;    

//==============================================================================
// Global functions
int API MCTBoxAPI_FINModule_QueryFinPortState(BYTE 		ucFinBoardID,
											  UINT 		uiFinPortNr,
											  EState 	*eFinPortState,
											  char 		*sErrorMesg)
{
	int iError = 0;
	char sFinCmd[64] = {0}, sFinResponse[64] = {0}, sError[256] = {0}, sFinPortState[16] = {0}; 
	char *pColonSubStr = NULL;
	unsigned int uiPosOfSpace_In_ColonSubStr = 0, uiPosOfSigh_In_ColonSubStr = 0;
	EState ePortState = LOW;
	
	sprintf(sFinCmd, "$FIN 0x%02X:%02d STATe?!", ucFinBoardID, uiFinPortNr);
	iError = MCTBoxAPI_Request(sFinCmd, sFinResponse);
	if (iError)
	{
		iError = MCTBoxAPI_IsCommunicationError(sError);
		sprintf(sErrorMesg, "%s", sError);
		return iError;
	}
	
	pColonSubStr = strstr(sFinResponse, ":");
	if (!pColonSubStr)
	{
		sprintf(sErrorMesg, "%s", "Failed to get the 'FIN single port command' response from MCTBox!");
		return -10;
	}
	uiPosOfSpace_In_ColonSubStr = strcspn(pColonSubStr, " ");
	uiPosOfSigh_In_ColonSubStr  = strcspn(pColonSubStr, "!");
	strncpy(sFinPortState, 
			pColonSubStr+uiPosOfSpace_In_ColonSubStr+1, 
			uiPosOfSigh_In_ColonSubStr-uiPosOfSpace_In_ColonSubStr-1);
	
	if (!stricmp(sFinPortState, "HIGH"))
		ePortState = HIGH;
	else if (!stricmp(sFinPortState, "LOW"))
		ePortState = LOW;
	else
	{
		sprintf(sErrorMesg, "%s", "Unknown state.");
		return -1;
	}	   
	memcpy(eFinPortState, &ePortState, sizeof(EState));
	
	return iError;
}


int API MCTBoxAPI_FINModule_ParallelQueryFinBoard24PortsState(BYTE 		ucFinBoardID, 					 
															  EState 	eFin24PortsState[24],
															  char 		*sErrorMesg)
{
	int iError = 0;
	char sFinCmd[64] 			= {0}, 
		 sFinResponse[64] 		= {0}, 
		 sError[256] 			= {0}, 
		 sFin24PortsState[32] 	= {0},
		 sFinSinglePortState[4] = {0};
	
	char *pColonSubStr = NULL;
	UINT uiPosOfSpace_In_ColonSubStr = 0, uiPosOfSigh_In_ColonSubStr = 0;
	
	sprintf(sFinCmd, "$FIN 0x%02X:* STATe?!", ucFinBoardID);
	iError = MCTBoxAPI_Request(sFinCmd, sFinResponse);
	if (iError)
	{
		iError = MCTBoxAPI_IsCommunicationError(sError);
		sprintf(sErrorMesg, "%s", sError);
		return iError;
	}
	
	pColonSubStr = strstr(sFinResponse, ":*");
	if (!pColonSubStr)
	{
		sprintf(sErrorMesg, "%s", "Failed to get the 'FIN 24 ports command' response from MCTBox!");
		return -10;
	}
	uiPosOfSpace_In_ColonSubStr = strcspn(pColonSubStr, " ");
	uiPosOfSigh_In_ColonSubStr  = strcspn(pColonSubStr, "!");
	strncpy(sFin24PortsState, 
			pColonSubStr+uiPosOfSpace_In_ColonSubStr+1, 
			uiPosOfSigh_In_ColonSubStr-uiPosOfSpace_In_ColonSubStr-1);
	for (int i=0; i<24; i++)
	{
		strncpy(sFinSinglePortState, sFin24PortsState+i, 1);
		eFin24PortsState[23-i] = atoi(sFinSinglePortState);
	}
	
	return iError;
}


int API MCTBoxAPI_FINModule_FinPortListAddEntry(char sFinPortTokenName[],
												char sFinPortDescription[],
												char sFinPortConnector[],
												char sFinPortDeviceName[],
												BYTE ucFinBoardID,
												UINT uiFinPortChannelNr)
{
	return MCTBoxAPI_DIOModule_DoutPortListAddEntry(sFinPortTokenName, 
													sFinPortDescription, 
													sFinPortConnector,
													sFinPortDeviceName,
													ucFinBoardID,
													uiFinPortChannelNr);
}


int API MCTBoxAPI_FINModule_FinPortDeleteList(void)
{
	return MCTBoxAPI_DIOModule_DioPortDeleteList();
}

int API MCTBoxAPI_FINModule_QueryFinPortStateByToken(char 	sFinPortToken[],		   
													 EState *eFinPortState,
													 char 	*sErrorMesg)
{
	int iError = 0, iHitTargetFlag = 0;
	char sError[256] = {0};
	
	PDioPortNode_t pTempNode = pDioPortNode;
	while (NULL != pTempNode)
	{
		if (!strcmp(pTempNode->stDioPortToken.sDioPortTokenName, sFinPortToken))
		{
			iHitTargetFlag = 1;
			iError = MCTBoxAPI_FINModule_QueryFinPortState(pTempNode->stDioPortPhyAddr.ucDioBoardID,
														   pTempNode->stDioPortPhyAddr.uiDioPortNr,
														   eFinPortState,
														   sError);
			if (iError)
			{
				sprintf(sErrorMesg, "%s", sError);
				return iError;
			}
			break;
		}
		pTempNode = pTempNode->next;
	}
	if (0 == iHitTargetFlag)
	{
		sprintf(sErrorMesg, "Unknown '%s' token of FIN port!", sFinPortToken);
		return -10;
	}
	
	return iError;
}
