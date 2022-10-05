
/***********************************************************************************
 * 																				   *
 * 	 [MODULE]: UART  															   *
 * 																				   *
 * 	 [FILE NAME]: UART.h														   *
 * 																				   *
 * 	 [AUTHOR]: Ahmed Abdelaal													   *
 * 																				   *
 * 	 [CREATED ON]: 30/09þ/2022													   *
 * 																				   *
 *   [DESCRIPTION]: Header file for the UART driver 					    	   *
 * 																				   *
 ***********************************************************************************/

#ifndef UART_H_
#define UART_H_
/*---------------------------------------------------------------------------------*
 *                                     INCLUDES                                    *
 *---------------------------------------------------------------------------------*/
#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"
/*---------------------------------------------------------------------------------*
 *                               GLOBAL CONST MACROS                               *
 *---------------------------------------------------------------------------------*/

#define BAUDRATE 						9600
#define BAUDRATE_PRESCALER              (((F_CPU / (BAUDRATE * 8UL))) - 1)
#define END_STRING_SYMBOL				(uint8)'#'

/*---------------------------------------------------------------------------------*
 *                                       ENUMS                                     *
 *---------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------*
 *                                STRUCTS AND UNIONS                               *
 *---------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------*
 *                               FUNCTION PROTOTYPES                               *
 *---------------------------------------------------------------------------------*/

/*[1]-------------------------------------------------------------------------------
 *
 * [FUNCTION NAME]: UART_Init
 *
 * [FUNCTION DESCRIPTION]: Function responsible for initialize configurations
 *                         for UART module.
 * [SYNCHRONIZATION]: sync
 *
 * [REENTARNCY]: Non-Reentrant
 *
 * [Params]: [in]:   none
 *           [out]:  none
 *
 * [return]: none
 *
 *---------------------------------------------------------------------------------*/
void UART_Init(void);
/*[2]-------------------------------------------------------------------------------
 *
 * [FUNCTION NAME]: Send_Byte
 *
 * [FUNCTION DESCRIPTION]: Function responsible for sending a byte of data
 * 						   using UART module.
 * [SYNCHRONIZATION]: sync
 *
 * [REENTARNCY]: Non-Reentrant
 *
 * [Params]: [in]:   const uint8 data : byte of data to be send
 *           [out]:  none
 *
 * [return]: none
 *
 *---------------------------------------------------------------------------------*/
void Send_Byte(const uint8);
/*[3]-------------------------------------------------------------------------------
 *
 * [FUNCTION NAME]: Resieve_Byte
 *
 * [FUNCTION DESCRIPTION]: Function responsible for recieving a byte of data
 * 						   using UART module.
 * [SYNCHRONIZATION]: sync
 *
 * [REENTARNCY]: Non-Reentrant
 *
 * [Params]: [in]:   none
 *           [out]:  none
 *
 * [return]: uint8 data :data which had been recieved
 *
 *---------------------------------------------------------------------------------*/
uint8 Resieve_Byte(void);
/*[4]-------------------------------------------------------------------------------
 *
 * [FUNCTION NAME]: Send_String
 *
 * [FUNCTION DESCRIPTION]: Function responsible for sending string
 * 						   using UART module.
 * [SYNCHRONIZATION]: sync
 *
 * [REENTARNCY]: Non-Reentrant
 *
 * [Params]: [in]:   const uint8* str :string to be send
 *           [out]:  none
 *
 * [return]: none
 *
 *---------------------------------------------------------------------------------*/
void Send_String(const uint8*);
/*[5]-------------------------------------------------------------------------------
 *
 * [FUNCTION NAME]: Resieve_String
 *
 * [FUNCTION DESCRIPTION]: Function responsible for recieving string
 * 						   using UART module.
 * [SYNCHRONIZATION]: sync
 *
 * [REENTARNCY]: Non-Reentrant
 *
 * [Params]: [in]:   none
 *           [out]:  uint8* str :string which had been recieved
 *
 * [return]: none
 *
 *---------------------------------------------------------------------------------*/
void Resieve_String(uint8*);

#endif /* UART_H_ */
