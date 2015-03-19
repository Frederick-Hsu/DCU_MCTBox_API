/*******************************************************************************************
 * File name		: MCTBox_API_PWM.h
 * Description		: To provide the API functions to access the PWM module of MCTBox.
 * Creator			: XU ZAN	[HSE-OT]
 * Creation date	: Thur.		June 26, 2014
 * Copyright(C)		2014	Hella Shanghai Electronics Co., Ltd.
 * All rights reserved.
 *
 *******************************************************************************************/

#ifndef MCTBOX_API_PWM_H
#define MCTBOX_API_PWM_H

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
			int API MCTBoxAPI_PWMModule_ConfigPwmOutCh1(int 	iFreq,			// unit : Hz
														float	fDutyCycle,		// range : 0<=duty cycle<=1
														float	fVoltage,		// unit : volt
														char	*sError);
			int API MCTBoxAPI_PWMModule_StartPwmOutCh1();
			int API MCTBoxAPI_PWMModule_StopPwmOutCh1(void);
			
			int API MCTBoxAPI_PWMModule_ConfigPwmOutCh2(int 	iFreq,			// unit : Hz
														float	fDutyCycle,		// range : 0>=duty cycle<=1
														float	fVoltage,		// unit : volt
														char	*sError);
			int API MCTBoxAPI_PWMModule_StartPwmOutCh2();
			int API MCTBoxAPI_PWMModule_StopPwmOutCh2(void);
			
	#ifdef __cplusplus
	    }
	#endif

#endif  /* ndef MCTBOX_API_PWM_H */
