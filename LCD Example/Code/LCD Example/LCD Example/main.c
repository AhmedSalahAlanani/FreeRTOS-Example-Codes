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



/* Define Tasks Priorities */
#define  TASK1_PRIORITY (2)
#define  TASK2_PRIORITY (2)


/* Define User Messages */
#define string1		(u8*)"Hi,I am Task (1)"
#define string2		(u8*)"Hi,I am Task (2)"

/* Semaphores */
xSemaphoreHandle LCD_SEM ;

/*tasks codes prototypes */
void task1_code(void*pvParamter);
void task2_code(void*pvParamter);


int main(void)
{
    /* Initializations */
	LCD_Vid_4BitInit();
	
	// Create  Semaphore
	vSemaphoreCreateBinary(LCD_SEM);
	
	/*Create tasks*/
	xTaskCreate(task1_code,NULL,85,NULL,TASK1_PRIORITY,NULL);
	xTaskCreate(task2_code,NULL,configMINIMAL_STACK_SIZE,NULL,TASK2_PRIORITY,NULL);
	
	/*start Scheduler */
	vTaskStartScheduler();
	
	return 0;
}


void task1_code(void*pvParamter)
{
	
	while (1)
	{
			 //xSemaphoreTake(LCD_SEM,20);		//2000 stands for delay in the waiting state for the Semaphore, you can replace it with (portMAX_DELAY)
			
			LCD_VidClrLCD();
			LCD_Vid4BitSendString(string1);
			vTaskDelay(2400); // Waiting for 2000 Tick
		
			//xSemaphoreGive(LCD_SEM);
	}
}

void task2_code(void*pvParamter)
{
	
	while(1)
	{
			//xSemaphoreTake(LCD_SEM,50);		//2000 stands for delay in the waiting state for the Semaphore, you can replace it with (portMAX_DELAY)
		
			LCD_VidClrLCD();
			LCD_Vid4BitSendString(string2);
			vTaskDelay(3000);	// Waiting for 1500 Tick
		
			//xSemaphoreGive(LCD_SEM);		
		
	}
}

