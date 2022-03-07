/*
* Author: Yadong Hu
* Date: 11/30/2021
* Description:
		Display a character or strings on the LCD screen.
*/


#include "PLL.h"
#include "PORT.h"

// Function Definitions 
void PORTA_Init(void) {
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x01;
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTA_AMSEL_R &= 0x00;
	GPIO_PORTA_PCTL_R &= 0x00000000;
	GPIO_PORTA_DIR_R |= 0x0C;
	GPIO_PORTA_AFSEL_R &= 0x00;
	GPIO_PORTA_PUR_R &= 0x00;
	GPIO_PORTA_DEN_R |= 0x0C;
}

void PORTB_Init(void) {
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x02;
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTB_AMSEL_R &= 0x00;
	GPIO_PORTB_PCTL_R &= 0x00000000;
	GPIO_PORTB_DIR_R |= 0x3C;
	GPIO_PORTB_AFSEL_R &= 0x00;
	GPIO_PORTB_PUR_R &= 0x00;
	GPIO_PORTB_DEN_R |= 0x3C;
}


void lcdENPluse(void) {
	lcdEN = 0x04;
	// Wait for 1 us
	SysTickWait(1);
	lcdEN = 0x00;
	SysTickWait(1);
}

// Since I use PB2-5 as data bits, data bits need to be shift by 2
char lcdNibbleHigh(char _c) {
	return (_c & 0xF0) >> 2;
}

char lcdNibbleLow(char _c) {
	return (_c & 0x0F) << 2;
}

void lcdNibbleWait() {
	lcdENPluse();
	SysTickWait(5000);
	lcdRS = 0x00;
}

void lcdWriteCommand(unsigned char _c) {
	// Send command
	lcdRS = 0x00;
	SysTickWait(45);
	
	// Shift high nibble left 2
	lcdDB = lcdNibbleHigh(_c);
	lcdENPluse();
	
	SysTickWait(5000);
	
	// Shift low nibble
	lcdDB = lcdNibbleLow(_c);

	lcdNibbleWait();
}


void lcdClearScreen(void) {
	// Send clear command
	lcdWriteCommand(0x01);
}


void lcdWriteData(unsigned char _c) {
	// Send data
	lcdRS = 0x08;
	SysTickWait(45);
	
	// Shift high nibble
	lcdDB = lcdNibbleHigh(_c);
	// Pluse EN and wait
	lcdENPluse();
	
	SysTickWait(250);
	
	// Shift low nibble
	lcdDB = lcdNibbleLow(_c);
	
	lcdNibbleWait();
}

void lcdDeleteData(void) {
	// Shift left
	lcdWriteCommand(0x10);
	// Overwrite by space
	lcdWriteData(' ');
	// Start at the left place
	lcdWriteCommand(0x10);
}


void lcdPosition(unsigned int _row, unsigned int _column) {
	if (_row == 1) {
		lcdWriteCommand((0x00 | _column | 0x80));
	}
	else if (_row == 2) {
		lcdWriteCommand((0x40 | _column | 0x80));
	}
}


void lcdShiftLeft(void) {
	lcdWriteCommand(0x18);
}


void lcdShiftRight(void) {
	lcdWriteCommand(0x1C);
}


void lcdWriteString(char* _string) {
	// Go through entire string by characters
	while (*_string) {
		lcdWriteData(*_string);
		_string++;
	}
}


void LCDInit(void) {
	// Initialise Ports A and B
	PORTA_Init();
	PORTB_Init();
	
	SysTickWait(200);
	// Display in two lines, font height with 8
	lcdWriteCommand(0x28);
	// Cursor blinks, screen on
	lcdWriteCommand(0x08);
	lcdWriteCommand(0x0F);
	// Restart the display
	lcdWriteCommand(0x01);
	// Cursor move and display move
	lcdWriteCommand(0x06);
}

