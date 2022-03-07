/*
* Author: Yadong Hu
* Date: 11/14/2021
* Description:
		System global wait() function

*	Adapted from course materials
*/

#include "PORT.h"


void PLLInit(void) {
	// PLL INIT
	SYSCTL_RCC2_R |= 0x80000000;
	SYSCTL_RCC2_R |= 0x00000800;
	SYSCTL_RCC_R = (SYSCTL_RCC_R & ~0x000007C0) + 0x00000540;
	SYSCTL_RCC2_R &= ~0x00000070;
	SYSCTL_RCC2_R &= ~0x00002000;
	SYSCTL_RCC2_R |= 0x40000000;
	SYSCTL_RCC2_R = (SYSCTL_RCC2_R & ~0x1FC00000) + (4 << 22);
	while ((SYSCTL_RIS_R & 0x00000040) == 0) {};
	SYSCTL_RCC2_R &= ~0x00000800;
	
	// SystemTick INIT
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 0x00FFFFFF;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R = 0x00000005;
}

// 20 ns
void wait(unsigned long delay) {
	NVIC_ST_RELOAD_R = delay - 1;
	NVIC_ST_CURRENT_R = 0;
	while ((NVIC_ST_CTRL_R & 0x00010000) == 0) {
	}
}

// Wait in us 
void SysTickWait(unsigned long delay) {
	unsigned long i = 0;
	for (; i < delay; i++) {
		wait(80); // 1us
	}
}


