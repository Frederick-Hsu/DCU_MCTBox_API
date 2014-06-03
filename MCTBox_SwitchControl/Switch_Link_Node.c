/****************************************************************************************************
 * File name		: Switch_Link_Node.c
 * Description		: To implement the Switch-control by token, through the link node algorithm.
 * Creator			: XU ZAN	[HSE-OT]
 * Creation date	: Mon.	Dec. 30, 2013
 * Copyright(C)		2013	Hella Shanghai Electronics Co., Ltd.
 * All rights reserved.
 *
 ****************************************************************************************************/

//==============================================================================
// Macros :
#define SHARE_DIO_PORT_STRUCTURE_DEFINITION

//==============================================================================
// Include files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#if !defined (SHARE_DIO_PORT_STRUCTURE_DEFINITION)
	#include "Switch_Link_Node.h"
#else
	#include "../MCTBox_API_DIO.h"
	#include "../MCTBox_DIO/DIO_Link_Node.h"
#endif

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Global variables
#if !defined (SHARE_DIO_PORT_STRUCTURE_DEFINITION)
	static PSwitchLNode_t pSwitchNode = NULL;
#else
	extern PDioPortNode_t pDioPortNode;
#endif

//==============================================================================
// Static functions

//==============================================================================
// Functions implementation :
#if !defined (SHARE_DIO_PORT_STRUCTURE_DEFINITION)
	void AssignSwitch(PSwitchLNode_t	lpSwitchNode,
					  UCHAR				sSwitchTokenName[], 
					  UCHAR 			sSwitchDescription[],
					  UCHAR 			sSwitchConnector[],
					  UCHAR 			sSwitchDeviceName[],
					  BYTE				byteSwitchBoardID,
					  UINT				uiSwitchChannelNr)
	{			
		// Assign the "Switch Token Name"
		lpSwitchNode->sSwitchTokenName = (UCHAR *)malloc(sizeof(UCHAR) * (strlen(sSwitchTokenName)+1));
		sprintf(lpSwitchNode->sSwitchTokenName, "%s", sSwitchTokenName);
		// Assign the "Switch Description"
		lpSwitchNode->sSwitchDescription = (UCHAR *)malloc(sizeof(UCHAR) * (strlen(sSwitchDescription)+1));
		sprintf(lpSwitchNode->sSwitchDescription, "%s", sSwitchDescription);
		// Assign the "Switch Connector"
		lpSwitchNode->sSwitchConnector = (UCHAR *)malloc(sizeof(UCHAR) * (strlen(sSwitchConnector)+1));
		sprintf(lpSwitchNode->sSwitchConnector, "%s", sSwitchConnector);
		// Assign the "Switch Device Name"
		lpSwitchNode->sSwitchDeviceName = (UCHAR *)malloc(sizeof(UCHAR) * (strlen(sSwitchDeviceName)+1));
		sprintf(lpSwitchNode->sSwitchDeviceName, "%s", sSwitchDeviceName);
		// Assign the "Switch Board ID"
		lpSwitchNode->tSwitchPhyAddress.ucSwitchBoardID = byteSwitchBoardID;
		// Assign the "Switch Channel Number"
		lpSwitchNode->tSwitchPhyAddress.uiSwitchChannelNr = uiSwitchChannelNr;
	}
#endif

