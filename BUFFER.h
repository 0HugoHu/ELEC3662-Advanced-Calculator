/*
* Author: Yadong Hu
* Date: 12/03/2021
* Description:
		Display currently pressed keys on the LCD
		Also store the input strings.
*/

#ifndef BUFFER_H
#define BUFFER_H

// Add a character to the buffer
extern void addBuffer(unsigned char);

// Delete character to the buffer
// int mode: 0 - delete all, 1 - delete last one
extern void delBuffer(int);

// Update screen
// int position: update current position
extern void updateBufferDisplay(int);

// Initialization
extern void bufferInit(void);

// Return a copy of bufferList
extern unsigned char* getBufferList(void);

#endif
