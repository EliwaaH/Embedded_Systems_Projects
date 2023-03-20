#include "EXT_INT.h"




/***********************************************************************************************************************************************

***************************************************** External Interrupts Configurations File ***************************************************************

********* Please Note That you Have To Configure Each Interrupt in A specific Element in the Configuration Arra
		  And you Have to Put The Number of Used Interrupts In the MACRO that Called REQUIRED_EXTERNAL_INTERRUPTS and exists in the Cfg.h File

    1- First Argument is the Interrupt Number (For Atmega32 theres only Three External Interrupts Which Are (INT0, INT1, INT2))
    
    2- The Second Argument is the Mode of this Interrupt or how you need This Interrupt Triggered

    3- The Third Argument is the Port That This Interrupts Number Exists in your Micro

    4- The Fourth Argument is the Channel in the port

***********************************************************************************************************************************************/


const ExtInt_Config ExtIntConfigType[REQUIRED_EXTERNAL_INTERRUPTS] = {
	
    {Ext_Int0, FallingEdgeMode, PORT_D, PIN2},
};