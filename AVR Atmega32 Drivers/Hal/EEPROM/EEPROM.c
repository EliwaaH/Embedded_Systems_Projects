#include "EEPROM.h"
#include "I2C.h"
#include <util/delay.h>

void EEPROM_Write_Byte(uint8 Word_Address, uint8 Data)
{
    /* First Send a Start Condition to the EEPROM and Wait for The ACK*/
    I2C_Start();

    /* 
    Second Step is 
    1 - Sending the Address of the EEPROM + The Write Operation 
    2 - Sending the Word Address That You Want to Write On

    ****************** Writing Frame of EEPROM ***********************
    -------------------------------------------------------------------
    S | A |  EEPROM_ADDRESS + W | A |  WORD_ADDRESS | A | DATA | A | P
    ------------------------------------------------------------------   
    */

	I2C_Write_Address_and_Data(EEPROM_ADDRESS_WRITE, Word_Address);

	I2C_Write_Data(Data);

    /*
    Third Step is Sending the Stop Condition to Indicate that Operation Finished
    */

	I2C_Stop();

}

uint8 EEPROM_Read_Byte(uint8 Word_Address)
{
    uint8 data = 0;
    /* First Send a Start Condition to the EEPROM and Wait for The ACK*/
    I2C_Start();

    /* 
    Second Step is 
    1 - Sending the Address of the EEPROM + The Write Operation 
    2 - Sending the Word Address That You Want to Write On

    ************************************* Read Frame of EEPROM *****************************************
    --------------------------------------------------------------------------------------------------------
    S | A |  EEPROM_ADDRESS + W | A |  REPEATED_START | A | EEPROM_ADDRESS + R | A | DATA_RETURN | NA | P |
    --------------------------------------------------------------------------------------------------------   
    */

	I2C_Write_Address_and_Data(EEPROM_ADDRESS_WRITE, Word_Address);
	
    I2C_Repeated_Start(EEPROM_ADDRESS_READ, READ, ACK_FALSE);

	data = I2C_Read_Data(ACK_FALSE);

    /* Third Step is Sending the Stop Condition to Indicate that Operation Finished */

	I2C_Stop();

    return data;
}

