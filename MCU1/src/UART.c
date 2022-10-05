/***********************************************************************************
 * 																				   *
 * 	 [MODULE]: UART  															   *
 * 																				   *
 * 	 [FILE NAME]: UART.c														   *
 * 																				   *
 * 	 [AUTHOR]: Ahmed Abdelaal													   *
 * 																				   *
 * 	 [CREATED ON]: 30/09þ/2022													   *
 * 																				   *
 *   [DESCRIPTION]: Source file for the UART driver 					    	   *
 * 																				   *
 ***********************************************************************************/

/*---------------------------------------------------------------------------------*
 *                                     INCLUDES                                    *
 *---------------------------------------------------------------------------------*/
#include "UART.h"

/*---------------------------------------------------------------------------------*
 *                                FUNCTION DEFINITIONS                             *
 *---------------------------------------------------------------------------------*/

void UART_Init()
{
	/*-------------------------------------UCSRA-------------------------------------*/
	/* Enable double speed */
	SET_BIT(UCSRA,U2X);

	/*-------------------------------------UCSRB-------------------------------------*/
	/* Enable reciving and transmitting */
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN);

	/*-------------------------------------UCSRC-------------------------------------*/
	/* Enable writing to UCSRC register */
	SET_BIT(UCSRC,URSEL);

	/* Async or Sync */
	/*---------------------------------Operation Mode--------------------------------
	*
    *					UMSEL 	 	   		          Mode
    *  				      0                   Asynchronous Operation
    *					  1                   Synchronous Operation
    *
    *----------------------------------------------------------------------------*/

	/* Set parity mode */
	/*---------------------------------Parity Mode--------------------------------
	 *
	 *					UPM1 	 	UPM0 		Parity Mode
     *  				 0           0            Disabled
	 *					 1           0            Enabled, Even Parity
	 * 					 1           1            Enabled, Odd Parity
	 *
	 *----------------------------------------------------------------------------*/

	/* Set Stop Bit */
	/*---------------------------------Stop Bit--------------------------------
	*
    *					 USBS 	 	   		       Stop Bit(s)
  	*  				      0                          1-bit
    *					  1                          2-bit
    *
	*----------------------------------------------------------------------------*/

	/* Set Character Size */
	/*-------------------------------Character Size--------------------------------
	 *
     *					UCSZ2 		UCSZ1		 UCSZ0 		Character Size
	 *					  0		      0            0             5-bit
	 *					  0           0            1             6-bit
	 *					  0           1            0             7-bit
	 *					  0           1            1             8-bit
	 *					  1           1            1             9-bit
	 *
	 *----------------------------------------------------------------------------*/
	/* 8-bit */
	SET_BIT(UCSRC,UCSZ0);
	SET_BIT(UCSRC,UCSZ1);

	/* Baudrate prescaler */
	UBRRH = (BAUDRATE_PRESCALER>>8);
    UBRRL = BAUDRATE_PRESCALER;
}
void Send_Byte(const uint8 data)
{
	/* wait until transmitter buffer register is empty */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}
	/* Send data */
	UDR=data;

}
uint8 Resieve_Byte()
{
	while(BIT_IS_CLEAR(UCSRA,RXC)){}
    return UDR;
}
void Send_String(const uint8* str)
{
	uint8 i = 0;
	while(str[i] != '\0')
	{
		Send_Byte(str[i]);
		i++;
		_delay_ms(50);
	}
	Send_Byte(END_STRING_SYMBOL);
	_delay_ms(50);
}
void Resieve_String(uint8* str)
{
	uint8 i = 0;
	str[i] = Resieve_Byte();
	while(str[i] != END_STRING_SYMBOL)
	{
		i++;
		str[i] = Resieve_Byte();
		_delay_ms(50);
	}
	str[i] = '\0';
}
