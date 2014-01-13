/****************************************************************************************************
 * File name		: Switch_Link_Node.h
 * Description		: To implement the Switch-control by token, through the link node algorithm.
 * Creator			: XU ZAN	[HSE-OT]
 * Creation date	: Mon.	Dec. 30, 2013
 * Copyright(C)		2013	Hella Shanghai Electronics Co., Ltd.
 * All rights reserved.
 *
 ****************************************************************************************************/

#ifndef SWITCH_LINK_NODE_H
#define SWITCH_LINK_NODE_H

	#ifdef __cplusplus
	    extern "C" 
		{
	#endif

			//==============================================================================
			// Include files
			#include "MCTBox_API_SwitchControl.h"

			//==============================================================================
			// Constants

			//==============================================================================
			// Types
			typedef struct SwitchPhyAddress
			{
				BYTE ucSwitchBoardID;
				UINT uiSwitchChannelNr;
			}
			SwitchPhyAddress_t, *PSwitchPhyAddress_t;
			
			
			typedef struct Switch_Link_Node
			{
				unsigned char *sSwitchTokenName;
				unsigned char *sSwitchDescription;
				unsigned char *sSwitchConnector;
				unsigned char *sSwitchDeviceName;
				SwitchPhyAddress_t tSwitchPhyAddress;
				
				struct Switch_Link_Node *next;
			}
			SwitchLNode_t, *PSwitchLNode_t;

			//==============================================================================
			// External variables

			//==============================================================================
			// Functions prototype :
			void AssignSwitch(PSwitchLNode_t	lpSwitchNode, 
							  UCHAR				sSwitchTokenName[], 
							  UCHAR 			sSwitchDescription[],
							  UCHAR 			sSwitchConnector[],
							  UCHAR 			sSwitchDeviceName[],
							  BYTE				byteSwitchBoardID,
							  UINT				uiSwitchChannelNr);

	#ifdef __cplusplus
	    }
	#endif

#endif  /* ndef SWITCH_LINK_NODE_H */
