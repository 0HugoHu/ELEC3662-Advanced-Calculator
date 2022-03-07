/*
* Author: Yadong Hu
* Date: 11/30/2021
* Description:
		Display a character or strings on the LCD screen.
*/

#ifndef LCD_H
#define LCD_H


// Initialize PORTA
// PA3-2 for LCD configurations
extern void PORTA_Init(void);

// Initialize PORTB
// PB7-0 for output data bits
extern void PORTB_Init(void);

// Initialization for LCD
extern void LCDInit(void);
extern void lcdENPluse(void);

// Display chars, commands, or strings
extern void lcdWriteCommand(unsigned char _c);
extern void lcdWriteData(unsigned char _c);
extern void lcdWriteString(char* _string);

// Convert to Low Nibble
char lcdNibbleLow(char _c);
// Convert to High Nibble
char lcdNibbleHigh(char _c);
// Wait while sending data
void lcdNibbleWait(void);

// Clear the last bit
extern void lcdDeleteData(void);
// Clear the full screen
extern void lcdClearScreen(void);

// Shift cursor position
extern void lcdPosition(unsigned int _row, unsigned int _column);
extern void lcdShiftLeft(void);
extern void lcdShiftRight(void);


#endif
