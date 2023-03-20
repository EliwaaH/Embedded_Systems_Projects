/*
 * LockerSystem_With_Layers.c
 *
 * Created: 05/03/2023 16:28:46
 * Author : Ahmed_Eliwa
 */ 


#include "LockerSystem_SWCs.h"



/* Here is The Main APP */
int main(void)
{
	/* First we use Init System to Initilize our systme componenets*/
	Init_System();


	/*
		Then, The Super Loop

		We put Every task in a while loop that keeps it running until it's semaphore is released 

	*/
    while (1) 
    {
		/*
			First we Check on the First Open Semaphore to Check if this is the first time to open the system after manfactured process or not
		*/


		while( (FirstTime_Open_Semaphore == 1) && (First_Open_Check() == 1) )
		{
			FirstTime_Open();
		}



		/*
			Second we Check on Default Semaphor, Please Note that Default Task is the Task that will always running until user enter his password

			we will not enter default task before checking that first open process or checking process is done correctly 
		*/

				
		while ((Default_Semaphore == 1) && (FirstTime_Open_Semaphore == 0) && (Change_Password_Semaphore == 0)) 
		{
			Default();
		}


		/*
			Here, we are checking on Change Password Semaphore
			Program will not Enter here unless Change Password Semaphore is Free
			And this only happen when this is the first time you open the system 
			Or you started the Reset Process
		*/
		
		while ( Change_Password_Semaphore == 1 )
		{
			Change_Password();
		}	
		

		/*
			Here we are checking on the Open Locker Semaphore
			This Task is Excuted only when Default task Semaphore is Released and this is done only when you enter correct Password
		*/
		while ( (Default_Semaphore == 0) && (Open_Locker_Semaphore == 1) )
		{
			Open_Locker();	
		}
		
	}
}