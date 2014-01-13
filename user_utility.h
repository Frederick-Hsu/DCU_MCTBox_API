/**************************************************************************************************************************************
 * File name		: user_utility.h
 * Description		: Define and implement some user utility functions, as the tool box here, in order to call freely.
 * Creator			: XU ZAN	[HSE-OT]
 * Creation date	: Mon.	Dec. 30, 2013
 * Copyright(C)		2013	Hella Shanghai Electronics Co., Ltd.
 * All rights reserved.*
 
 **************************************************************************************************************************************/

#ifndef USER_UTILITY_H
#define USER_UTILITY_H

	#ifdef __cplusplus
	    extern "C" 
		{
	#endif

			//==============================================================================
			// Include files

			//==============================================================================
			// Constants

			//==============================================================================
			// Types

			//==============================================================================
			// External variables

			//==============================================================================
			// Functions prototype :
			int ParseTokenList(char sARGIN_TokenListStr[], char *sARGOUT_TokenArray[], int *iNumOfToken);

	#ifdef __cplusplus
	    }
	#endif

#endif  /* ndef USER_UTILITY_H */
