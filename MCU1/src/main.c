/*
 * main.c
 *
 *      Author: Ahmed Abdelaal
 */

/*---------------------------------------------------------------------------------*
 *                                     INCLUDES                                    *
 *---------------------------------------------------------------------------------*/
#include "project_macros.h"


uint8 try = NUMBER_OF_TRIES;
uint8 correctFlag = FALSE;
uint8* password=RESET_PASSWORD;
uint8 entered_Password[PASSWORD_LENGTH];
/*---------------------------------------------------------------------------------*
 *                                FUNCTION DEFINITIONS                             *
 *---------------------------------------------------------------------------------*/
int main()
{
	KeyPad_INIT();
	UART_Init();
	LCD_init();
	sendCommand(FETCH_PASSWORD_COMMAND);
	Resieve_String(password);
	while(HIGH)
	{
		if(try && !correctFlag)
		{
			Password_Entry(entered_Password,"Welcome, please enter password");
			if(IsCorrect(password,entered_Password))
			{
				correctFlag = TRUE;
				LCD_clearScreen();
				LCD_goToRowColumn(0, 0);
				LCD_displayString("Password is correct :) ");
				_delay_ms(DELAY_PERIOD_1);

			}
			else
			{
				--try;
				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 0,"Password is not correct :( ");
				if(try)
				{
				LCD_displayStringRowColumn(1, 0,"you have ");
				LCD_displayInteger(try);
				LCD_displayString(" more tries");
				_delay_ms(DELAY_PERIOD_1);
				}
				else
				{
					_delay_ms(DELAY_PERIOD_1);
					LCD_clearScreen();
					LCD_displayStringRowColumn(0, 0,"Warning !! you typed wrong  ");
					LCD_displayStringRowColumn(1, 0,"password for 3 times !");
				}
			}
		}
		else if(try && correctFlag)
		{
			options();
		}
		else
		{
			sendCommand(WARNING_COMMAND);
			_delay_ms(DELAY_PERIOD_1/2);
			LCD_displayOff();
			_delay_ms(DELAY_PERIOD_1/2);
			LCD_cursorOff();
		}
	}


}

uint8 IsCorrect (uint8* password , uint8* entered_Password)
{
	uint8 flag = TRUE;
	for (int i=0;i<PASSWORD_LENGTH;i++)
	{
		if(password[i] != entered_Password[i])
		{
			flag = FALSE;
			break;
		}
	}
	return flag;
}