/******************************************************************************/
int API MCTBoxAPI_SwitchModule_SwitchListAddEntry(UCHAR sSwitchTokenName[], 
												  UCHAR sSwitchDescription[],
												  UCHAR sSwitchConnector[],
												  UCHAR sSwitchDeviceName[],
												  BYTE	byteSwitchBoardID,
												  UINT	uiSwitchChannelNr)
{
	int iResult = 0;
	#if !defined (SHARE_DIO_PORT_STRUCTURE_DEFINITION)
		PSwitchLNode_t pCurrentNode, pTemp = pSwitchNode, pNewNode = NULL;
	
		if (pSwitchNode == NULL)
		{
			pSwitchNode = (PSwitchLNode_t)malloc(sizeof(SwitchLNode_t));	// Create the head node
			if (pSwitchNode)
			{
				// Assign the Switch :
				AssignSwitch(pSwitchNode,
							 sSwitchTokenName,
							 sSwitchDescription,
							 sSwitchConnector,
							 sSwitchDeviceName,
							 byteSwitchBoardID,
							 uiSwitchChannelNr);
				// Assign the next node to NULL.
				pSwitchNode->next = NULL;
			
				return 0;	// OK
			}
			else
			{
				return -2;	// Memory overflow
			}
		}
	
		/* 
		 * Append a new tail node
		 */
		do
		{
			pCurrentNode = pTemp;	// Stage current node
			pTemp = pTemp->next;
		}
		while (pTemp != NULL);	// Move to the tail node
	
		pNewNode = (PSwitchLNode_t)malloc(sizeof(SwitchLNode_t));	// Create the new node
		if (pNewNode)
		{
			AssignSwitch(pNewNode, 
						 sSwitchTokenName, 
						 sSwitchDescription, 
						 sSwitchConnector, 
						 sSwitchDeviceName, 
						 byteSwitchBoardID, 
						 uiSwitchChannelNr);
			pNewNode->next = NULL;
		}
		else
		{
			return -2;
		}
		pCurrentNode->next = pNewNode;	// Insert as the tail node.
	#else					
		iResult = MCTBoxAPI_DIOModule_DoutPortListAddEntry(sSwitchTokenName,
														   sSwitchDescription,
														   sSwitchConnector,
														   sSwitchDeviceName,
														   byteSwitchBoardID,
														   uiSwitchChannelNr);
	#endif
	return iResult;
}

int API MCTBoxAPI_SwitchModule_SwitchDeleteList(void)
{
	int iResult = 0;
	#if !defined (SHARE_DIO_PORT_STRUCTURE_DEFINITION)
		PSwitchLNode_t pTemp = pSwitchNode;
	
		while (NULL != pTemp)
		{					
			pTemp = pTemp->next;	// Stage the new node
			free(pSwitchNode);		// Destroy current node
			pSwitchNode = pTemp;	// Move to next node
		}
		if (NULL != pSwitchNode)
			free(pSwitchNode);			// Destroy the tail node
	#else
		iResult = MCTBoxAPI_DIOModule_DioPortDeleteList();
	#endif
	return iResult;
}

