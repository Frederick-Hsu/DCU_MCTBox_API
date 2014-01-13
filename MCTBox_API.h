/************************************************************************************************************
 * File name	: MCTBox_API.h
 * Description	: To provide the API accessing portal for the MCTBox_API library project.
 * Creator		: XU ZAN	[HSE-OT]
 * Creation date: Mon.	Nov. 25, 2013
 * Copyright(C)		2013	Hella Shanghai Electronics Co., Ltd.
 * 
 ************************************************************************************************************/

#ifndef MCTBOX_API_H
#define MCTBOX_API_H

	#ifdef __cplusplus
	    extern "C" 
		{
	#endif
			//==============================================================================
			// Include files
			#include "MCTBox_API_import_export.h"

			//==============================================================================
			// Constants

			//==============================================================================
			// Types

			//==============================================================================
			// External variables

			//==============================================================================
			// Functions prototype :
			void API MCTBoxAPI_Bio(char *sMCTBox_BioInfo);
			void API MCTBoxAPI_LibraryVersion(char *sMCTBox_LibraryVersionInfo);
			
			/*******************************************************************************/
			int API MCTBoxAPI_Init(int iComPortNr, char *sARGOUT_ComError);
			int API MCTBoxAPI_SayHello2MCTBox(char *sARGOUT_MCTBoxResponse);
			int API MCTBoxAPI_Exit(char *sARGOUT_ComError);
			
			/*******************************************************************************/
			int API MCTBoxAPI_Transmit(char sARGIN_TxCommand[]);
			int API MCTBoxAPI_Receive(char *sARGOUT_RxResponse);
			int API MCTBoxAPI_Request(char sARGIN_TxCommand[], char *sARGOUT_RxResponse);
			int API MCTBoxAPI_IsCommunicationError(char *sARGOUT_CommunicationError);
			
			int API MCTBoxAPI_IsExecutionError(char *sARGOUT_ExecutionError);
			void API MCTBoxAPI_FirmwareVersion(char *sMCTBox_FirmwareVersionInfo);
			
			
			//==============================================================================
			// Test Functions prototype :
			void API MCTBoxAPI_TF_Init(int hThisStep);
			void API MCTBoxAPI_TF_Exit(int hThisStep);
			void API MCTBoxAPI_TF_SayHello2MCTBox(int hThisStep);
			void API MCTBoxAPI_TF_Transmit(int hThisStep);
			void API MCTBoxAPI_TF_Receive(int hThisStep);
			void API MCTBoxAPI_TF_Request(int hThisStep);
			void API MCTBoxAPI_TF_IsExecutionError(int hThisStep);
			void API MCTBoxAPI_TF_FirmwareVersion(int hThisStep);
			
			void API MCTBoxAPI_RegisterCommonTFSteps(void);
			
	#ifdef __cplusplus
	    }
	#endif

#endif  /* ndef MCTBOX_API_H */
