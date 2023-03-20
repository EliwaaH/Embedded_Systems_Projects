#ifndef LCD_H
#define LCD_H


#include "Platform_Types.h"
#include "PORT.h"




typedef struct {
	
	Dio_PortType 	 	    portID;
	Dio_PortType     		portContorl;
	Dio_ChannelType 		RS_PIN;
	Dio_ChannelType 		E_PIN;

} LCD_config_T;

extern const LCD_config_T  LCD_Config;


/***************************************************************************************/
/* Description! Apply initialization sequence for LCD module                           */
/* Input      ! Nothing                                                                */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void LCD_Init(const LCD_config_T LCD_config);

/***************************************************************************************/
/* Description! Interface to send the configuration commands to the LCD Driver         */
/* Input      ! Command number                                                         */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void LCD_SendCommand(const LCD_config_T LCD_config, uint8 uint8CmdCpy);

/***************************************************************************************/
/* Description! Interface to write character on LCD screen                             */
/* Input      ! Data to send                                                           */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void LCD_WriteCharctar(const LCD_config_T LCD_config, uint8 uint8DataCpy);

/***************************************************************************************/
/* Description! Interface to write string on LCD screen                                */
/* Input      ! Pointer to the string                                                  */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void LCD_WriteString(const LCD_config_T LCD_config, uint8* puint8StringCpy);


/***************************************************************************************/
/* Description! Interface to write number on LCD screen                                */
/* Input      ! Number														           */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void LCD_WriteNumber(const LCD_config_T LCD_config, uint32 Number);

void Gotoxy(const LCD_config_T LCD_config, uint8 Y, uint8 X);
void LCD_Clear(const LCD_config_T LCD_config);

#endif /* LCD_H */
