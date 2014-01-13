/**************************************************************************************************************************************
 * File name		: user_utility.h
 * Description		: Define and implement some user utility functions, as the tool box here, in order to call freely.
 * Creator			: XU ZAN	[HSE-OT]
 * Creation date	: Mon.	Dec. 30, 2013
 * Copyright(C)		2013	Hella Shanghai Electronics Co., Ltd.
 * All rights reserved.*
 
 **************************************************************************************************************************************/

//==============================================================================
// Include files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user_utility.h"

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

//==============================================================================
// Functions implementation :
int ParseTokenList(char sARGIN_TokenListStr[], char *sARGOUT_TokenArray[], int *iNumOfToken)
{
	int iCnt = 0;
	int iPosOfComma = strcspn(sARGIN_TokenListStr, ",");	// The position of 1st comma ','
	char sCurrentTokenStr[128] = {0}, sRestStr[512] = {0}, sTempStr[512] = {0};
	
	if (iPosOfComma == strlen(sARGIN_TokenListStr))		// It indicated that only 1 token was defined
	{
		*iNumOfToken = 1;
		sARGOUT_TokenArray[0] = (char *)malloc((strlen(sARGIN_TokenListStr)+1)*sizeof(char));
		sprintf(sARGOUT_TokenArray[0], "%s", sARGIN_TokenListStr);
		return 0;	// OK
	}
	
	sprintf(sRestStr, "%s", sARGIN_TokenListStr);
	iCnt = 0;
	do
	{
		iPosOfComma = strcspn(sRestStr, ",");
		strncpy(sCurrentTokenStr, sRestStr, iPosOfComma);
		
		{	// Assign to Token array
			sARGOUT_TokenArray[iCnt] = (char *)malloc((strlen(sCurrentTokenStr)+1)*sizeof(char));
			sprintf(sARGOUT_TokenArray[iCnt], "%s", sCurrentTokenStr);
			++iCnt;
		}
		memset(sCurrentTokenStr, 0, (strlen(sCurrentTokenStr)+1));	// Clean current token string, wait for next token.
		// sprintf(sCurrentTokenStr, "%s", "");	// This clean method will bring some side effect, it could be assigned the wrong string at the end.
		
		{	// Cut off the rest string after current separator ','
			strncpy(sTempStr, sRestStr+iPosOfComma+1, strlen(sRestStr)-iPosOfComma-1); 
			// sprintf(sRestStr, "%s", "");	
			memset(sRestStr, 0, (strlen(sRestStr)+1));	// Clean current rest string
			strcpy(sRestStr, sTempStr);		// Assign the new rest string
			// sprintf(sTempStr, "%s", "");	
			memset(sTempStr, 0, (strlen(sTempStr)+1));	// Clean current temp string, wait for next
		}
	}
	while (strstr(sRestStr, ","));	// Till the last comma separator.
	// For last token
	if (0 != strlen(sRestStr))	// Make sure the rest str is valid, avoid the influence of last comma.
	{
		sARGOUT_TokenArray[iCnt] = (char *)malloc((strlen(sRestStr)+1)*sizeof(char));
		sprintf(sARGOUT_TokenArray[iCnt], "%s", sRestStr);
		*iNumOfToken = iCnt+1;	// Please note that the number of parsed token should be iCnt+1, not iCnt.	Remarked by XU ZAN@2014-01-08
	}
	else
	{						  
		*iNumOfToken = iCnt;
	}
	return 0;
}
