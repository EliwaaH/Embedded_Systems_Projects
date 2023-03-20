#include "I2C.h"
#include "Bit_Math.h"
#include "Platform_Types.h"
#include "REGISTERS.h"
#include "I2C_HW.h"

#define     ACK_STATUS                          (TWSR & STATUS_BITS)

#define     STATUS_BITS                                (0xF8)

#define     START_CONDITION_ACK                        (0x08)
#define     REPEATED_START_ACK                         (0x10)
#define     ADDRESS_WRITE_ACK                          (0x18)
#define     ADDRESS_READ_ACK                           (0x40)
#define     DATA_WRITE_ACK                             (0x28)
#define     DATA_READ_ACK                              (0x50)
#define     DATA_READ_NACK                             (0x58)


#define     SLAVE_ADDRESS_WRITE_ACK                    (0x60)
#define     SLAVE_ADDRESS_WRITE_ACK_ARBITRATION        (0x68)
#define     GENERAL_CALL_ACK                           (0x70)
#define     PREV_ADDRESS_WRITE_ACK                     (0x80)
#define     STOP_OR_REPEATED_START_ACK                 (0xA0)

#define     SLAVE_ADDRESS_READ_ACK                     (0xA8)
#define     SLAVE_ADDRESS_READ_ACK_ARBITRATION         (0xB0)
#define     SLAVE_DATA_TRANSMIT_ACK                    (0xB8)
#define     SLAVE_LAST_DATA_TRASNMIT_ACK               (0xC8)
#define     SLAVE_DATA_TRANSMIT_NACK                   (0xC0)





static uint32 Power(uint8 num, uint8 pow)
{
    uint32 pow_num = num;

    for(uint8 i =0; i<pow; i++)
    {
        pow_num *= num; 
    }

    return pow_num;
}

void I2C_Init(const I2C_ConfigType ConfigCont, Address_ MC_Address)
{   
    uint8 PrescalerMode = ConfigCont.PrescalerMode;
    uint8 PrescalerVal  = ConfigCont.PrescalerValue;
    uint8 AckMode       = ConfigCont.AckControlMode;
    uint8 I2CMode       = ConfigCont.I2Cmode;
    



    if(I2CMode == MASTER_MODE)
    {
        // Set The Address of this MC and Enabling General Call
        TWAR = (MC_Address << 1) | (1 << TWGCE);

        // First we need to know the prescaler value to update the TWSR register
        if(PrescalerMode == Prescaler_ON)
        {
            switch(PrescalerVal)
            {
                case Prescaler_4:
                    TWSR =  (1 << TWPS0) | (0 << TWPS1);
                    break;
                
                case Prescaler_16:
                    TWSR = (0 << TWPS0) | (1 << TWPS1);
                    break;
                
                case Prescaler_64:
                    TWSR = (1 << TWPS0) | (1 << TWPS1);
            }
        }

        else if(PrescalerMode == Prescaler_OFF)
        {
            TWSR = (0 << TWPS0) | (0 << TWPS1);
        }

        //Set the TWBR Register Corresponding to The Chosen SCL Clock
        TWBR = ((CPU_FREQ / SCL_CLOCK) - 16) / (2 * Power(4, (TWSR & ((1 << TWPS0) | (1 << TWPS1)))));

    }

    else if(I2CMode == SLAVE_MODE)
    {

        // Set The Address of this MC and Enabling General Call
        TWAR = (MC_Address << 1) | (1 << TWGCE);
    }
    
    /* Enable The I2C Cicuit (Power ON)*/
    TWCR = (1 << TWEN) | (1 << TWEN);

    /*

    if(AckMode == ACKControl_ON)
    {
        TWCR = (1 << TWEA);
    }

    else
    {
        // Do Nothing
    }

    */
    

}



uint8 I2C_Start(void)
{  
  
    // Enbale I2C Peipheral -- Send Start Condition -- Enable ACK
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT) | (1 << TWEA);

    //Pooling on TWINT  To Make Sure that Operation is done   
    while (!(TWCR & (LOGICAL_ONE << TWINT)))
    {
        /* Wait Until TWINT Become one */
    }


    // If Condition to Check on Status Register to See if Start Ack Received or not
    if (ACK_STATUS != START_CONDITION_ACK)
    {
        return FALSE;
    }

}



void I2C_Write(uint8 Data)
{
	TWDR = Data;
	
	TWCR = (1 << TWEN) | (1 << TWINT);
	
	while( !(TWCR & (1 << TWINT)) );
}


uint8 I2C_Read(uint8 ACK)
{
	TWCR = (1 << TWEN) | (1 << TWINT) | (ACK << TWEA);
	
	while( !(TWCR & (1 << TWINT)) );
	
	return TWDR;
}





