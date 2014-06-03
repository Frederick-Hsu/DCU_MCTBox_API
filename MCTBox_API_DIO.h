/********************************************************************************************************
 * File name		: MCTBox_API_DIO.h
 * Description		: To provide the APIs for accessing the DIO module of MCTBox instrument.
 * Creator			: XU ZAN
 * Creation date	: Fri.	Dec. 27, 2013
 * Copyright(C)		2013	Hella Shanghai Electronics Co., Ltd.
 * All rights reserved.
 *
 ********************************************************************************************************/

#ifndef MCTBOX_API_DIO_H
#define MCTBOX_API_DIO_H

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
			// Functions implementation :
			int API MCTBoxAPI_DIOModule_SetDoutPortHighLow(BYTE 	ucDoutBoardID,	// Board ID range : [0x01, 0xFF]
														   UINT 	uiDoutPortNr,	// Port number range : [1, 24]
														   EState 	eDoutPortState,	// HIGH=1,  LOW=0
														   char 	*sErrorMesg);
			
			int API MCTBoxAPI_DIOModule_QueryDinPortState(UINT 		uiDinPortNr,	// Port number : [1, 24]
														  EState 	*eDinPortState,	// Port state returned
														  char 		*sErrorMesg);
			
			int API MCTBoxAPI_DIOModule_ParallelQueryDin24PortsState(EState eDin24PortsState[24],	// 24 ports' state
																	 char 	*sErrorMesg);
			
			int API MCTBoxAPI_DIOModule_DoutPortListAddEntry(char sDoutPortTokenName[],
															 char sDoutPortDescription[],
															 char sDoutPortConnector[],
															 char sDoutPortDeviceName[],
															 BYTE bytDoutBoardID,			// Board ID range : [0x01, 0xFF]
															 UINT uiDoutPortChannelNr);		// Port number range : [1, 24]
			
			int API MCTBoxAPI_DIOModule_DinPortListAddEntry(char sDinPortTokenName[],
															char sDinPortDescription[],
															char sDinPortConnector[],
															char sDinPortDeviceName[],
															BYTE bytDinBoardID,				// this board ID is not used. Default is 0x00
															UINT uiDinPortChannelNr);		// Port number range : [1, 24]
			
			int API MCTBoxAPI_DIOModule_DioPortDeleteList(void);
			
			int API MCTBoxAPI_DIOModule_SetDoutPortHighLowByToken(char 		sDoutPortToken[], 
																  EState 	eDoutPortState, 
																  char 		*sErrorMesg);
			
			int API MCTBoxAPI_DIOModule_QueryDinPortStateByToken(char 		sDinPortToken[], 
																 EState 	*eDinPortState, 
																 char 		*sErrorMesg);
			
			
			//==============================================================================
			// Test Functions implementation :
			void API MCTBOxAPI_TF_DIOModule_SetDoutPortHighLow(int hThisStep);
			void API MCTBoxAPI_TF_DIOModule_GetDinPortState(int hThisStep);
			void API MCTBoxAPI_TF_DIOModule_ParallelGetDin24PortsStates(int hThisStep);
			void API MCTBoxAPI_TF_DIOModule_SetDoutPortHighLowByTokens(int hThisStep);
			void API MCTBoxAPI_TF_DIOModule_GetDinPortStateByToken(int hThisStep);
			
			void API MCTBoxAPI_RegisterDIOModuleTFSteps(void);

	#ifdef __cplusplus
	    }
	#endif

#endif  /* ndef MCTBOX_API_DIO_H */
