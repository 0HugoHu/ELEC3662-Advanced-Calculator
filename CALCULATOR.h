/*
* Author: Yadong Hu
* Date: 12/09/2021
* Description:
		Core mathematical calcualtions. Achieved by Stacks.
*/

#ifndef CALCULATOR_H
#define CALCULATOR_H

// Maximum input length
#define MAX_SIZE 40

#define PI 3.1415926


// Variables for each button
enum STATE {
	NORMAL,
	SINGLE,
	DOUBLE,
	TRIPLE
};

// Calculation error state
enum ERROR
{
	NO_ERROR,
	DIVIDED_BY_ZERO,
	INVALID_EXPONENTIAL,
	INVALID_LOGARITHM,
	OUT_OF_RANGE,
	MAX_CHARACTER,
	UNKOWN
};

// Stack operation state
enum STACK
{
	STACK_FULL,
	STACK_NOT_FULL,
	STACK_EMPTY,
	COM_SUCCESS,
	PUSH_SUCCESS
};


// Calculate the result of one minimized expression
double calculate(double _num1, double _num2, char _operator);

// Priority of the operators
int priority(char _operator);

// Number stack initialization
void initNumberStack(double* _stack, int* _top);

// Operator stack initialization
void initOperatorStack(char* _stack, int* _top);

// Check if the stack is full
enum STACK isStackFull(int* _top);

// Check if the stack is empty
enum STACK isStackEmpty(int* _top);

// Push number stack
enum STACK pushNumber(double* _stack, double* _num, int* _top);

// Push operator stack
enum STACK pushOperator(char* _stack, char* _operator, int* _top);

// Pop number stack
double popNumber(double* _stack, int* _top);

// Pop operator stack
char popOperator(char* _stack, int* _top);

// Compare the priority of the parsing operators
// + - * / . e l ( )
// with the priority of the top-of-stack operators,
// and perform various push/pop stack operations according to the rules
enum STACK comparePriority(char* _raw, char* _stackOperator, int* _topOperator, double* _stackNumber, int* _topNumber);

// Convert machine expression to human-readable expression
// e.g. 2*10l200 -> 2xlog10(200)
int machineToHuman(char* _machineExp, char* _humanExp);

// Remove unnessary zeros of a floating number
double removeZeros(double _num);

// Main process
extern double startCalculator(double _last_result);

#endif
