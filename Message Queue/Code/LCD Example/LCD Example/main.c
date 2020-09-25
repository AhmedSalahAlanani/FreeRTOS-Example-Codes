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
#include "KeyPad_Driver/Keypad_INIT.h"



/* Define Tasks Priorities */
#define  TASK1_PRIORITY (2)
#define  TASK2_PRIORITY (2)


/* Define Button States */
#define  NOT_PRESSED (0)


/* Define User Messages */
#define string1		(u8*)"Wait.."

/* Create Message Queue Handle */
xQueueHandle buffer;

/*tasks codes prototypes */
void KeypadTask(void*pvParamter);
void LCDTask(void*pvParamter);


int main(void)
{
    /* Initializations */
	LCD_Vid_4BitInit();
	Vid_Keypad_INIT();

	/*Create Message Queue*/
	buffer = xQueueCreate(6, sizeof(unsigned char));

	/*Create tasks*/
	xTaskCreate(KeypadTask,NULL,85,NULL,TASK1_PRIORITY,NULL);
	xTaskCreate(LCDTask,NULL,configMINIMAL_STACK_SIZE,NULL,TASK2_PRIORITY,NULL);
	
	/*start Scheduler */
	vTaskStartScheduler();
	
	return 0;
}


/* keypad task function, which is a periodic function with period 50 ms */
void KeypadTask(void*pvParamter)
{
	/* Variable used to hold the value of the pressed key */
	unsigned char val;
	
	for(;;)
	{
			/* get the pressed key value */
			val = Keypad_GetPressed();
			
			/* Check if no key is pressed */
			if(val != NOT_PRESSED)
			{
				/* If a key is pressed, send the value to buffer"Message Queue" */
				xQueueSend(buffer, &val, portMAX_DELAY);
			}
			
			/* delay to make the task periodic each 50 ms */
			vTaskDelay(50);
	}
}

void LCDTask(void*pvParamter)
{
	unsigned char val;
	unsigned char ret;
	static unsigned char counter=0;
	
	while(1)
	{
			ret = xQueueReceive(buffer, &val, portMAX_DELAY);		//It Removes the read Values as soon as possible, unlike " receivewithoutdelete(); "
			
			if(ret==pdTRUE)
			{
				counter++;
				
				if (counter>6)		//Optional Value
				{
					LCD_VidClrLCD();
					LCD_Vid4BitSendString(string1);
				}
				
				else
				{
					LCD_Vid_4BitSendChar(val);
				}
			}
		
	}
}

