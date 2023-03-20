#ifndef I2C_H
#define I2C_H



#include "I2C_Cfg.h"
#include "Platform_Types.h"

#define    READ                             (1U)
#define    WRITE                            (0U) 
#define    REPEATED_START_TRUE              (1U)
#define    REPEATED_START_FALSE             (0U)
#define	   ACK_TRUE							(1U)
#define    ACK_FALSE						(0U)


typedef uint8     READ_or_Write;
typedef uint8     Repeated_Start;
typedef uint8     Address_;

typedef enum
{
    ACKControl_OFF,
    ACKControl_ON,

}ACKControl_Mode;




typedef enum
{
    Prescaler_OFF,
    Prescaler_ON,

}Prescaler_Mode;


typedef enum
{
    Prescaler_4,
    Prescaler_16,
    Prescaler_64,

}Prescaler_Value;



typedef enum
{
    MASTER_MODE,
    SLAVE_MODE,

}I2C_MODE;


typedef struct 
{
    I2C_MODE            I2Cmode;
    ACKControl_Mode     AckControlMode;
    Prescaler_Mode      PrescalerMode;
    Prescaler_Value     PrescalerValue;

}I2C_ConfigType;


extern const I2C_ConfigType I2C_Config;


void I2C_Init(const I2C_ConfigType ConfigCont, Address_ MC_Address);
uint8 I2C_Start(void);

void I2C_Write(uint8 Data);
uint8 I2C_Read(uint8 ACK);

void I2C_Repeated_Start(Address_ DevAdd, READ_or_Write R_W, uint8 ACK);
void I2C_Stop(void);

uint8 I2C_Write_Address_and_Data(Address_ DevAdd, uint8 Data);
uint8 I2C_Write_Data(uint8 Data);

uint8 I2C_Read_Address_and_Data(Address_ DevAdd, uint8 ACK);
uint8 I2C_Read_Data(uint8 ACK);

uint8 I2C_Slave_Read(void);
uint8 I2C_Slave_Write(uint8 Data);



#endif // I2C_H