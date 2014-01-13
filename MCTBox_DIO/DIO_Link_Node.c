/******************************************************************************************************************
 * File name		: DIO_Link_Node.c
 * Description		: To implement the link-node structure & algorithm, by defining the tokens to access
 *					  the corresponding DIO ports.
 * Creator			: XU ZAN	[HSE-OT]
 * Creation date	: Mon.	Jan. 06, 2014
 * Copyright(C)		2014	Hella Shanghai Electronics Co., Ltd.
 * All rights reserved.
 *
 ******************************************************************************************************************/

//==============================================================================
// Include files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DIO_Link_Node.h"
#include "../MCTBox_API_DIO.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
static PDioPortNode_t pDioPortNode = NULL;

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions
int API MCTBoxAPI_DIOModule_DoutPortListAddEntry(char sDoutPortTokenName[],
												 char sDoutPortDescription[],
												 char sDoutPortConnector[],
												 char sDoutPortDeviceName[],
												 BYTE bytDoutBoardID,
												 UINT uiDoutPortChannelNr)
{
	int iResult = 0;
	PDioPortNode_t pTemp = pDioPortNode, pCurrentNode = NULL, pNewNode = NULL;
	
	if (pDioPortNode == NULL)
	{
		pDioPortNode = (PDioPortNode_t)malloc(sizeof(DioPortNode_t));
		if (pDioPortNode == NULL)
		{
			return -2;	// Memory overflow
		}
		else
		{
			AssignDioPortNode(pDioPortNode, 
							  sDoutPortTokenName, 
							  sDoutPortDescription,
							  sDoutPortConnector,
							  sDoutPortDeviceName, 
							  bytDoutBoardID, 
							  uiDoutPortChannelNr);
			pDioPortNode->next = NULL;
			return 0;
		}
	}
	
	do
	{
		pCurrentNode = pTemp;
		pTemp = pTemp->next;
	}
	while (pTemp != NULL);
	
	pNewNode = (PDioPortNode_t)malloc(sizeof(DioPortNode_t));
	if (pNewNode == NULL)
		return -2;
	AssignDioPortNode(pNewNode,
					  sDoutPortTokenName,
					  sDoutPortDescription,
					  sDoutPortConnector,
					  sDoutPortDeviceName,
					  bytDoutBoardID,
					  uiDoutPortChannelNr);
	pNewNode->next = NULL;   
	pCurrentNode->next = pNewNode;		// Insert as the tail node
	
	return iResult;
}

int API MCTBoxAPI_DIOModule_DinPortListAddEntry(char sDinPortTokenName[],
												char sDinPortDescription[],
												char sDinPortConnector[],
												char sDinPortDeviceName[],
												BYTE bytDinBoardID,
												UINT uiDinPortChannelNr)
{
	int iResult = 0;
	iResult = MCTBoxAPI_DIOModule_DoutPortListAddEntry(sDinPortTokenName,
													   sDinPortDescription,
													   sDinPortConnector,
													   sDinPortDeviceName,
													   bytDinBoardID,
													   uiDinPortChannelNr);
	return iResult;
}

int API MCTBoxAPI_DIOModule_DioPortDeleteList(void)
{
	int iResult = 0;
	PDioPortNode_t pTemp = pDioPortNode;
	
	while (pTemp != NULL)
	{
		pTemp = pTemp->next;
		free(pDioPortNode);
		pDioPortNode = pTemp;
	}
	free(pDioPortNode);
	
	return iResult;
}

