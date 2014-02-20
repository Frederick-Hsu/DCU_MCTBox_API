/****************************************************************************************************************
 * File name		: AIO_Channel_LinkNode.h
 * Description		: Define the link list node of AIO channel.
 * Creator			: XU ZAN
 * Creation date	: Mon.	Feb. 17, 2014
 * Copyright(C)		2014	Hella Shanghai Electronics Co., Ltd.
 * All rights reserved.
 *
 ****************************************************************************************************************/

#ifndef AIO_CHANNEL_LINKNODE_H
#define AIO_CHANNEL_LINKNODE_H

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
			struct AdcChAttr
			{
				char 	*sAdcToken;
				char 	*sAdcDescription;
				char 	*sAdcConnector;
				char 	*sAdcDeviceName;
				int 	iAdcChNr;
				float 	fAdcShuntResistorInOhm;
			};
			
			typedef struct AdcChLinkList
			{
				struct AdcChAttr tMeasChannel;
				struct AdcChLinkList *next;
			}
			ADC_CH_LinkNode_t, *PADC_CH_LinkNode_t;

			//==============================================================================
			// External variables

			//==============================================================================
			// Global functions
			void AssignMeasChannelNode(PADC_CH_LinkNode_t 	pCurrentNode,
									   char 				sMeasTokenName[],
									   char					sMeasDescription[],
									   char					sMeasConnector[],
									   char					sMeasDeviceName[],
									   int					iMeasChannelNr,
									   float				fMeasShuntResistorInOhm);

	#ifdef __cplusplus
	    }
	#endif

#endif  /* ndef AIO_CHANNEL_LINKNODE_H */
