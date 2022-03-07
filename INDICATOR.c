/*
* Author: Yadong Hu
* Date: 12/29/2021
* Description:
* 	Switch LEDs status based on situations.
*/

#include "PORT.h"
#include "PLL.h"

unsigned char state = 0x00;

void PORTF_Init(void) {
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x20;
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTF_CR_R |= 0x1E;
	GPIO_PORTF_AMSEL_R &= 0x00;
	GPIO_PORTF_PCTL_R &= 0x00;
	GPIO_PORTF_DIR_R &= ~0x00;
	GPIO_PORTF_DIR_R |= 0x1E;
	GPIO_PORTF_AFSEL_R &= 0x00;
	GPIO_PORTF_PUR_R &= 0x00;
	GPIO_PORTF_DEN_R |= 0x1E;
}


void setLEDState(unsigned char _state) {
	int _i = 0;
	state = _state;
	switch (state) {
	case 0x00:
		// Turn on LED0 (GPIOF1) for normal state
		GPIO_PORTF_DATA_R = 0x02;
		break;
	case 0x01:
		// Turn on LED1 (GPIOF2) for shift state
		GPIO_PORTF_DATA_R = 0x06;
		break;
	case 0x02:
		// Turn on LED2 (GPIOF3) for double shift state
		GPIO_PORTF_DATA_R = 0x0E;
		break;
	case 0x10:
		// Lock state
		GPIO_PORTF_DATA_R = 0x1E;
		break;
	case 0x11:
		// Operation succeed
		while (_i < 3) {
			GPIO_PORTF_DATA_R = 0x1E;
			// Wait for 200 mili seconds
			SysTickWait(200 * 1000);
			GPIO_PORTF_DATA_R = 0x00;
			SysTickWait(200 * 1000);
			_i++;
		}
		break;
	case 0x20:
		// Log in
		while (_i < 3) {
			GPIO_PORTF_DATA_R = 0x06;
			// Wait for 200 mili seconds
			SysTickWait(100 * 1000);
			GPIO_PORTF_DATA_R = 0x0C;
			SysTickWait(100 * 1000);
			GPIO_PORTF_DATA_R = 0x18;
			SysTickWait(100 * 1000);
			GPIO_PORTF_DATA_R = 0x12;
			SysTickWait(100 * 1000);
			_i++;
		}
		break;
	case 0xFF:
	default:
		// Error
		// Reset state to normal
		GPIO_PORTF_DATA_R = 0x10;
		// Wait for 1.5 seconds
		SysTickWait(1.5 * 1000 * 1000);
		state = 0x00;
		// Reset LED indicator
		GPIO_PORTF_DATA_R = 0x02;
		break;
	}
}

void indicatorInit(void) {
	PORTF_Init();
	// Set a error value to test the LED
	setLEDState(0xFF);
}

unsigned char readLEDState(void) {
	return state;
}
