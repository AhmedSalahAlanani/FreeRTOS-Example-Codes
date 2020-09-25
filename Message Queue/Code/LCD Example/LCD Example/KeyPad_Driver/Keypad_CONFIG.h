//****************************************************************************
#ifndef		KEYPAD_CONFIG_H_
#define		KEYPAD_CONFIG_H_


//	Clock	Frequency
#ifndef F_CPU
#define F_CPU 1000000UL						 // 1 MHz clock speed
#endif


//	Select the Used Port
#define		KeypadPORT			portB	


//	Select the Used Pins
#define		C1					0
#define		C2					1
#define		C3					2
#define		C4					3

#define		R1					4
#define		R2					5
#define		R3					6
#define		R4					7


//	Select the Dimensions for the KeyPad
#define		COL					4
#define		ROW					4


//	Define Columns and Rows of KeyPad
static	volatile u8 Columns[COL]  = {C1,C2,C3,C4};
static	volatile u8 Rows[ROW]	  = {R1,R2,R3,R4};


//	Define the Buttons of the KeyPad
static	volatile u8 Keypad_Buttons[ROW][COL] = { 
													{'7','8','9','/'},
													{'4','5','6','x'},
													{'1','2','3','-'},
													{'C','0','=','+'} 
																		 };

//	End of Configuration

#endif
//****************************************************************************