void Password_Entry(uint8* entered_Password, char* msg)
{
	int i=0;
	uint8 flag=FALSE;
	uint8 key;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0,msg);
	LCD_goToRowColumn(1, 0);
	while(i < PASSWORD_LENGTH)
	{
		key = KeyPad_getPressedKey();
		if (key && !flag)
		{
			if(key>0 && key<10)
			{
			    itoa(key,&(entered_Password[i]),10);
			}
			else if(key == '#')
			{}
			else
			{
				entered_Password[i]=key;
			}
			if(key != '#')
			{
				LCD_displayCharacter(entered_Password[i]);
				_delay_ms(150);
				LCD_goToRowColumn(1, i);
				LCD_displayCharacter('*');
				i++;
			}
			else
			{
				if(i)
				{
				--i;
				LCD_goToRowColumn(1, i);
				LCD_displayCharacter(' ');
				LCD_goToRowColumn(1, i);
				}
			}
				flag = TRUE;
		}
		else if (key && flag)
		{
		}
		else
		{
		flag = FALSE;
		}

	}
	entered_Password[i]='\0';
	_delay_ms(DELAY_PERIOD_1/5);
}
void options()
{
	uint8 choice=0;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0,"Choose one of following options : ");
	_delay_ms(DELAY_PERIOD_1);
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0,"1- Lock door");
	LCD_displayStringRowColumn(0, 16,"2- Unlock door");
	LCD_displayStringRowColumn(1, 0,"3- Change password");
	LCD_displayStringRowColumn(1, 21,"4- Log out");
	while(!choice)
	{
		choice = KeyPad_getPressedKey();
		switch(choice)
		{
		case 1:
			lockDoor();
			break;
		case 2:
			unlockDoor();
			break;
		case 3:
			changePassword();
			break;
		case 4:
			logOut();
			break;
		default:
			choice = 0;
		}
	}
}
void lockDoor()
{
	sendCommand(LOCK_DOOR_COMMAND);
	if(Resieve_Byte())
	{
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0,"Door is already Locked ");
		_delay_ms(DELAY_PERIOD_1);
		options();
	}
	else
	{
		LCD_clearScreen();
		if(Resieve_Byte())
		{
			LCD_displayStringRowColumn(0, 0,"Door have been Locked ");
			LCD_displayStringRowColumn(1, 0,"successfully !!");
		}
		else
		{
			LCD_displayStringRowColumn(0, 0,"Error !!");
		}
		_delay_ms(DELAY_PERIOD_1);
		options();
	}
}
void unlockDoor()
{
	sendCommand(UNLOCK_DOOR_COMMAND);
	if(Resieve_Byte())
	{
		LCD_clearScreen();
		if(Resieve_Byte())
		{
			LCD_displayStringRowColumn(0, 0,"Door have been opened ");
			LCD_displayStringRowColumn(1, 0,"successfully !!");
		}
		else
		{
		LCD_displayStringRowColumn(0, 0,"Error !!");
		}
		_delay_ms(DELAY_PERIOD_1);
		options();

	}
	else
	{
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0,"Door is already opened ");
		_delay_ms(DELAY_PERIOD_1);
		options();
	}
}

void changePassword()
{
	if(assertion("Sure to change password ?"))
	{
		Password_Entry(entered_Password,"Enter old password");
		if(IsCorrect(password, entered_Password))
		{
			Password_Entry(entered_Password,"Enter new password");
		    strCpy(password ,entered_Password);
		    sendCommand(CHANGE_PASSWORD_COMMAND);
		    Send_String(password);
		    _delay_ms(DELAY_PERIOD_1/20);
			LCD_clearScreen();
		    if(Resieve_Byte())
		    {
		    	LCD_displayStringRowColumn(0, 0,"password saved successfully !!");
		    }
		    else
		    {
				LCD_displayStringRowColumn(0, 0,"Error !!");

		    }
		   _delay_ms(DELAY_PERIOD_1);
			sendCommand(FETCH_PASSWORD_COMMAND);
			Resieve_String(password);
			endSession();
		}
		else
		{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0,"Password is not correct :( ");
		   _delay_ms(DELAY_PERIOD_1);
			options();
		}
	}
	else
	{
	options();
	}

}
void logOut()
{
	if(assertion("Are you sure to log out?"))
	{
		sendCommand(LOG_OUT_COMMAND);
		endSession();
	}
	else
	{
		options();
	}

}
uint8 assertion(char* msg)
{
	uint8 answer=0;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0,msg);
	LCD_displayStringRowColumn(1, 0,"1- No");
	LCD_displayStringRowColumn(1, 16,"2- Yes");
	while(!answer)
		{
			answer = KeyPad_getPressedKey();
			switch(answer)
			{
			case 1:
				return FALSE;
			case 2:
				return TRUE;
			default:
				answer = 0;
			}
		}
}
void endSession()
{
	correctFlag=FALSE;
	try=NUMBER_OF_TRIES;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0,"Session ended !");
    _delay_ms(DELAY_PERIOD_1/4);
	LCD_displayStringRowColumn(1, 0,"you have to login again");
	_delay_ms(DELAY_PERIOD_1);
}
void strCpy(uint8* str1 ,uint8* str2)
{
	for (int i=0;i<PASSWORD_LENGTH;i++)
	{
		str1[i]=str2[i];
	}
}
void sendCommand(uint8 command)
{
	Send_Byte(command);
	_delay_ms(DELAY_PERIOD_1/20);
}
