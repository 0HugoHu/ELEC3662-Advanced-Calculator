/*
* Author: Yadong Hu
* Date: 11/25/2021
* Description:
		All ports declarations
*/

#ifndef PORT_H
#define PORT_H

// Input for keypad
#define output               		(*((volatile unsigned long *)0x4000703C))  
// Output for keypad
#define input                		(*((volatile unsigned long *)0x4002403C))
	
// Bit Specific Ports 
// RS - PA3
#define lcdRS 									(*((volatile unsigned long *) 0x40004020)) 
// EN - PA2
#define lcdEN 									(*((volatile unsigned long *) 0x40004010)) 
// DB4 - PB2 , DB5 - PB3 , DB6 - PB4 , DB7 - PB5
#define lcdDB 									(*((volatile unsigned long *) 0x400050F0)) 

// Port Declaration
#define GPIO_PORTA_DATA_R       (*((volatile unsigned long *)0x400043FC))
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_PUR_R        (*((volatile unsigned long *)0x40004510))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_LOCK_R       (*((volatile unsigned long *)0x40004520))
#define GPIO_PORTA_CR_R         (*((volatile unsigned long *)0x40004524))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))

#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x400053FC))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_PUR_R        (*((volatile unsigned long *)0x40005510))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_LOCK_R       (*((volatile unsigned long *)0x40005520))
#define GPIO_PORTB_CR_R         (*((volatile unsigned long *)0x40005524))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))

#define GPIO_PORTD_DATA_R       (*((volatile unsigned long *)0x400073FC))
#define GPIO_PORTD_DIR_R        (*((volatile unsigned long *)0x40007400))
#define GPIO_PORTD_AFSEL_R      (*((volatile unsigned long *)0x40007420))
#define GPIO_PORTD_PUR_R        (*((volatile unsigned long *)0x40007510))
#define GPIO_PORTD_DEN_R        (*((volatile unsigned long *)0x4000751C))
#define GPIO_PORTD_LOCK_R       (*((volatile unsigned long *)0x40007520))
#define GPIO_PORTD_CR_R         (*((volatile unsigned long *)0x40007524))
#define GPIO_PORTD_AMSEL_R      (*((volatile unsigned long *)0x40007528))
#define GPIO_PORTD_PCTL_R       (*((volatile unsigned long *)0x4000752C))

#define GPIO_PORTE_DATA_R  			(*((volatile unsigned long *) 0x400243FC))
#define GPIO_PORTE_DIR_R   			(*((volatile unsigned long *) 0x40024400))
#define GPIO_PORTE_AFSEL_R  		(*((volatile unsigned long *) 0x40024420))
#define GPIO_PORTE_PUR_R  			(*((volatile unsigned long *) 0x40024510))
#define GPIO_PORTE_PDR_R				(*((volatile unsigned long *) 0x40024514))
#define GPIO_PORTE_ODR_R				(*((volatile unsigned long *) 0x4002450C))
#define GPIO_PORTE_DEN_R   			(*((volatile unsigned long *) 0x4002451C))
#define GPIO_PORTE_AMSEL_R  		(*((volatile unsigned long *) 0x40024528))
#define GPIO_PORTE_PCTL_R   		(*((volatile unsigned long *) 0x4002452C))
#define GPIO_PORTE_IS_R 				(*((volatile unsigned long *) 0x40024404))
#define GPIO_PORTE_IBE_R 				(*((volatile unsigned long *) 0x40024408))
#define GPIO_PORTE_IEV_R  			(*((volatile unsigned long *) 0x4002440C))
#define GPIO_PORTE_ICR_R 				(*((volatile unsigned long *) 0x4002441C))
#define GPIO_PORTE_IM_R 				(*((volatile unsigned long *) 0x40024410))

#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))

#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

#define NVIC_PRI1_R 						(*((volatile unsigned long *) 0xE000E404))
#define NVIC_EN0_R 							(*((volatile unsigned long *) 0xE000E100))

// EEPROM defines
#define EEPROM_RCGC 						(*((volatile unsigned long *) 0x400FE658))
#define EEPROM_LOCK							(*((volatile unsigned long *) 0x400AF004))
#define EEPROM_OFFSET						(*((volatile unsigned long *) 0x400AF008))
#define EEPROM_RDWR							(*((volatile unsigned long *) 0x400AF010))
#define EEPROM_PR 							(*((volatile unsigned long *) 0x400FEA58))
#define	EEPROM_FINISHED 				(*((volatile unsigned long *) 0x400AF018))
	
//PLL related Defines
#define SYSCTL_RIS_R          (*((volatile unsigned long *)0x400FE050))	
#define SYSCTL_RCC_R          (*((volatile unsigned long *)0x400FE060))
#define SYSCTL_RCC2_R         (*((volatile unsigned long *)0x400FE070))	

//SysTick related Defines	
#define NVIC_ST_CTRL_R        (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R      (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R     (*((volatile unsigned long *)0xE000E018))

#endif
