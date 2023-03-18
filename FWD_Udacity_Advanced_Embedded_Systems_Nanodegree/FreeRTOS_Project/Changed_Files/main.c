
#include "app.h"


/*-----------------------------------------------------------*/


// Macros for Each Task Period(DeadLine)
#define BUTTON_ONE_PERIOD              			 ( ( BaseType_t ) 50 )
#define BUTTON_TWO_PERIOD              			 ( ( BaseType_t ) 50 )
#define UART_RECIEVER_PERIOD            		 ( ( BaseType_t ) 20 )
#define PERIODC_TRANSMIT_PERIOD              ( ( BaseType_t ) 100 )
#define LOAD_ONE_PERIOD             				 ( ( BaseType_t ) 10 )
#define LOAD_TWO_PERIOD              				 ( ( BaseType_t ) 100 )



/* Constants to setup I/O and processor. */
#define mainBUS_CLK_FULL	( ( unsigned char ) 0x01 )

/* Constants for the ComTest demo application tasks. */
#define mainCOM_TEST_BAUD_RATE	( ( unsigned long ) 115200 )



char _UART_Receiver_ [50];
char Button_One_Falling_Edge_String [] = "\n Button1 Falling Edge Catched \n";
char Button_One_Rising_Edge_String [] = "\n Button1 Rising Edge Catched \n";
char Button_Two_Falling_Edge_String [] = "\n Button2 Falling Edge Catched \n";
char Button_Two_Rising_Edge_String [] = "\n Button2 Rising Edge Catched \n";
char Periodic_Transmitter_String [] = "\n Periodic_Message \n";

/*
 * Configure the processor for use with the Keil demo board.  This is very
 * minimal as most of the setup is managed by the settings in the project
 * file.
 */
static void prvSetupHardware( void );
/*-----------------------------------------------------------*/





/* Tasks Implementation */

/*
 Task One --> Button_1_Monitor
 
 The Functionality of this task is to catch any change on the Port0-Pin0 that refers to button one
 
 and send data if any changes happend to the consumer task
 
 */
void Button_1_Monitor( void * pvParameters )
{

	TickType_t Current_Tick = xTaskGetTickCount();
	pinState_t Button_one_previous_state =  GPIO_read(PORT_0,PIN0);
	pinState_t Button_one_current_state;

	
    for( ;; )
    {
			Button_one_current_state = GPIO_read(PORT_0,PIN0);
			
			if (Button_one_current_state == PIN_IS_LOW && Button_one_previous_state == PIN_IS_HIGH )
			{
				if (xQueue)
				{
					xQueueSend( xQueue, (char *)&Button_One_Falling_Edge_String, (TickType_t) 0);
				}
			}
			else if (Button_one_current_state == PIN_IS_HIGH && Button_one_previous_state == PIN_IS_LOW)
			{
				if (xQueue)
				{
					xQueueSend( xQueue, (char *)&Button_One_Rising_Edge_String, (TickType_t) 0);
				}
			}
			Button_one_previous_state = Button_one_current_state;
					
		// This part for simulation to visulaize when this task come in the logic analyzer
			GPIO_write(PORT_0,PIN2,PIN_IS_LOW);
			vTaskDelayUntil( &Current_Tick ,50);
			GPIO_write(PORT_0,PIN2,PIN_IS_HIGH);
    }
		
}






 /*
 Task Two --> Button_2_Monitor
 
 The Functionality of this task is to catch any change on the Port0-Pin1 that refers to button two
 
 and send data if any changes happend to the consumer task
 
 */
