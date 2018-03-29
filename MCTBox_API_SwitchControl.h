/********************************************************************************************************
 * File name		: MCTBox_API_SwitchControl.h
 * Description		: To provide the APIs for accessing the SwitchControl module of MCTBox instrument.
 * Creator			: XU ZAN
 * Creation date	: Fri.	Dec. 27, 2013
 * Copyright(C)		2013	Hella Shanghai Electronics Co., Ltd.
 * All rights reserved.
 *
 ********************************************************************************************************/

#ifndef MCTBOX_API_SWITCHCONTROL_H
#define MCTBOX_API_SWITCHCONTROL_H

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
			typedef struct Switch
			{
				BYTE ucSwitchBoardID;
				UINT uiSwitchChannelNr;
				EState eSwitchState;
			}
			Switch_t, *PSwitch_t;

			//==============================================================================
			// External variables

			//==============================================================================
			// Functions protype :
			int API MCTBoxAPI_SwitchModule_OpenCloseSwitch(BYTE 	ucSwitchBoardID,		// Board ID range : [0x01, 0xFF] 
														   UINT 	uiSwitchChannelNr, 		// Channel number range: [1, 24]
														   EState 	eSwitchState,			// 0=Switch OFF; 1=Switch ON
														   char 	*sErrorMesg);
			
			int API MCTBoxAPI_SwitchModule_ClearAllSwitches(BYTE ucSwitchBoardID, char *sErrorMesg);
			int API MCTBoxAPI_SwitchModule_SetAllSwitches(BYTE ucSwitchBoardID, char *sErrorMesg);   
			
			int API MCTBoxAPI_SwitchModule_OpenCloseMultiSwitches(PSwitch_t ptSwitch1, ...);	// Note: Please set the last argument to 'NULL' when calling
			
			int API MCTBoxAPI_SwitchModule_SwitchListAddEntry(UCHAR sSwitchTokenName[],
															  UCHAR sSwitchDescription[],
															  UCHAR sSwitchConnector[],
															  UCHAR sSwitchDeviceName[],
															  BYTE	byteSwitchBoardID,
															  UINT	uiSwitchChannelNr);
			int API MCTBoxAPI_SwitchModule_SwitchDeleteList(void);
			
			int API MCTBoxAPI_SwitchModule_SetSwitch(UCHAR sSwitchTokenName[], char *sErrorMesg);
			int API MCTBoxAPI_SwitchModule_ResetSwitch(UCHAR sSwitchTokenName[], char *sErrorMesg);
			
			int API MCTBoxAPI_SwitchModule_OutValve(char sSwitchTokenName[], EState eValveState, char *sErrorMesg);
			
			
			
			#if defined (SUT_SEQUENZER)
				//==============================================================================
				// Test Functions protype :
				void API MCTBoxAPI_TF_SwitchModule_OpenCloseSwitch(int hThisStep);
				void API MCTBoxAPI_TF_SwitchModule_ClearAllSwitches(int hThisStep);
				void API MCTBoxAPI_TF_SwitchModule_SetAllSwitches(int hThisStep);
				void API MCTBoxAPI_TF_SwitchModule_SetResetSwitch(int hThisStep);
			
				void API MCTBoxAPI_RegisterSwitchModuleTFSteps(void);
			#endif

	#ifdef __cplusplus
	    }
	#endif

#endif  /* ndef MCTBOX_API_SWITCHCONTROL_H */
