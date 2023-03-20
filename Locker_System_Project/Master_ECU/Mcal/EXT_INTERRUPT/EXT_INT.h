
#ifndef EXT_INT_H
#define EXT_INT_H

#include "PORT.h"
#include "ExtINT_Cfg.h"


#define NULL        ((void *)0x00)


typedef void(*CB_type)(void);



typedef enum
{

	Ext_Int0,
	Ext_Int1,
	Ext_Int2,

}Ext_Int_num;


typedef enum 
{
    LowLevelMode,
    LogicalChangeMode,
    FallingEdgeMode,
    RisingEdgeMode,

}EXT_Int_Mode;



typedef struct 
{
    Ext_Int_num         ExtIntNum;
    EXT_Int_Mode        ExtIntMode;
	Dio_PortType        PortID;
	Dio_ChannelType     ChannelID;

}ExtInt_Config;

extern const ExtInt_Config ExtIntConfigType[REQUIRED_EXTERNAL_INTERRUPTS];



void INT0_CB(CB_type ptr);
void INT0_CB(CB_type ptr);
void INT0_CB(CB_type ptr);
void ExtInt_Init(const ExtInt_Config* ConfigPtr);


#endif // !EXT_INT_H