/******************************************************************************/
int API MCTBoxAPI_SwitchModule_SetSwitch(UCHAR sSwitchTokenName[], char *sErrorMesg)
{
	int iResult = 0;
	#if !defined (SHARE_DIO_PORT_STRUCTURE_DEFINITION)
		PSwitchLNode_t pTemp = pSwitchNode;
		int iHitTargetFlag = 0, iError = 0;
		char sError[256] = {0};
	
		while(pTemp != NULL)
		{
			if (!strcmp(pTemp->sSwitchTokenName, sSwitchTokenName))
			{
				iHitTargetFlag = 1;
				iError = MCTBoxAPI_SwitchModule_OpenCloseSwitch(pTemp->tSwitchPhyAddress.ucSwitchBoardID,
																pTemp->tSwitchPhyAddress.uiSwitchChannelNr,
																ON,
																sError);
				if (iError)
				{
					sprintf(sErrorMesg, "%s", sError);
					return iError;
				}
			}
		
			pTemp = pTemp->next;	// next node
		}
		if (iHitTargetFlag != 1)	// Check the token existed.
		{
			sprintf(sErrorMesg, "No '%s' switch token existed", sSwitchTokenName);
			return -10;		// Token NOT found.
		}
	#else
		PDioPortNode_t pTemp = pDioPortNode;
		int iHitTargetFlag = 0;
		char sError[256] = {0};
	
		while (pTemp != NULL)
		{
			if (!strcmp(pTemp->stDioPortToken.sDioPortTokenName, sSwitchTokenName))
			{
				iHitTargetFlag = 1;
				iResult = MCTBoxAPI_SwitchModule_OpenCloseSwitch(pTemp->stDioPortPhyAddr.ucDioBoardID,
																 pTemp->stDioPortPhyAddr.uiDioPortNr,
																 ON,
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
			sprintf(sErrorMesg, "No '%s' switch token existed", sSwitchTokenName);
			return -10;
		}
	#endif
	
	return iResult;
}

/******************************************************************************/
int API MCTBoxAPI_SwitchModule_ResetSwitch(UCHAR sSwitchTokenName[], char *sErrorMesg)
{
	int iResult = 0;
	#if !defined (SHARE_DIO_PORT_STRUCTURE_DEFINITION)
		PSwitchLNode_t pTemp = pSwitchNode;
		int iHitTargetFlag = 0, iError = 0;
		char sError[256] = {0};
	
		while(pTemp != NULL)
		{
			if (!strcmp(pTemp->sSwitchTokenName, sSwitchTokenName))
			{
				iHitTargetFlag = 1;
				iError = MCTBoxAPI_SwitchModule_OpenCloseSwitch(pTemp->tSwitchPhyAddress.ucSwitchBoardID,
																pTemp->tSwitchPhyAddress.uiSwitchChannelNr,
																OFF,
																sError);
				if (iError)
				{
					sprintf(sErrorMesg, "%s", sError);
					return iError;
				}
			}
		
			pTemp = pTemp->next;	// next node
		}
		if (iHitTargetFlag != 1)	// Check the token existed.
		{
			sprintf(sErrorMesg, "Unknown '%s' switch token.", sSwitchTokenName);
			return -10;		// Token NOT found.
		}
	#else
		PDioPortNode_t pTemp = pDioPortNode;
		int iHitTargetFlag = 0;
		char sError[256] = {0};
	
		while (pTemp != NULL)
		{
			if (!strcmp(pTemp->stDioPortToken.sDioPortTokenName, sSwitchTokenName))
			{
				iHitTargetFlag = 1;
				iResult = MCTBoxAPI_SwitchModule_OpenCloseSwitch(pTemp->stDioPortPhyAddr.ucDioBoardID,
																 pTemp->stDioPortPhyAddr.uiDioPortNr,
																 OFF,
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
			sprintf(sErrorMesg, "Unknown '%s' switch token.", sSwitchTokenName);
			return -10;
		}
	#endif
	return 0;
}

/******************************************************************************/
int API MCTBoxAPI_SwitchModule_OutValve(char sSwitchTokenName[], EState eValveState, char *sErrorMesg)
{
	int iResult = 0;   
	#if !defined (SHARE_DIO_PORT_STRUCTURE_DEFINITION)
		PSwitchLNode_t pTemp = pSwitchNode;
		int iHitTargetFlag = 0;
		char sError[256] = {0};
	
		while (pTemp != NULL)
		{
			if (!strcmp(pTemp->sSwitchTokenName, sSwitchTokenName))
			{
				iHitTargetFlag = 1;
				iResult = MCTBoxAPI_SwitchModule_OpenCloseSwitch(pTemp->tSwitchPhyAddress.ucSwitchBoardID,
																 pTemp->tSwitchPhyAddress.uiSwitchChannelNr,
																 eValveState,
																 sError);
			}
			if (iResult)
			{
				sprintf(sErrorMesg, "%s", sError);
				return iResult;
			}
			pTemp = pTemp->next;	// next node
		}
		if (iHitTargetFlag != 1)
		{
			sprintf(sErrorMesg, "Unknown '%s' switch token.", sSwitchTokenName);
			return -10;		// Token NOT found.
		}											
	#else
		PDioPortNode_t pTemp = pDioPortNode;
		int iHitTargetFlag = 0;
		char sError[256] = {0};
	
		while (pTemp != NULL)
		{
			if (!strcmp(pTemp->stDioPortToken.sDioPortTokenName, sSwitchTokenName))
			{
				iHitTargetFlag = 1;
				iResult = MCTBoxAPI_SwitchModule_OpenCloseSwitch(pTemp->stDioPortPhyAddr.ucDioBoardID,
																 pTemp->stDioPortPhyAddr.uiDioPortNr,
																 eValveState,
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
			sprintf(sErrorMesg, "Unknown '%s' switch token.", sSwitchTokenName);
			return -10;
		}
	#endif
	return iResult;
}
