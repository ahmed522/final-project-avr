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
 *   [DESCRIPTION]: Header file define common project macros for MCU 2      	   *
 * 																				   *
 ***********************************************************************************/

#ifndef PROJECT_MACROS_H_
#define PROJECT_MACROS_H_
/*---------------------------------------------------------------------------------*
 *                                     INCLUDES                                    *
 *---------------------------------------------------------------------------------*/
#include "external_eeprom.h"
#include "UART.h"
/*---------------------------------------------------------------------------------*
 *                               GLOBAL CONST MACROS                               *
 *---------------------------------------------------------------------------------*/
#define PASSWORD_LENGTH 			5
#define FETCH_PASSWORD_COMMAND		(uint8)0x01
#define LOCK_DOOR_COMMAND 			(uint8)0x02
#define UNLOCK_DOOR_COMMAND 	    (uint8)0x03
#define CHANGE_PASSWORD_COMMAND 	(uint8)0x04
#define LOG_OUT_COMMAND 			(uint8)0x05
#define WARNING_COMMAND 			(uint8)0x06
#define PASSWORD_START_ADDRESS 		(uint16)0x0300
#define FIRST_TIME_FLAG_ADDRESS 	(uint16)0x0330
#define RESET_PASSWORD          	(uint8*)"00000"
#define GREEN_LED            	    PA0
#define RED_LED            	        PA1
#define BUZZER            	        PA2
#define UNLOCK_DOOR_ANGLE			0
#define LOCK_DOOR_ANGLE				5
/*---------------------------------------------------------------------------------*
 *                                       ENUMS                                     *
 *---------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------*
 *                                STRUCTS AND UNIONS                               *
 *---------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------*
 *                               FUNCTION PROTOTYPES                               *
 *---------------------------------------------------------------------------------*/
uint8 isFirstTime();
void setPassword(uint8* password);
void fetchPassword();
void PWM_TIMER_INIT(float duty_Cycle) ;
void lockDoor();
void openDoor();
#endif /* PROJECT_MACROS_H_ */
