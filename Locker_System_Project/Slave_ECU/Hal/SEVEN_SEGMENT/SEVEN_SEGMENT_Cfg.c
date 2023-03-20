#include "SEVEN_SEGMENT.h"





/*

    ------------------------------------------------------------------------------------------------------------
    ***************** This is the way of how to fill the SEVEN SEGMENT Configuration STRUCT ********************

    First --> The MicrController Port that is Connected to SevenSegment

    Second --> The Type of the Seven Segment (CATHOD   --   ANODE)

    Third -->  Put the Default Number that Seven Segment will Display When no number is written on it.
    ***************************************          **********************************************
                                            number_0
                                            number_1,
                                            number_2,
                                            number_3,
                                            number_4,
                                            number_5,
                                            number_6,
                                            number_7,
                                            number_8,
                                            number_9,

    ******************************************************************************************************


	Dio_PortType     PortID;
	seg_Type_T 		 seg_Type;
	seg_number_T 	 seg_number;


*/




const sevenSegment_T    SevenSegment_Config =
{
    PORT_B,
    CATHOD,
    number_0,

};