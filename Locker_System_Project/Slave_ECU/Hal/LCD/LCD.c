
#include "util/delay.h"

#include "LCD.h"

/***************************************************************************************/
/********************************** Macros *********************************************/
/***************************************************************************************/

#define lcd_Clear           	0x01          /* replace all characters with ASCII 'space' */
#define lcd_Home            	0x02          /* return cursor to first position on first line */
#define lcd_EntryMode       	0x06          /* shift cursor from left to right on read/write */
#define lcd_DisplayOff      	0x08          /* turn display off */
#define lcd_DisplayOn       	0x0C          /* display on, cursor off, don't blink character */
#define lcd_FunctionReset   	0x30          /* reset the LCD */
#define lcd_FunctionSet8bit 	0x38          /* 8-bit data, 2-line display, 5 x 7 font */
#define lcd_FunctionSet4bit 	0x28          /* 4-bit data, 2-line display, 5 x 7 font */
#define lcd_SetCursor       	0x80          /* set cursor position */

/***************************************************************************************/
/********************************** Constant Variables *********************************/
/***************************************************************************************/

/***************************************************************************************/
/* Description! Apply initialization sequence for LCD module                           */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void LCD_Init(const LCD_config_T LCD_config) {
	/* Delay 30ms to ensure the initialization of the LCD driver */
	_delay_ms(30);

	Dio_SetPortDirection(LCD_config.portID, 0xFF);

	Dio_SetChannelDirection(LCD_config.portContorl,
			LCD_config.RS_PIN, OUTPUT);

	Dio_SetChannelDirection(LCD_config.portContorl,
			LCD_config.E_PIN, OUTPUT);

	
	/* Return Home  */
	LCD_SendCommand(LCD_config, lcd_Home);
	_delay_ms(15);

	/* Function Set  */
	LCD_SendCommand(LCD_config, lcd_FunctionSet8bit);
	_delay_ms(1);

	/* Display ON OFF Control */
	LCD_SendCommand(LCD_config, lcd_DisplayOn);
	_delay_ms(1);

	/* Clear Display */
	LCD_SendCommand(LCD_config, lcd_Clear);
	_delay_ms(15);

	/* Entry Mode Set  */
	LCD_SendCommand(LCD_config, lcd_EntryMode);
	_delay_ms(2);

}

/***************************************************************************************/
/* Description! Interface to send the configuration commands to the LCD Driver         */
/* Input      ! Command number                                                         */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void LCD_SendCommand(const LCD_config_T LCD_config, uint8 uint8CmdCpy) {

	/* Set RS to LOW */
	Dio_ClearChannel(LCD_config.portContorl,
			LCD_config.RS_PIN);

	_delay_us(1);

	/* Set E to HIGH */
	Dio_WriteChannel(LCD_config.portContorl,
			LCD_config.E_PIN);
	_delay_us(1);

	/* Load Command on Data bus */
	Dio_WritePort(LCD_config.portID, uint8CmdCpy);

	_delay_us(1);

	/* Set E to LOW */
	Dio_ClearChannel(LCD_config.portContorl,
			LCD_config.E_PIN);

	/* Wait for E to settle */
	_delay_ms(5);

	/* Set E to HIGH */
	Dio_WriteChannel(LCD_config.portContorl,
			LCD_config.E_PIN);

	/* Delay for 10ms to let the LCD execute command */
	_delay_ms(10);

}

/***************************************************************************************/
/* Description! Interface to write character on LCD screen                             */
/* Input      ! Data to send                                                           */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void LCD_WriteCharctar(const LCD_config_T LCD_config, uint8 uint8DataCpy)
{

	/* Set RS to HIGH */
	Dio_WriteChannel(LCD_config.portContorl,
			LCD_config.RS_PIN);
	_delay_us(1);

	/* Set E to HIGH */
	Dio_WriteChannel(LCD_config.portContorl,
			LCD_config.E_PIN);
	_delay_us(1);

	/* Load Command on Data bus */
	Dio_WritePort(LCD_config.portID, uint8DataCpy);

	_delay_us(1);

	/* Set E to LOW */
	Dio_ClearChannel(LCD_config.portContorl,
			LCD_config.E_PIN);

	/* Wait for E to settle */
	_delay_ms(5);

	/* Set E to HIGH */
	Dio_WriteChannel(LCD_config.portContorl,
			LCD_config.E_PIN);

	/* Delay for 10ms to let the LCD execute command */
	_delay_ms(10);

}

/***************************************************************************************/
/* Description! Interface to write string on LCD screen                                */
/* Input      ! Pointer to the string                                                  */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void LCD_WriteString(const LCD_config_T LCD_config, uint8* puint8StringCpy) {

	//	/* Local loop index */
	uint8 uint8Index = 0;
	while (puint8StringCpy[uint8Index] != '\0') {
		/* Write Character on LCD */
		LCD_WriteCharctar(LCD_config, puint8StringCpy[uint8Index]);

		//		/* Increment local loop index */
		uint8Index++;

		/* Delay to let the LCD show the character */
		_delay_ms(2);
	}

}



/***************************************************************************************/
/* Description! Interface to Write Number on LCD     */
/* Input      ! Number of a 32 Data Type                                */
/* Output     ! Nothing                                                                */
/***************************************************************************************/

void LCD_WriteNumber(const LCD_config_T LCD_config, uint32 Number)
{
	uint8 number_array[10]={0};
	sint8 counter = 0;

	if(0 == Number)
	{
		LCD_WriteCharctar(LCD_Config, Number + 48);
	}

	else if(0 != Number)
	{
		while( 0 != Number)
		{
			number_array[counter] = Number % 10;

			Number *= 0.1;

			counter++;

		}

		while(counter != 0)
		{
			counter--;
			LCD_WriteCharctar(LCD_Config, (number_array[counter] + 48));

			
		}
	}

}

/***************************************************************************************/
/* Description! Interface to start the writing process at certain digit in the LCD     */
/* Input      ! Y = Row position , X = Column position                                 */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void Gotoxy(const LCD_config_T LCD_config, uint8 ROWS, uint8 COL) {
	if (COL >= 0 && COL <= 39) {
		switch (ROWS) {
		case 0:
			LCD_SendCommand(LCD_config, ((COL + 0x00) | (0x80)));
			break;
		case 1:
			LCD_SendCommand(LCD_config, ((COL + 0x40) | (0x80)));
			break;
		default:
			break;
		}
	}
}




void LCD_Clear(const LCD_config_T LCD_config)
{
	LCD_SendCommand(LCD_config, lcd_Clear);
}