void AssignDioPortNode(PDioPortNode_t 	lpDioPortNode,					
					   char 			sDoutPortTokenName[],  
					   char 			sDoutPortDescription[],
					   char 			sDoutPortConnector[],
					   char 			sDoutPortDeviceName[],
					   BYTE 			bytDoutBoardID,
					   UINT 			uiDoutPortChannelNr)
{
	lpDioPortNode->stDioPortToken.sDioPortTokenName 	= (char *)malloc(sizeof(char)*(strlen(sDoutPortTokenName)+1));
	lpDioPortNode->stDioPortToken.sDioPortDescription 	= (char *)malloc(sizeof(char)*(strlen(sDoutPortDescription)+1));
	lpDioPortNode->stDioPortToken.sDioPortConnector 	= (char *)malloc(sizeof(char)*(strlen(sDoutPortConnector)+1));
	lpDioPortNode->stDioPortToken.sDioPortDeviceName 	= (char *)malloc(sizeof(char)*(strlen(sDoutPortDeviceName)+1));
	
	sprintf(lpDioPortNode->stDioPortToken.sDioPortTokenName, 	"%s", sDoutPortTokenName);
	sprintf(lpDioPortNode->stDioPortToken.sDioPortDescription, 	"%s", sDoutPortDescription);
	sprintf(lpDioPortNode->stDioPortToken.sDioPortConnector, 	"%s", sDoutPortConnector);
	sprintf(lpDioPortNode->stDioPortToken.sDioPortDeviceName, 	"%s", sDoutPortDeviceName);
	
	lpDioPortNode->stDioPortPhyAddr.ucDioBoardID 		= bytDoutBoardID;
	lpDioPortNode->stDioPortPhyAddr.uiDioPortNr			= uiDoutPortChannelNr; 
	
	return;
}

int API MCTBoxAPI_DIOModule_SetDoutPortHighLowByToken(char sDoutPortToken[], EState eDoutPortState, char *sErrorMesg)
{
	int iResult = 0, iHitTargetFlag = 0;
	char sError[256] = {0};
	PDioPortNode_t pTemp = pDioPortNode;
	
	while (pTemp != NULL)
	{
		if (!strcmp(pTemp->stDioPortToken.sDioPortTokenName, sDoutPortToken))
		{
			iHitTargetFlag = 1;
			iResult = MCTBoxAPI_DIOModule_SetDoutPortHighLow(pTemp->stDioPortPhyAddr.ucDioBoardID,
															 pTemp->stDioPortPhyAddr.uiDioPortNr,
															 eDoutPortState,
															 sError);
			if (iResult)
			{
				sprintf(sErrorMesg, "%s", sError);
				return iResult;
			}
		}
		pTemp = pTemp->next;
	}
	if (iHitTargetFlag != 1)
	{
		sprintf(sErrorMesg, "Unknown '%s' token of DIO port!", sDoutPortToken);
		return -10;
	}
	
	return iResult;
}

int API MCTBoxAPI_DIOModule_QueryDinPortStateByToken(char sDinPortToken[], EState *eDinPortState, char *sErrorMesg)
{
	int iResult = 0, iHitTargetFlag = 0;
	char sError[256] = {0};
	PDioPortNode_t pTemp = pDioPortNode;
	
	while (pTemp != NULL)
	{
		if (!strcmp(pTemp->stDioPortToken.sDioPortTokenName, sDinPortToken))
		{
			iHitTargetFlag = 1;
			iResult = MCTBoxAPI_DIOModule_QueryDinPortState(pTemp->stDioPortPhyAddr.ucDioBoardID,
															pTemp->stDioPortPhyAddr.uiDioPortNr,
															eDinPortState,
															sError);
			if (iResult)
			{
				sprintf(sErrorMesg, "%s", sError);
				return iResult;
			}
			/* NOTE : Digital-IN token does not support the duplicate token name,
			 * Otherwise, you cannot distinguish which token is corresponding to his state.
			 * 
			 * Remarked by XU ZAN@2014-01-06
			 */
			break;	
		}
		pTemp = pTemp->next;
	}
	if (iHitTargetFlag != 1)
	{
		sprintf(sErrorMesg, "Unknown '%s' token of DIO port!", sDinPortToken);
		return -10;
	}
	
	return iResult;
}
