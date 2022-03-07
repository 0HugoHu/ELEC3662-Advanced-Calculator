/*
* Author: Yadong Hu
* Date: 12/12/2021
* Description:
		Obtain the keypad input based on the global states.
*/

#ifndef KEY_H
#define KEY_H

// Four states
enum FSM { LOCK, PASSWORD, LOGIN, CALCULATION };

// Initialize PORTD
// PD3-0 for input from keypad
extern void PORTD_Init(void);

// Initialize PORTE
// PE3-0 for output to keypad
extern void PORTE_Init(void);

// Read key
/*
*		1		2		3		A
*		4		5		6		B
*		7		8		9		C
*		*		0		#		D
*
* Return value in ASCII code, e.g. 1 -> '1', A -> 'A'
**/
// Input: _led_state - enable Shift A controls
//				_result_page - if it is in result page
//				_current_state - global FSM state
extern unsigned char readKeypad(unsigned char _led_state, unsigned char _result_page, enum FSM _current_state);

// Initialize keypad
extern void keypadInit(void);

#endif
