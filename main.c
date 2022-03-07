/*
* Author: Yadong Hu
* Date: 11/14/2021
* Description:
  A calculator running on Tiva C Series TM4C123G implements:
	1. addition, subtraction, multiplication and division.													Completed!
	2. decimal.																																			Completed!
	3. brackets.																																		Completed!
	4. power and logarithmic operations.																						Completed!
	5. deletion and emptying.																												Completed!
	6. constant p.																																	Completed!
	7. the result of the previous operation: ANS.																		Completed!
	8. locking/unlocking and changing passwords.																		Completed!
	9. adjusting the contrast.																										# Abandoned!
	10. animation of locking/unlocking and when operating large calculations.				Completed!
* 
* # I could not achieve this function due to the lack of a sliding resistor.
* # PWM can be used instead, but my GPIO ports are full (Well, I am lazy...).
*
*
* Bug:
*	1. 3++2 3--2 Error results
* 2. Long expression display errors
* 3. Sometimes the result displays unnecessary zeros, e.g. 3.12000
*/

#include <stdio.h>
#include "TExaS.h"
#include "PORT.h"
#include "PLL.h"
#include "LCD.h"
#include "KEY.h"
#include "BUFFER.h"
#include "INDICATOR.h"
#include "CALCULATOR.h"
#include "PASSWORD.h"

/************************/
/*** Global Variables ***/
/************************/

// Current pressed key
unsigned char key = 0x00;
// LED lights indicators
unsigned char led_state = 0x10;
// If currently display the result
unsigned char result_page = 0x00;

// Used for ANS function
double last_result = 0.0f;

// Password stored in EEPROM
unsigned long password_saved = 0;
// Password temperarily entered
unsigned long password_enter = 0;

// Pre-determined waiting time
unsigned long long delay = 1 * 1000 * 1000;

// Current state
enum FSM current_state = LOCK;

// Flag for delay clear function
unsigned char clear_delay_flag = 0x00;


/************************/
/*  Function Prototypes */
/************************/

// Update indicator LEDs based on keypad input
void updateIndicator(void);

// Global finate state machine
void menu(void);
void lock(void);
void password(void);
void login(void);
void calculation(void);

// Delay clear
void clear_delay(void);

// Welcome animation
void animation(void);


/************************/
/*******  Main  *********/
/************************/

int main(void) {

	PLLInit();				// System clock
	passwordInit();		// EEPROM
	LCDInit();				// LCD screen
	keypadInit(); 		// Keypad
	indicatorInit();	// Indicator LEDs
	
	bufferInit();			// Display buffer

	password_saved = getPassword(); 	// Get password from EEPROM

	while (1) {
		// Get key input
		key = readKeypad(led_state, result_page, current_state);
		// Update indicator LEDs
		updateIndicator();
		// Start Finate-State Machine
		menu();
	}
	return 0;

}


/************************/
/*Function Specification*/
/************************/

void updateIndicator(void) {
	switch (current_state) {
	case LOCK:
	case PASSWORD:
		if (led_state != 0x10) {
			setLEDState(led_state);
		}
		setLEDState(0x10);
		led_state = readLEDState();
		break;
	case LOGIN:
		setLEDState(0x20);
		led_state = readLEDState();
		break;
	case CALCULATION:
		// Shift A
		if (key == 'A' || clear_delay_flag == 0x01) {
			led_state = readLEDState();
			// Normal
			if (led_state == 0x00) {
				setLEDState(0x01);
			}
			// Single Shift A
			else if (led_state == 0x01) {
				setLEDState(0x02);
			}
			// Double Shift A
			else if (led_state == 0x02) {
				setLEDState(0x00);
			}
			else {
				setLEDState(0xFF);
			}
			led_state = readLEDState();
		}
		// Lock the calculator
		else if (key == 'K') {
			current_state = LOCK;
		}
		break;
	default:
		break;
	}
}


void menu(void) {
	// Enable delay clear
	if (clear_delay_flag == 0x01) {
		clear_delay();
	}

	switch (current_state) {
	case LOCK:
		lock();
		break;
	case PASSWORD:
		password();
		break;
	case LOGIN:
		login();
		break;
	case CALCULATION:
		calculation();
		break;
	default:
		lock();
		break;
	}
}


