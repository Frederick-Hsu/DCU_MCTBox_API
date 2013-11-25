/*************************************************************************************************************************************************
 * Project workspace			: MCTBox
 *
 * Current sub-project name		: MCTBox_API
 *
 * Description					: This project will provide the API functions bundle, to drive MCTBox equipment through RS232 serial port.
 *								  It can directly send commands to MCTBox, to execute such actions as 
 *										1. Switch-Relay-Control, 
 *										2. Digital-In/Out, 
 *										3. ADC-Voltage/Current-measuring,
 *								  		4. DAC-Voltage-Outputing, 
 *										5. PWM-signal-outputing,
 *										6. PWM-signal-acquiring,
 *										7. CAN-bus-communicating/analyzing,
 *										8. LIN-bus-communicating/analyzing
 *
 * ===============================================================================================================================================
 *
 * Program file name	: MCTBox_API_DLL_Main.c
 * Description			: This file implements the DllMain() entry function.
 * Creator				: XU ZAN	[HSE-OT]
 * Creation date		: Mon.	Nov. 25, 2013
 * Copyright(C)		2013	Hella Shanghai Electronics Co., Ltd.
 * All rights reserved.
 *
 *************************************************************************************************************************************************/

#include <windows.h>
#include <cvirte.h>

int __stdcall DllMain(HINSTANCE 	hInstDll,
					  DWORD 		dwReason4Call,
					  LPVOID 		lpvReserved)
{
	switch (dwReason4Call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
		if (InitCVIRTE(hInstDll, 0, 0) == 0)
			return 0;	/*  out of memory  */
		break;
	case DLL_PROCESS_DETACH:
	case DLL_THREAD_DETACH:
		CloseCVIRTE();
		break;
	default :
		break;
	}
	
	return TRUE;
}

int __stdcall DllEntryPoint (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	/* Included for compatibility with Borland */

	return DllMain (hinstDLL, fdwReason, lpvReserved);
}
