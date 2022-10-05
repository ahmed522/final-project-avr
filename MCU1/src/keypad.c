/***********************************************************************************
 * 																				   *
 * 	 [MODULE]: KEYPAD															   *
 * 																				   *
 * 	 [FILE NAME]: keypad.c														   *
 * 																				   *
 * 	 [AUTHOR]: Ahmed Abdelaal													   *
 * 																				   *
 * 	 [CREATED ON]: 04þ/09þ/2022													   *
 * 																				   *
 *   [DESCRIPTION]: Source file for the Keypad driver					    	   *
 * 																				   *
 ***********************************************************************************/

#include "keypad.h"

/***********************************************************************************
 * 																				   *
 *                      Functions Prototypes(Private)      						   *
 * 																				   *
 ***********************************************************************************/

#if (N_col == 3)
/*----------------------------------------------------------------------------------
 *
 * [FUNCTION NAME]: KeyPad_4x3_adjustKeyNumber
 *
 * [FUNCTION DESCRIPTION]: Function responsible for returning the corresponding value for
 *                         each key pressed for 4x3 keypad.
 * [Params]: [1] uint8 button_number : index of key pressed
 *
 * [return]: return the corresponding value of given key
 *
 *---------------------------------------------------------------------------------*/
static uint8 KeyPad_4x3_adjustKeyNumber(uint8 button_number);

#elif (N_col == 4)
/*----------------------------------------------------------------------------------
 *
 * [FUNCTION NAME]: KeyPad_4x4_adjustKeyNumber
 *
 * [FUNCTION DESCRIPTION]: Function responsible for returning the corresponding value for
 *                         each key pressed for 4x4 keypad.
 * [Params]: [1] uint8 button_number : index of key pressed
 *
 * [return]: return the corresponding value of given key
 *
 *---------------------------------------------------------------------------------*/
static uint8 KeyPad_4x4_adjustKeyNumber(uint8 button_number);
#endif
/***********************************************************************************
 * 																				   *
 *              	          Functions Definitions                                *
 * 																				   *
 ***********************************************************************************/
void KeyPad_INIT(void) {
	/*
	 * set Keypad rows pins direction to input
	 */
	KEYPAD_ROW_PORT_DIR = (KEYPAD_ROW_PORT_DIR
			& ~((1 << ROW1) | (1 << ROW2) | (1 << ROW3) | (1 << ROW4)));
	/*
	 * enable the internal pull up resistors for the rows pins
	 */
	KEYPAD_ROW_PORT_OUT = (KEYPAD_ROW_PORT_OUT
			| ((1 << ROW1) | (1 << ROW2) | (1 << ROW3) | (1 << ROW4)));
}
/*---------------------------------------------------------------------------------*/
uint8 KeyPad_getPressedKey(void) {
	uint8 col, row;
		for (col = 0; col < N_col; col++) /* loop for columns */
		{

			/*
			 * each time only one of the column pins will be output and
			 * the rest will be input pins
			 */
			KEYPAD_COL_PORT_DIR = (KEYPAD_COL_PORT_DIR
					& ~((1 << COL1) | (1 << COL2) | (1 << COL3) | (1 << COL4)))
					| ((1 << COL1) << col);

			/*
			 * clear the output pin column in this trace and enable the internal
			 * pull up resistors for the cloumns pins
			 */
			KEYPAD_COL_PORT_OUT = (KEYPAD_COL_PORT_OUT & ~((1 << COL1) << col));

			for (row = 0; row < N_row; row++) /* loop for rows */
			{
				if (BIT_IS_CLEAR(KEYPAD_ROW_PORT_IN, (ROW1+row))) /* if the switch is press in this row */
				{
#if (N_col == 3)
					return KeyPad_4x3_adjustKeyNumber((row*N_col)+col+1);
#elif (N_col == 4)
					return KeyPad_4x4_adjustKeyNumber((row * N_col) + col + 1);
#endif
				}
			}
		}
	return 0;
}

/*---------------------------------------------------------------------------------*/
#if (N_col == 3)

static uint8 KeyPad_4x3_adjustKeyNumber(uint8 button_number)
{
	switch(button_number)
	{
		case 10: return '*'; // ASCII Code of *
				 break;
		case 11: return 0;
				 break;
		case 12: return '#'; // ASCII Code of #
				 break;
		default: return button_number;
	}
}

#elif (N_col == 4)

static uint8 KeyPad_4x4_adjustKeyNumber(uint8 button_number)
{
	switch(button_number)
	{
		case 1: return 7;
				break;
		case 2: return 8;
				break;
		case 3: return 9;
				break;
		case 4: return '%'; // ASCII Code of %
				break;
		case 5: return 4;
				break;
		case 6: return 5;
				break;
		case 7: return 6;
				break;
		case 8: return '*'; /* ASCII Code of '*' */
				break;
		case 9: return 1;
				break;
		case 10: return 2;
				break;
		case 11: return 3;
				break;
		case 12: return '-'; /* ASCII Code of '-' */
				break;
		case 13: return '#';  /* ASCII of Enter */
				break;
		case 14: return '0';
				break;
		case 15: return '='; /* ASCII Code of '=' */
				break;
		case 16: return '+'; /* ASCII Code of '+' */
				break;
		default: return button_number;
	}
}

#endif

