/*
* Author: Yadong Hu
* Date: 12/09/2021
* Description:
		Read, edit the password stored in EEPROM.
*/

#ifndef PASSWORD_H
#define PASSWORD_H

// Initialize EEPROM
extern void passwordInit(void);

// Password should be less than 8 digits
extern void setPassword(unsigned long);

// Return the password
extern unsigned long getPassword(void);

// Wait for the work to be done
void waitPassword(void);

#endif