void Button_2_Monitor( void * pvParameters )
{
	TickType_t Current_Tick = xTaskGetTickCount();
	pinState_t Button_two_previous_state = GPIO_read(PORT_0,PIN1);
	pinState_t Button_two_current_state;

    for( ;; )
    {
			Button_two_current_state = GPIO_read(PORT_0,PIN1);
			
			if (Button_two_current_state == PIN_IS_LOW && Button_two_previous_state == PIN_IS_HIGH )
			{
				if (xQueue)
				{
					xQueueSend( xQueue, (char *)&Button_Two_Falling_Edge_String, (TickType_t) 0);
				}
			}
			else if (Button_two_current_state == PIN_IS_HIGH && Button_two_previous_state == PIN_IS_LOW)
			{
				if (xQueue)
				{
					xQueueSend( xQueue, (char *)&Button_Two_Rising_Edge_String, (TickType_t) 0);
				}
			}
			Button_two_previous_state = Button_two_current_state;
			
			// This part for simulation to visulaize when this task come in the logic analyzer
			GPIO_write(PORT_0,PIN3,PIN_IS_LOW);
			vTaskDelayUntil( &Current_Tick ,50);
			GPIO_write(PORT_0,PIN3,PIN_IS_HIGH);
    }
}








 /*
 Task Three --> Periodic Transmit
 
 This Function Will send Peiodic string which is New_Period Every 100ms to the conumer task (UART Transc) 
 
 */

void Periodic_Transmitter( void * pvParameters )
{
	
	TickType_t Current_Tick = xTaskGetTickCount();


    for( ;; )
    {
			if(xQueue)
			{
				xQueueSend ( xQueue, (void *)&Periodic_Transmitter_String, (TickType_t) 0);
			}
			
			
			// This part for simulation to visulaize when this task come in the logic analyzer
			GPIO_write(PORT_0,PIN4,PIN_IS_LOW);
			vTaskDelayUntil( &Current_Tick ,100);
			GPIO_write(PORT_0,PIN4,PIN_IS_HIGH);
    }
}



/*
Task Four --> The Conusmer Task (UART Transciever)

Thsi Functionnality of this task is to recieve the data from other task and diplay it on the screen 
by using UART communication protocol 

*/
void UART_Receiver( void * pvParameters )
{

	TickType_t Current_Tick = xTaskGetTickCount();

    for( ;; )
    {
			if ( xQueueReceive ( xQueue, &_UART_Receiver_, (TickType_t) 0) == pdTRUE)
			{
				vSerialPutString( (signed char *)_UART_Receiver_, strlen(_UART_Receiver_));
			}
			
			// This part for simulation to visulaize when this task come in the logic analyzer
			GPIO_write(PORT_0,PIN5,PIN_IS_LOW);
			vTaskDelayUntil( &Current_Tick ,20);
			GPIO_write(PORT_0,PIN5,PIN_IS_HIGH);
    }
}




// /*
// Task Five --> Load_1_Simulation
// 
// The Functionality of this task is to make load on the cpu to see if this will cause CPU load or not
// 
// */
void Load_1_Simulation( void * pvParameters )
{

	int i;
	
	TickType_t Current_Tick = xTaskGetTickCount();

    for( ;; )
    {
			for ( i=0 ; i<37315 ; i++ );
			
			// This part for simulation to visulaize when this task come in the logic analyzer
			GPIO_write(PORT_0,PIN6,PIN_IS_LOW);
			vTaskDelayUntil( &Current_Tick ,10);
			GPIO_write(PORT_0,PIN6,PIN_IS_HIGH);
    }
}


// /*
// Task Six --> Load_2_Simulation
// 
// The Functionality of this task is to make load on the cpu to see if this will cause CPU load or not
// 
// */
void Load_2_Simulation( void * pvParameters )
{
	int i;
	TickType_t Current_Tick = xTaskGetTickCount();
    for( ;; )
    {
			for ( i=0 ; i<68330 ; i++ );
			
			// This part for simulation to visulaize when this task come in the logic analyzer
			GPIO_write(PORT_0,PIN7,PIN_IS_LOW);
			vTaskDelayUntil( &Current_Tick ,100);
			GPIO_write(PORT_0,PIN7,PIN_IS_HIGH);
			
			
    }
}

