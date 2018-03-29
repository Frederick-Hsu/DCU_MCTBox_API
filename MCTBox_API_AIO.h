/********************************************************************************************************
 * File name		: MCTBox_API_AIO.h
 * Description		: To provide the APIs for accessing the AIO module of MCTBox instrument.
 * Creator			: XU ZAN
 * Creation date	: Fri.	Dec. 27, 2013
 * Copyright(C)		2013	Hella Shanghai Electronics Co., Ltd.
 * All rights reserved.
 *
 ********************************************************************************************************/

#ifndef MCTBOX_API_AIO_H
#define MCTBOX_API_AIO_H

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
			typedef enum
			{
				MCTBox_ADC_CH1 = 1,
				MCTBox_ADC_CH2 = 2,
				MCTBox_ADC_CH3 = 3,
				MCTBox_ADC_CH4 = 4,
				MCTBox_ADC_CH5 = 5,
				MCTBox_ADC_CH6 = 6,
				MCTBox_ADC_CH7 = 7,
				MCTBox_ADC_CH8 = 8
			}
			EAdcChannel_t;

			//==============================================================================
			// External variables

			//==============================================================================
			// Functions prototype :
			int API MCTBoxAPI_AIOModule_AcquireVoltageOfAdcChannel(EAdcChannel_t 	eMCTBox_ADC_ChannelNr,
																   double 			*dARGOUT_AcquiredVoltageOfAdcChannel,	// unit : Volt
																   char 			*sARGOUT_ErrorMesg);
			
			int API MCTBoxAPI_AIOModule_AcquireVoltagesOfAll8Channels(double dARGOUT_VoltagesOfAll8Channels[8],		// 8 voltage values of 8 ADC channels, unit : Volt 
																	  char 	 *sARGOUT_ErrorMesg);
			
			int API MCTBoxAPI_AIOModule_AcquireCurrentOfAdcChannel(EAdcChannel_t 	eMCTBox_ADC_CurrentChannelNr,
																   float 			fShuntResistorInOhm,					// unit : Ohm
																   double 			*dARGOUT_AcquiredCurrentOfAdcChannel,	// unit : Ampere
																   char 			*sARGOUT_ErrorMesg);
			
			int API MCTBoxAPI_AIOModule_MeasChannelListAddEntry(char 	sMeasTokenName[],
																char 	sMeasDescription[],
																char 	sMeasConnector[],
																char 	sMeasDeviceName[],
																int		iMeasChannelNr,
																float	fMeasShuntResistorInOhm);	// Default 0Ohm, just used in measuring current, ignore in measuring voltage
			int API MCTBoxAPI_AIOModule_DeleteMeasChannelList(void);
			
			int API MCTBoxAPI_AIOModule_MeasVoltageByToken(char 	sMeasTokenName[], 
														   double 	*dARGOUT_VoltageInV,
														   char 	*sARGOUT_ErrorMesg);
			
			int API MCTBoxAPI_AIOModule_MeasCurrentByToken(char 	sMeasTokenName[], 
														   float 	fMeasShuntResistorInOhm, 
														   double 	*dARGOUT_CurrentInA,
														   char		*sARGOUT_ErrorMesg);
			
			#if defined (SUT_SEQUENZER)
				//==============================================================================
				// Test Functions prototype :
				void API MCTBoxAPI_TF_AIOModule_AcquireVoltageOfAdcChannel(int hThisStep);
				void API MCTBoxAPI_TF_AIOMpdule_AcquireCurrentOfAdcChannel(int hThisStep);
				void API MCTBoxAPI_TF_AIOModule_MeasVoltageByToken(int hThisStep);
				void API MCTBoxAPI_TF_AIOModule_MeasCurrentByToken(int hThisStep);
			
				void API MCTBoxAPI_RegisterAIOModuleTFSteps(void);
			#endif
				
	#ifdef __cplusplus
	    }
	#endif

#endif  /* ndef MCTBOX_API_AIO_H */