void lock(void) {
	char _password_str[MAX_SIZE];

	// Add key number
	if (key >= '0' && key <= '9') {
		password_enter *= 10;
		password_enter += key - '0';
	}
	// Delete a digit
	else if (key == 'Z') {
		password_enter = (int)(password_enter / 10);
		lcdClearScreen();
	}

	// Write string to the first row
	lcdPosition(1, 0);
	lcdWriteString("Enter Password: ");
	lcdPosition(2, 0);

	if (password_enter != 0) {
		// Cast long to string
		sprintf(_password_str, "%lu", password_enter);
		// Display current entered number
		lcdWriteString(_password_str);
	}

	// Correct password, goto LOGIN state
	if (key == '=' && (password_enter == password_saved)) {
		clear_delay_flag = 0x01;
		current_state = LOGIN;
		// Succeed leds
		led_state = 0x11;
	}
	// Incorrect password, clear the password, stay in LOCK state
	else if (key == '=' && (password_enter != password_saved)) {
		delBuffer(0);
		lcdWriteString("Wrong! Please");
		lcdPosition(2, 0);
		lcdWriteString("Re-enter PSW!");
		// Error leds
		led_state = 0xFF;
		clear_delay_flag = 0x01;
	}
	// Goto edit password state
	else if (key == 'B') {
		// Within wrong psw cannot entering editing mode
		if (password_enter != password_saved) {
			delBuffer(0);
			lcdWriteString("Incorrect Old");
			lcdPosition(2, 0);
			lcdWriteString("Password!");
			// Error leds
			led_state = 0xFF;
			clear_delay_flag = 0x01;
		}
		else {
			delBuffer(0);
			current_state = PASSWORD;
			password_enter = 0;
			// Succeed leds
			led_state = 0x11;
		}
	}
}


void password(void) {
	char _password_str[MAX_SIZE];

	// Add key number
	if (key >= '0' && key <= '9') {
		password_enter *= 10;
		password_enter += key - '0';
	}
	// Delete a digit
	else if (key == 'Z') {
		password_enter = (int)(password_enter / 10);
		lcdClearScreen();
	}

	// Write string to the first row
	lcdPosition(1, 0);
	lcdWriteString("New Password:");
	lcdPosition(2, 0);

	if (password_enter != 0) {
		// Cast long to string
		sprintf(_password_str, "%lu", password_enter);
		// Display current entered number
		lcdWriteString(_password_str);
	}

	// Password cannot be 0, 00, 000 ...
	if (key == '=' && password_enter == 0) {
		lcdPosition(1, 0);
		lcdWriteString("PSW Can't be 0!");
		lcdPosition(2, 0);
		// Error leds
		led_state = 0xFF;
		clear_delay_flag = 0x01;
	}
	// Password cannot be large than 99,999,999
	else if (key == '=' && password_enter > 99999999) {
		lcdPosition(1, 0);
		lcdWriteString("PSW Should Have");
		lcdPosition(2, 0);
		lcdWriteString("<= 8 Digits! ");
		// Error leds
		led_state = 0xFF;
		clear_delay_flag = 0x01;
	}
	else if (key == '=') {
		current_state = LOCK;
		// Set the new password to temp
		setPassword(password_enter);
		// Set password store as the new passowrd from EEPROM
		password_saved = getPassword();
		lcdPosition(1, 0);
		lcdWriteString("Password Edit");
		lcdPosition(2, 0);
		lcdWriteString("Succeeded!");
		// Succeed leds
		led_state = 0x11;
		clear_delay_flag = 0x01;
	}
}


void login(void) {
	animation();
	lcdPosition(1, 0);
	lcdWriteString(" >> Welcome <<");
	lcdPosition(2, 0);
	lcdWriteString("@2022 Hu,Yadong");
	SysTickWait(1 * 1000 * 1000);
	current_state = CALCULATION;
	clear_delay_flag = 0x01;
	led_state = 0xFF;
}


void calculation(void) {
	if (key == '=') {
		last_result = startCalculator(last_result);
		result_page = 0x01;
	}
	// End result page
	else if (key == 0xFF) {
		result_page = 0x00;
	}
}


void clear_delay(void) {
	// Clear all the buffer
	delBuffer(0);
	password_enter = 0;
	clear_delay_flag = 0x00;
}


void animation(void) {
	int _i = 0;
	lcdPosition(1, 0);
	while(_i < 16) {
		lcdWriteData('#');
		SysTickWait(50 * 1000);
		_i++;
	}
	_i = 0;
	lcdPosition(2, 0);
	while(_i < 16) {
		lcdWriteData('#');
		SysTickWait(50 * 1000);
		_i++;
	}
	lcdClearScreen();
}
