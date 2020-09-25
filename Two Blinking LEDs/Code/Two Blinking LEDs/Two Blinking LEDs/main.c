/*
 * Two Blinking LEDs.c
 *
 * Created: 14-Jul-20 6:16:47 PM
 * Author : Ahmed Salah
 */ 

#define	F_CPU	16000000UL

#include "FreeRTOS.h"
#include "task.h"
#include "croutine.h"

//#include "FreeRTOSConfig.h"
#include "DIO Driver/DIO_INIT.h"




/* Define Tasks Priorities */
#define  TASK1_PRIORITY (1)
#define  TASK2_PRIORITY (2)


/*tasks codes prototypes */
void LED1(void*pv);
void LED2(void*pv);


/*Function prototypes*/
void Init_System(void);


int main(void)
{
   /*Initialize the System*/
   Init_System();
   
   /*Create Tasks*/
   xTaskCreate(LED1,NULL,250,NULL,TASK1_PRIORITY,NULL);
   xTaskCreate(LED2,NULL,250,NULL,TASK2_PRIORITY,NULL);
   
   /*start Scheduler */
   vTaskStartScheduler();
   
   return 0;
}


/* Task1 */
void LED1(void*pv)
{
	while(1)
	{
		TOG_BIT(PORTD_REG,0);
		vTaskDelay(500);
	}	
}


/* Task2 */
void LED2(void*pv)
{
	while(1)
	{
		TOG_BIT(PORTD_REG,1);
		vTaskDelay(200);
	}	
}


void Init_System(void)
{
	DIO_VidSetPinDirection(0,portD,OUTPUT);
	DIO_VidSetPinDirection(1,portD,OUTPUT);

}