
/***********************************************************************************
 * 																				   *
 * 	 [MODULE]: Automatic door locking system        							   *
 * 																				   *
 * 	 [FILE NAME]: project_macros.h												   *
 * 																				   *
 * 	 [AUTHOR]: Ahmed Abdelaal													   *
 * 																				   *
 * 	 [CREATED ON]: 04þ/10þ/2022													   *
 * 																				   *
 *   [DESCRIPTION]: Header file define common project macros for MCU 1	    	   *
 * 																				   *
 ***********************************************************************************/

#ifndef PROJECT_MACROS_H_
#define PROJECT_MACROS_H_

/*---------------------------------------------------------------------------------*
 *                                     INCLUDES                                    *
 *---------------------------------------------------------------------------------*/
#include "keypad.h"
#include "UART.h"
#include "lcd.h"

/*---------------------------------------------------------------------------------*
 *                               GLOBAL CONST MACROS                               *
 *---------------------------------------------------------------------------------*/
#define PASSWORD_LENGTH 			5
#define NUMBER_OF_TRIES				3
#define FETCH_PASSWORD_COMMAND		(uint8)0x01
#define LOCK_DOOR_COMMAND 			(uint8)0x02
#define UNLOCK_DOOR_COMMAND 	    (uint8)0x03
#define CHANGE_PASSWORD_COMMAND 	(uint8)0x04
#define LOG_OUT_COMMAND 			(uint8)0x05
#define WARNING_COMMAND 			(uint8)0x06
#define RESET_PASSWORD          	(uint8*)"00000"
#define DELAY_PERIOD_1				1000
/*---------------------------------------------------------------------------------*
 *                                       ENUMS                                     *
 *---------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------*
 *                                STRUCTS AND UNIONS                               *
 *---------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------*
 *                               FUNCTION PROTOTYPES                               *
 *---------------------------------------------------------------------------------*/
uint8 IsCorrect (uint8*,uint8*);
void Password_Entry(uint8* entered_Password,char* msg);
void options();
void lockDoor();
void unlockDoor();
void changePassword();
void logOut();
uint8 assertion(char* msg);
void endSession();
void strCpy(uint8* str1 ,uint8* str2);
void sendCommand(uint8 command);
#endif /* PROJECT_MACROS_H_ */
