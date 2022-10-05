/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Ahmed Abdelaal
 */
/*---------------------------------------------------------------------------------*
 *                                     INCLUDES                                    *
 *---------------------------------------------------------------------------------*/
#include "project_macros.h"

uint8* password=RESET_PASSWORD;
uint8 isLocked = TRUE;
uint8 theif = FALSE;
/*---------------------------------------------------------------------------------*
 *                                FUNCTION DEFINITIONS                             *
 *---------------------------------------------------------------------------------*/
int main()
{
/* Initializations ---------------------------------*/

	/* set direction of output leds and buzzer */
	SET_BIT(DDRA,GREEN_LED);
	SET_BIT(DDRA,RED_LED);
	SET_BIT(DDRA,BUZZER);
    /*----------------*/
	/* initialize EEPROM and uart modules */
	EEPROM_init();
	UART_Init();
    /*----------------*/
	/* initialize PWM for servo motor */
	SREG |= (1 << 7);
	PWM_TIMER_INIT(LOCK_DOOR_ANGLE);
    /*----------------*/
	/* set reset password in EEPROM if first time */
    if(isFirstTime())
    {
		setPassword(password);
		EEPROM_writeByte(FIRST_TIME_FLAG_ADDRESS, 0x00);
		_delay_ms(10);
    }
    /*----------------*/
/*-------------------------------------------------*/
	uint8 command;
	while(HIGH)
	{
/* Set leds and buzzer congigurations -------------*/
		if(isLocked && !theif)					/* if door is locked */
		{
			CLEAR_BIT(PORTA,RED_LED);
			SET_BIT(PORTA,GREEN_LED);
		}
		else if(isLocked && theif)				/* if warning (wrong password) */
		{
			SET_BIT(PORTA,GREEN_LED);
			CLEAR_BIT(PORTA,RED_LED);
			SET_BIT(PORTA,BUZZER);
			_delay_ms(500);
			SET_BIT(PORTA,RED_LED);
			CLEAR_BIT(PORTA,BUZZER);
			_delay_ms(500);
		}										/* if door is opened */
		else
		{
			CLEAR_BIT(PORTA,GREEN_LED);
			SET_BIT(PORTA,RED_LED);
		}
/*-------------------------------------------------*/
/*Recieve command from first MCU ------------------*/
		command = Resieve_Byte();
		switch(command)
		{
		case FETCH_PASSWORD_COMMAND:
			fetchPassword();
			Send_String(password);
			_delay_ms(50);
			break;
		case LOCK_DOOR_COMMAND:
			Send_Byte(isLocked);
			_delay_ms(50);
			if(!isLocked)
			{
				lockDoor();
				Send_Byte(TRUE);
				_delay_ms(50);
			}
			break;
		case UNLOCK_DOOR_COMMAND:
			Send_Byte(isLocked);
			_delay_ms(50);
			if(isLocked)
			{
				openDoor();
				/* Acknowledgement */
				Send_Byte(TRUE);
				_delay_ms(50);
				/*-----------------*/
			}
			break;
		case LOG_OUT_COMMAND:
			lockDoor();
			break;
		case CHANGE_PASSWORD_COMMAND:
			Resieve_String(password);
			_delay_ms(50);
			setPassword(password);
			/* Acknowledgement */
			Send_Byte(TRUE);
			_delay_ms(1000);
			/*-----------------*/
			lockDoor();
			break;
		case WARNING_COMMAND:
			lockDoor();
			theif = TRUE;
			break;
		}

/*-------------------------------------------------*/

	}
}
uint8 isFirstTime()
{
	uint8 firstTimeFlag;
	EEPROM_readByte(FIRST_TIME_FLAG_ADDRESS, &firstTimeFlag);
	return firstTimeFlag;
}
void setPassword(uint8* password)
{
	for(uint8 i=0;i<PASSWORD_LENGTH;i++)
	{
		EEPROM_writeByte((PASSWORD_START_ADDRESS + i), password[i]);
		_delay_ms(10);
	}

}
void fetchPassword()
{
	for(uint8 i=0;i<PASSWORD_LENGTH;i++)
		{
			EEPROM_readByte((PASSWORD_START_ADDRESS + i), password+i);
			_delay_ms(10);
		}
}
void lockDoor()
{
	PWM_TIMER_INIT(LOCK_DOOR_ANGLE);
	isLocked = TRUE;
}
void openDoor()
{
	PWM_TIMER_INIT(UNLOCK_DOOR_ANGLE);
	isLocked = FALSE;
}
void PWM_TIMER_INIT(float duty_Cycle)
{
	unsigned char compare_Val = (unsigned char) duty_Cycle * 255 / 100;
	TCNT0 = 0;
	OCR0 = compare_Val;
	DDRB |= (1 << PB3);
	TCCR0 |= (1 << WGM01) | (1 << WGM00) | (1 << COM01) | (1 << CS02)
			| (1 << CS00);   //PRESCALER =1024
}
