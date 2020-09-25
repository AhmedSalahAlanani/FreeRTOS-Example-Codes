/*
 * LCD Example.c
 *
 * Created: 15-Jul-20 3:33:01 PM
 * Author : Ahmed Salah
 */ 

/* Define Clock Frequency*/
#define	F_CPU	1000000UL

#include "FreeRTOS.h"
#include "task.h"
#include "croutine.h"

#include "semphr.h"

#include "DIO Driver/DIO_INIT.h"
#include "LCD Driver/LCD_INIT.h"
#include "External_Interrupt Driver/ext_interrupt.h"


/* Define Tasks Priorities */
#define  TASK1_PRIORITY (2)


/* Define User Messages */
#define string1		(u8*)"Button Pressed:D"

/*create a semaphore handle*/
xSemaphoreHandle task_sync_sem ;

/*tasks codes prototypes */
void task1_code(void*pvParamter);


int main(void)
{
    /* Initializations */
	LCD_Vid_4BitInit();
	DIO_VidSetPinDirection(2,portD,INPUT);
	DIO_VidSetPinValue(2,portD,HIGH);
	Init_Ext_INT0();

	/*Create binary semaphore with initial value 0 because we used it for sync. between INTERRUPT and TASK*/
	task_sync_sem = xSemaphoreCreateCounting(1,0);	
	
	/*Create tasks*/
	xTaskCreate(task1_code,NULL,85,NULL,TASK1_PRIORITY,NULL);
	//xTaskCreate(task2_code,NULL,configMINIMAL_STACK_SIZE,NULL,TASK2_PRIORITY,NULL);
	
	/*start Scheduler */
	vTaskStartScheduler();
	
	return 0;
}


void task1_code(void*pvParamter)
{
	int ret ;

	for (;;)
	{
		 /*pend for semaphore until it released from ISR */

		 ret =xSemaphoreTake(task_sync_sem,portMAX_DELAY);
		 if(ret==1)
		 {
			 /*print if semaphore released*/
			 LCD_Vid4BitSendString(string1);

			 _delay_ms(500);

			 /*clear screen */
			LCD_VidClrLCD();
		 }
		 /*take semaphore to decrement it is val. to wait again until it released by Interrupt */
		 //xSemaphoreTake(task_sync_sem,portMAX_DELAY); 
	}
	 
}



/*interrupt service routine for external interrupt 0 (PD2) */
ISR(INT0_vect)
{

	/*release semaphore */
	xSemaphoreGiveFromISR(task_sync_sem,NULL);
}
