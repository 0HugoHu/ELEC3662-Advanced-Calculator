/*
* Author: Yadong Hu
* Date: 12/09/2021
* Description:
		Read, edit the password stored in EEPROM.
*/

#include "PLL.h"
#include "PORT.h"

// Password to be shared with main()
unsigned long password_global;
// Default value
unsigned long password_default = 1234L;

void waitPassword(void) {
	while (EEPROM_FINISHED != 0x00);
}

void setPassword(unsigned long _password) {
	EEPROM_LOCK = 0x01;
	EEPROM_OFFSET = 0x01;
	EEPROM_RDWR = _password;
	waitPassword();
	password_global = EEPROM_RDWR;
	waitPassword();
}

unsigned long getPassword(void) {
	return password_global;
}

void passwordInit(void) {
	EEPROM_RCGC = 0x01;
	SysTickWait(150);
	while (EEPROM_PR == 0x00);
	waitPassword();
	SysTickWait(600);
	EEPROM_LOCK = 0x01;
	EEPROM_OFFSET = 0x01;
	if (EEPROM_RDWR == password_default) {
		// if it is not set to 1234. This is the default password_global.
		setPassword(password_default);
	}
	else {
		password_global = EEPROM_RDWR;
		waitPassword();
	}
}

