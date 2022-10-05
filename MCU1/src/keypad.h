
/***********************************************************************************
 * 																				   *
 * 	 [MODULE]: KEYPAD															   *
 * 																				   *
 * 	 [FILE NAME]: keypad.h														   *
 * 																				   *
 * 	 [AUTHOR]: Ahmed Abdelaal													   *
 * 																				   *
 * 	 [CREATED ON]: 04þ/09þ/2022													   *
 * 																				   *
 *   [DESCRIPTION]: Header file for the Keypad driver					    	   *
 * 																				   *
 ***********************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

/*----------------------------------INCLUDES---------------------------------------*/

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

/***********************************************************************************
 * 																				   *
 * 	                			PREPROCESSOR MACROS								   *
 * 																				   *
 ***********************************************************************************/

/* Keypad configurations for number of rows and columns */
#define N_col 4
#define N_row 4

/* Keypad Port Configurations */
#define KEYPAD_COL_PORT_DIR DDRC
#define KEYPAD_COL_PORT_OUT PORTC
#define KEYPAD_ROW_PORT_DIR DDRB
#define KEYPAD_ROW_PORT_OUT PORTB
#define KEYPAD_ROW_PORT_IN  PINB

/* Keypad configurations for pins of rows and columns */
#define COL1 PC4
#define COL2 PC5
#define COL3 PC6
#define COL4 PC7
/*--------------------------*/
#define ROW1 PB4
#define ROW2 PB5
#define ROW3 PB6
#define ROW4 PB7


/***********************************************************************************
 * 																				   *
 * 	                			FUNCTION PROTOTYPES								   *
 * 																				   *
 ***********************************************************************************/

/*[1]-------------------------------------------------------------------------------
 *
 * [FUNCTION NAME]: KeyPad_INIT
 *
 * [FUNCTION DESCRIPTION]: Function responsible for initialize the keypad rows and colmns
 *
 * [Params]: none
 *
 * [return]: none
 *
 *---------------------------------------------------------------------------------*/
void KeyPad_INIT(void);

/*[2]-------------------------------------------------------------------------------
 *
 * [FUNCTION NAME]: KeyPad_getPressedKey
 *
 * [FUNCTION DESCRIPTION]: Function responsible for getting the pressed keypad key
 *
 * [Params]: none
 *
 * [return]: return the index of key pressed
 *
 *---------------------------------------------------------------------------------*/
uint8 KeyPad_getPressedKey(void);


#endif /* KEYPAD_H_ */
