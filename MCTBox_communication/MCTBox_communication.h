/****************************************************************************************************************
 * File name	: MCTBox_communication.h
 * Description	: The MCTBox_communication module will implement the RS232 communicating & accessing between
 *				  host PC and MCTBox test instrument.
 * Creator		: XU ZAN	[HSE-OT]
 * Creation date: Wed.	Nov. 27, 2013
 * Copyright(C)		2013	Hella Shanghai Electronics Co., Ltd.
 *
 ****************************************************************************************************************/

#ifndef MCTBOX_COMMUNICATION_H
#define MCTBOX_COMMUNICATION_H

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

			//==============================================================================
			// External variables

			//==============================================================================
			// Functions prototype :
			int MCTBox_communication_RS232_Init(int iComPortNr, char *sARGOUT_ComError);
			int MCTBox_communication_RS232_Exit(char *sARGOUT_ComError);
			
			int MCTBox_communication_RS232_Write(char sARGIN_ComCmd2Write[], char *sARGOUT_ComError);
			int MCTBox_communication_RS232_Read(char *sARGOUT_ComResponse, char *sARGOUT_ComError);
			int MCTBox_communication_RS232_Query(char sARGIN_ComCmd2Write[], char *sARGOUT_ComResponse, char *sARGOUT_ComError);

	#ifdef __cplusplus
	    }
	#endif

#endif  /* ndef MCTBOX_COMMUNICATION_H */
