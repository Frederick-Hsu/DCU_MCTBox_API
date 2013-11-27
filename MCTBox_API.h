/************************************************************************************************************
 * File name	: MCTBox_API.h
 * Description	: To provide the API accessing portal for the MCTBox_API library project.
 * Creator		: XU ZAN	[HSe-OT]
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
			void API MCTBoxAPI_Version(char *sMCTBox_VersionInfo);
			/*******************************************************************************/
			int API MCTBoxAPI_Init(int iComPortNr, char *sARGOUT_ComError);
			int API MCTBoxAPI_Exit(char *sARGOUT_ComError);
			
	#ifdef __cplusplus
	    }
	#endif

#endif  /* ndef MCTBOX_API_H */
