/******************************************************************************************************************
 * File name		: DIO_Link_Node.c
 * Description		: To implement the link-node structure & algorithm, by defining the tokens to access
 *					  the corresponding DIO ports.
 * Creator			: XU ZAN	[HSE-OT]
 * Creation date	: Mon.	Jan. 06, 2014
 * Copyright(C)		2014	Hella Shanghai Electronics Co., Ltd.
 * All rights reserved.
 *
 ******************************************************************************************************************/

#ifndef DIO_LINK_NODE_H
#define DIO_LINK_NODE_H

	#ifdef __cplusplus
	    extern "C" 
		{
	#endif

			//==============================================================================
			// Include files
			#include "../MCTBox_API_SwitchControl.h"

			//==============================================================================
			// Constants

			//==============================================================================
			// Types
			typedef struct DIO_Port
			{
				BYTE ucDioBoardID;
				UINT uiDioPortNr;
			}
			DioPort_t, *PDioPort_t;
			
			typedef struct DIO_Port_Token
			{
				char *sDioPortTokenName;
				char *sDioPortDescription;
				char *sDioPortConnector;
				char *sDioPortDeviceName;
			}
			DioPortToken_t, *PDioPortToken_t;
			
			typedef struct Dio_Port_Node
			{
				DioPortToken_t stDioPortToken;
				DioPort_t stDioPortPhyAddr;
				
				struct Dio_Port_Node *next;
			}
			DioPortNode_t, *PDioPortNode_t;

			//==============================================================================
			// External variables

			//==============================================================================
			// Global functions
			void AssignDioPortNode(PDioPortNode_t 	lpDioPortNode,
								   char 			sDoutPortTokenName[],  
								   char 			sDoutPortDescription[],
								   char 			sDoutPortConnector[],
								   char 			sDoutPortDeviceName[],
								   BYTE 			bytDoutBoardID,
								   UINT 			uiDoutPortChannelNr);

	#ifdef __cplusplus
	    }
	#endif

#endif  /* ndef DIO_LINK_NODE_H */
