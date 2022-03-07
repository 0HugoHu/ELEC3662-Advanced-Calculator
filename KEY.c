/*
* Author: Yadong Hu
* Date: 12/12/2021
* Description:
		Obtain the keypad input based on the global states.
*/


#include "PORT.h"
#include "PLL.h"
#include "BUFFER.h"
#include "KEY.h"


// Button debounce
unsigned char lastPressed = 0x00;

// Keymap
// Z - delete, N - Answer, P - PI, R - Clear
// L - logarithm, K - Lock
const unsigned char keymap[3][6] = {
	{'A','+','-','=','.','Z'},
	{'A','*','/','N','P','R'},
	{'A','e','L','K','(',')'}
};

void PORTD_Init(void) {
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x08;
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTD_AMSEL_R &= 0x00;
	GPIO_PORTD_PCTL_R &= 0x00;
	GPIO_PORTD_DIR_R |= 0x0F;
	GPIO_PORTD_AFSEL_R &= 0x00;
	GPIO_PORTD_PUR_R |= ~0x0F;
	GPIO_PORTD_DEN_R |= 0x0F;
}

void PORTE_Init(void) {
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000010;
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTE_AMSEL_R &= 0x00;
	GPIO_PORTE_PCTL_R &= 0x00000000;
	GPIO_PORTE_DIR_R &= ~0x0F;
	GPIO_PORTE_AFSEL_R &= 0x00;
	GPIO_PORTE_PDR_R |= 0x0F;
	GPIO_PORTE_ODR_R |= 0x0F;
	GPIO_PORTE_DEN_R |= 0x0F;
	GPIO_PORTE_IS_R &= ~0x0F;     		// Edge-sensitive
	GPIO_PORTE_IBE_R &= ~0x0F;    		// Not both edges
	GPIO_PORTE_IEV_R |= 0x0F;    			// Rising edge event
}

void keypadInit(void) {
	PORTD_Init();
	PORTE_Init();
}

unsigned char readKeypad(unsigned char _led_state, unsigned char _result_page, enum FSM _current_state) {
	// Initial value 0, no key pressed
	int _keyValue = 0x00;

	// Input counter
	int _i = 0;

	// Set output from column 1 (GPIOE0)
	output = 0x01;

	// Prevent error
	if (_led_state > 0x02) {
		_led_state = 0x00;
	}

	// Go through 4 cols
	for (_i = 0; _i <= 3; _i++) {
		// Check column 1
		SysTickWait(1 * 1000);
		if (output == 0x01) {
			SysTickWait(1 * 1000);
			if (input == 0x01) {
				_keyValue = '1';
				break;
			}
			else if (input == 0x02) {
				_keyValue = '4';
				break;
			}
			else if (input == 0x04) {
				_keyValue = '7';
				break;
			}
			else if (input == 0x08) {
				// Load value based on 'A' state
				_keyValue = keymap[_led_state][4];
				break;
			}
		}

		// Check column 2
		else if (output == 0x02) {
			SysTickWait(1 * 1000);
			if (input == 0x01) {
				_keyValue = '2';
				break;
			}
			else if (input == 0x02) {
				_keyValue = '5';
				break;
			}
			else if (input == 0x04) {
				_keyValue = '8';
				break;
			}
			else if (input == 0x08) {
				_keyValue = '0';
				break;
			}
		}

		// Check column 3
		else if (output == 0x04) {
			SysTickWait(1 * 1000);
			if (input == 0x01) {
				_keyValue = '3';
				break;
			}
			else if (input == 0x02) {
				_keyValue = '6';
				break;
			}
			else if (input == 0x04) {
				_keyValue = '9';
				break;
			}
			else if (input == 0x08) {
				_keyValue = keymap[_led_state][5];
				break;
			}
		}

		// Check column 4
		else if (output == 0x08) {
			SysTickWait(1 * 1000);
			if (input == 0x01) {
				_keyValue = keymap[_led_state][0];
				break;
			}
			else if (input == 0x02) {
				_keyValue = keymap[_led_state][1];
				break;
			}
			else if (input == 0x04) {
				_keyValue = keymap[_led_state][2];
				break;
			}
			else if (input == 0x08) {
				_keyValue = keymap[_led_state][3];
				break;
			}
		}

		// Shift to the next col
		output = output << 1;

	} // end for loop


	// At least trigered twice can be regarded as button pressed
	if (_keyValue != lastPressed) {
		lastPressed = _keyValue;
		SysTickWait(10 * 1000);
		return 0x00;
	}


	// If shown the result, press any key to quit
	if (_result_page == 0x01 && _keyValue != 0x00) {
		_keyValue = 0xFF;
	}

	// Show the char to the display
	// Keymap
	// Z - delete, N - Answer, P - PI, R - Clear
	// L - logarithm, K - Lock
	switch (_keyValue) {
	case 'Z':
		// if in other modes, do nothing
		(_current_state == CALCULATION) ? delBuffer(1) : 1;
		break;
	case 'N':
		(_current_state == CALCULATION) ? addBuffer('a') : 1;
		break;
	case 'P':
		(_current_state == CALCULATION) ? addBuffer('p') : 1;
		break;
	case 'L':
		(_current_state == CALCULATION) ? addBuffer('l') : 1;
		break;
	case 0xFF:
	case 'R':
		delBuffer(0);
		break;
	case 'K':
	case 0x00:
	case 'A':
	case '=':
		break;
	default:
		if (_current_state == CALCULATION) {
			addBuffer(_keyValue);
		}
		// Button B -> goto Edit PASSWORD mode 
		else if (_keyValue == '+' || _keyValue == '*' || _keyValue == 'e') {
			_keyValue = 'B';
		}
	}

	if (_current_state == LOCK && (_keyValue == '=' || _keyValue == 'N' || _keyValue == 'K')) {
		_keyValue = '=';
	}

	// If any key was pressed, wait for a long time
	// to prevent fluctuations. Otherwise, wait for
	// a short time to elimate delays.
	if (_keyValue != 0x00) {
		SysTickWait(300 * 1000);
	}
	else {
		SysTickWait(50);
	}

	return _keyValue;
}
