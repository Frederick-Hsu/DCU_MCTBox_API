/*****************************************************************************************************************
 * File name		: MCTBox_API_FIN.h
 * Description		: To rpovide the APIs for accessing the Optical-couple Input board of MCTBox instrument.
 * Creator			: XU ZAN
 * Creation date	: Tue.	Apr. 01, 2014
 * Copyright(C)		2014	Hella Shanghai Electronics Co., Ltd.
 * All rights reserved.
 *
 *****************************************************************************************************************/

#ifndef MCTBOX_API_FIN_H
#define MCTBOX_API_FIN_H

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
			// Global functions
			int API MCTBoxAPI_FINModule_QueryFinPortState(BYTE 		ucFinBoardID,
														  UINT 		uiFinPortNr,
														  EState 	*eFinPortState,
														  char 		*sErrorMesg);
			
			int API MCTBoxAPI_FINModule_ParallelQueryFinBoard24PortsState(BYTE 		ucFinBoardID, 
																		  EState 	eFin24PortsState[24],
																		  char 		*sErrorMesg);
			
			int API MCTBoxAPI_FINModule_FinPortListAddEntry(char sFinPortTokenName[],
															char sFinPortDescription[],
															char sFinPortConnector[],
															char sFinPortDeviceName[],
															BYTE ucFinBoardID,
															UINT uiFinPortChannelNr);
			
			int API MCTBoxAPI_FINModule_FinPortDeleteList(void);
			
			int API MCTBoxAPI_FINModule_QueryFinPortStateByToken(char 	sFinPortToken[],
																 EState *eFinPortState,
																 char 	*sErrorMesg);
			
			#if defined (SUT_SEQUENZER)
				//==============================================================================
				// Test Functions implementation :
				void API MCTBoxAPI_TF_FINModule_QueryFinPortState(int hThisStep);
				void API MCTBoxAPI_TF_FINModule_ParallelQueryFinBoard24PortsState(int hThisStep);
				void API MCTBoxAPI_TF_FINModule_QueryFinPortStateByToken(int hThisStep);
			
				void API MCTBoxAPI_RegisterFINModuleTFSteps(void);
			#endif
	
	#ifdef __cplusplus
	    }
	#endif

#endif  /* ndef MCTBOX_API_FIN_H */
