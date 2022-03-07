/*
* Author: Yadong Hu
* Date: 12/29/2021
* Description:
* 	Switch LEDs status based on situations.
*/


#ifndef INDICATOR_H
#define INDICATOR_H

// Initialize PORTF
// PF4-1 for output LEDs
extern void PORTF_Init(void);

// Initialize Port F for indicator LEDs
extern void indicatorInit(void);

// Read key A state
// 0x00 - Normal
// 0x01 - Shift A
// 0x02 - Double Shift A
// 0xFF - Error
extern unsigned char readLEDState(void);

// Light LEDs according to the state
extern void setLEDState(unsigned char);

#endif
