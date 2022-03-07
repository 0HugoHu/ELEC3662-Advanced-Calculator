/*
* Author: Yadong Hu
* Date: 11/14/2021
* Description:
		System global wait() function

*	Referenced from course materials
*/

#ifndef PLL_H
#define PLL_H

// Initialize PLL
extern void PLLInit(void);

// Pause for a given period, unit in us
extern void SysTickWait(unsigned long delay);

#endif