void I2C_Repeated_Start(Address_ DevAdd, READ_or_Write R_W, uint8 ACK)
{
    /* CALL the Start Function */
	I2C_Start();
	
	
	
	if(R_W == READ)
	{
		TWDR = DevAdd;

		// ENable I2C - Clear I2C Flag
		TWCR = (1 << TWEN) | (1 << TWINT) | (ACK << TWEA);

		//Pooling on TWINT  To Make Sure that Operation is done   
		while (!(TWCR & (LOGICAL_ONE << TWINT)))
		{
			/* Wait Until TWINT Become one */
		}

		if(ACK_STATUS != ADDRESS_READ_ACK)
		{
			return 0;
		}
	}

	else
	{
		TWDR = DevAdd;

		// ENable I2C - Clear I2C Flag
		TWCR = (1 << TWEN) | (1 << TWINT) | (ACK << TWEA);

		//Pooling on TWINT  To Make Sure that Operation is done   
		while (!(TWCR & (LOGICAL_ONE << TWINT)))
		{
			/* Wait Until TWINT Become one */
		}

		if(ACK_STATUS != ADDRESS_WRITE_ACK)
		{
			return 0;
		}
	}

}





void I2C_Stop(void)
{
    // Enbale I2C Peipheral -- Send Start Condition -- Enable ACK
    TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
	
	while((TWCR & (1 << TWSTO)))
	{
		/* wait until the stop condition excute */
	}

}




uint8 I2C_Write_Address_and_Data(Address_ DevAdd, uint8 Data)
{
	
	/* Send the address to the I2C_Write Function */
	I2C_Write(DevAdd);
    
    // If ACK Doesn't match so send 0 as Error State and Exit Function
    // Check for SLA+W transmitted &ack received */
    if(ACK_STATUS != ADDRESS_WRITE_ACK)
    {
	    return FALSE;  // Return 0 to indicate ack received
    }	
    
	/* Send the Data  */
	I2C_Write(Data);

    // If ACK Doesn't match so send 0 as Error State and Exit Function
    // Check for Data transmitted &ack received */	
	if (ACK_STATUS != DATA_WRITE_ACK)
	{
		return FALSE;
	}
}




uint8 I2C_Write_Data(uint8 Data)
{

	/* Load the data in the TWDR register*/
	I2C_Write(Data);
	
    // If ACK Doesn't match so send 0 as Error State and Exit Function
    // Check for Data transmitted &ACK received */
    if (ACK_STATUS != DATA_WRITE_ACK)
    {
	    return FALSE;
    }

}





uint8 I2C_Read_Address_and_Data(Address_ DevAdd, uint8 ACK)
{
	
	/* Load The SLA + R in the register TWDR*/
	
	I2C_Write(DevAdd);
	
	
    // If ACK Doesn't match so send 0 as Error State and Exit Function
    // Check for SLA+R transmitted & ACK received */
    if(ACK_STATUS != ADDRESS_READ_ACK)
    {
	    return FALSE;  // Return 0 to indicate ACK received
    }
	
	
	/* Call the I2C_Read function to read the coming data*/
	I2C_Read(ACK);
			 
	if ((ACK_STATUS == DATA_READ_NACK) || (ACK_STATUS == DATA_READ_NACK))
	{
		// Check for the acknowledgment		
		return TWDR;
	}
}




uint8 I2C_Read_Data(uint8 ACK)
{
   
   /* Call The I2C_Read */
   I2C_Read(ACK);
   
   if (ACK_STATUS == DATA_READ_NACK || ACK_STATUS == DATA_READ_NACK)
   {
	   // Check for the acknowledgment
	   
	   return TWDR;
   }
}






/*********************************************************** SLAVE APIs *************************************************************************/


uint8 I2C_Slave_Read(void)
{
    //Enable I2C and Clear Interrupt Flag And Enable ACK
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);

    while (!(TWCR & (1 << TWINT)))
    {
        /* Wait Until TWINT Become one */
    }

    // If ACK Doesn't match so send FLASE as Error State and Exit Function
    if((ACK_STATUS == SLAVE_ADDRESS_WRITE_ACK) || (ACK_STATUS == SLAVE_ADDRESS_WRITE_ACK_ARBITRATION) || (ACK_STATUS == PREV_ADDRESS_WRITE_ACK))
    {
        return TWDR;  
    }

    else
    {
        return FALSE;
    }
        


}



uint8 I2C_Slave_Write(uint8 Data)
{
    //Enable I2C and Clear Interrupt Flag And Enable ACK
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);

    while (!(TWCR & (1 << TWINT)))
    {
        /* Wait Until TWINT Become one */
    }

    if(ACK_STATUS != SLAVE_ADDRESS_READ_ACK)
    {
        return FALSE;
    }

    TWDR = Data;

    //Enable I2C and Clear Interrupt Flag And Enable ACK
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);

    while (!(TWCR & (1 << TWINT)))
    {
        /* Wait Until TWINT Become one */
    }

    if(ACK_STATUS != SLAVE_DATA_TRANSMIT_NACK)
    {
        return FALSE;
    }

}


















