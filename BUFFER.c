/*
* Author: Yadong Hu
* Date: 12/03/2021
* Description:
		Display currently pressed keys on the LCD
		Also store the input strings.
*/


#include "INDICATOR.h"
#include "LCD.h"

// Maximum input length
#define MAX_SIZE 41

unsigned char bufferList[MAX_SIZE];
int position = -1;

void bufferInit(void) {
	// Empty String
	int i = 0;
	for (; i < MAX_SIZE; i++) {
		bufferList[i] = '\0';
	}
	position = -1;
}

unsigned char* getBufferList(void) {
	return bufferList;
}

void addBuffer(unsigned char _character) {
	if (position < MAX_SIZE - 1) {
		position++;
		bufferList[position] = _character;
		bufferList[position + 1] = '\0';
		// Display the newly added character
		lcdWriteData(bufferList[position]);
		// If the line is full, shift the screen to the right
		if (position >= 15) {
			lcdShiftLeft();
		}
	}
	else {
		// Error state
		setLEDState(0xFF);
	}
}


void delBuffer(int _mode) {
	if (_mode == 0) {
		lcdClearScreen();
		bufferInit();
	}
	else {
		if (position >= 0) {
			bufferList[position] = '\0';
			position--;
			lcdDeleteData();
		}
		else {
			// Error state
			setLEDState(0xFF);
		}
	}
}


void updateBufferDisplay(int _position) {
	int _i = 0;
	if (_position == -1) {
		while (bufferList[_i] != '\0') {
			lcdWriteData(bufferList[_i]);
		}
	}
}