/*
 * Application entry point:
 * Starts all the other tasks, then starts the scheduler. 
 */
int main( void )
{
	/* Setup the hardware for use with the Keil demo board. */
	prvSetupHardware();
	
	xQueue = xQueueCreate ( 1, sizeof(_UART_Receiver_)) ;
	
	xTaskPeriodicCreate(
                    Button_1_Monitor,       /* Function that implements the task. */
                    "Button_1_Monitor",          /* Text name for the task. */
                    configMINIMAL_STACK_SIZE,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &Button_1_Monitor_Handler,
										BUTTON_ONE_PERIOD);      /* Used to pass out the created task's handle. */
										
	xTaskPeriodicCreate(
                    Button_2_Monitor,       /* Function that implements the task. */
                    "Button_2_Monitor",          /* Text name for the task. */
                    configMINIMAL_STACK_SIZE,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &Button_2_Monitor_Handler,
										BUTTON_TWO_PERIOD);      /* Used to pass out the created task's handle. */

	xTaskPeriodicCreate(
                    Periodic_Transmitter,       /* Function that implements the task. */
                    "Periodic Transmitter",          /* Text name for the task. */
                    configMINIMAL_STACK_SIZE,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &Periodic_Transmitter_Handler,
										PERIODC_TRANSMIT_PERIOD);      /* Used to pass out the created task's handle. */

	xTaskPeriodicCreate(
                    UART_Receiver,       /* Function that implements the task. */
                    "UART Receiver",          /* Text name for the task. */
                    configMINIMAL_STACK_SIZE,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
										1,/* Priority at which the task is created. */
                    &UART_Receiver_Handler,
										UART_RECIEVER_PERIOD);      /* Used to pass out the created task's handle. */
										
	xTaskPeriodicCreate(
                    Load_1_Simulation,       /* Function that implements the task. */
                    "Load_1_Simulation",          /* Text name for the task. */
                    configMINIMAL_STACK_SIZE,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &Load_1_Simulation_Handler,
										LOAD_ONE_PERIOD);      /* Used to pass out the created task's handle. */
										
	xTaskPeriodicCreate(
                    Load_2_Simulation,       /* Function that implements the task. */
                    "Load_2_Simulation",          /* Text name for the task. */
                    configMINIMAL_STACK_SIZE,      /* Stack size in words, not bytes. */
                    ( void * ) 0,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &Load_2_Simulation_Handler,
										LOAD_TWO_PERIOD);      /* Used to pass out the created task's handle. */
										
							

	/* Now all the tasks have been started - start the scheduler.

	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is 
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used here. */
	vTaskStartScheduler();

	/* Should never reach here!  If you do then there was not enough heap
	available for the idle task to be created. */
	for( ;; );
}
/*-----------------------------------------------------------*/


void vApplicationTickHook (void)
{
	GPIO_write(PORT_0,PIN9, PIN_IS_HIGH);
	GPIO_write(PORT_0,PIN9, PIN_IS_LOW);
}


/* Function to reset timer 1 */
void timer1Reset(void)
{
	T1TCR |= 0x2;
	T1TCR &= ~0x2;
}

/* Function to initialize and start timer 1 */
static void configTimer1(void)
{
	T1PR = 1000;
	T1TCR |= 0x1;
}

static void prvSetupHardware( void )
{
	/* Perform the hardware setup required.  This is minimal as most of the
	setup is managed by the settings in the project file. */

	/* Configure UART */
	xSerialPortInitMinimal(mainCOM_TEST_BAUD_RATE);

	/* Configure GPIO */
	GPIO_init();
	
	/* Config trace timer 1 and read T1TC to get current tick */
	configTimer1();

	/* Setup the peripheral bus to be the same as the PLL output. */
	VPBDIV = mainBUS_CLK_FULL;
}
/*-----------------------------------------------------------*/