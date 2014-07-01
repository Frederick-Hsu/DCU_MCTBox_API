/***********************************************************************************************************
 * File name	: MCTBox_API_Version.h
 * Description	: Define the current version of MCTBox_API library.
 * Creator		: XU ZAN	[HSE-OT]
 * Creation date: Mon.	Nov. 25, 2013
 * Copyright(C)		2013	Hella Shanghai Electronics Co., Ltd.
 *
 ***********************************************************************************************************/

#ifndef MCTBOX_API_VERSION_H
#define MCTBOX_API_VERSION_H

	#define YES	1
	#define NO	0

	#define UPGRADE_VERSION		YES
/*****************************************************************/

	#if (UPGRADE_VERSION == YES)
		#define CURRENT_VERSION			"MCTBox_API Version : V1.0.1.1    Build-date : 2014-07-01"
		// #define CURRENT_VERSION		"MCTBox_API Version : V0.9.3.1    Build-date : 2014-06-01"
		// #define CURRENT_VERSION		"MCTBox_API Version : V0.0.0.1    Build-date : 2013-11-25"
	#else
		#define PREVIOUS_VERSION		"MCTBox_API Version : V0.9.3.1    Build-date : 2014-06-01"
		// #define PREVIOUS_VERSION		"MCTBox_API Version : V0.0.0.1    Build-date : 2013-11-25"
		// #define PREVIOUS_VERSION		"MCTBox_API Version : V0.0.0.0"
	#endif	/*  UPGRADE_VERSION  */

#endif  /* ndef MCTBOX_API_VERSION_H */
