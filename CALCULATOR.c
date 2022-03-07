/*
* Author: Yadong Hu
* Date: 12/09/2021
* Description:
		Core mathematical calcualtions. Achieved by Stacks.
*/

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "BUFFER.h"
#include "LCD.h"
#include "CALCULATOR.h"


// Global error flag
enum ERROR globalResultFlag = NO_ERROR;

// Store the whole expression
char globalStr0[MAX_SIZE] = { '\0' };
char* globalStr = globalStr0;
// Store the initial address of globalStr
char* globalStrI = globalStr0;
// A copy of raw expression
char* globalPtr = globalStr0;
// Human-readable expression
char globalHtr0[MAX_SIZE * 2] = { '\0' };
char* globalHtr = globalHtr0;
// Store the initial address of globalHtr
char* globalHtrI = globalHtr0;

// Global ANS
double globalANS = 0.0;


double calculate(double _num1, double _num2, char _operator)
{
	switch (_operator)
	{
	case '+':
	{
		return _num1 + _num2;
	}
	case '-':
	{
		return _num1 - _num2;
	}
	case '*':
	{
		return _num1 * _num2;
	}
	case '/':
	{
		if (_num2 == 0.0) {
			globalResultFlag = DIVIDED_BY_ZERO;
			return 0.0;
		}
		else {
			return _num1 / _num2;
		}
	}
	// e: exponential functions.
	case 'e':
	{
		if (_num1 == 0) {
			return 0.0;
		}
		else {
			double _temp = pow(_num1, _num2);
			if (_temp == 0.0) {
				globalResultFlag = INVALID_EXPONENTIAL;
			}
			return _temp;
		}
	}
	// l: logarithmic functions.
	case 'l':
	{
		if (_num1 <= 0 || _num2 <= 0) {
			globalResultFlag = INVALID_LOGARITHM;
			return 0.0;
		}
		else {
			return log(_num2) / log(_num1);
		}
	}
	// .: point, e.g. 3.2
	case '.':
	{
		double _temp = _num2;
		while (_temp >= 1)
		{
			_temp /= 10;
			_num2 *= 0.1;
		}
		return _num1 + _num2;
	}
	default:
		globalResultFlag = UNKOWN;
		return 0.0;
	}
}

int priority(char _operator)
{
	switch (_operator)
	{
	case '+':
	case '-':
	{
		return 1;
	}
	case '*':
	case '/':
	{
		return 2;
	}
	case 'e':
	case 'l':
	{
		return 3;
	}
	case '.':
	{
		return 4;
	}
	default:
	{
		globalResultFlag = UNKOWN;
		return 0;
	}
	}
}

void initNumberStack(double* _stack, int* _top)
{
	int i = 0;
	for (; i < MAX_SIZE; i++)
	{
		_stack[i] = 0.0;
	}
	*_top = -1;
}

void initOperatorStack(char* _stack, int* _top)
{
	int i = 0;
	for (; i < MAX_SIZE; i++)
	{
		_stack[i] = 0;
	}
	*_top = -1;
}

enum STACK isStackFull(int* _top)
{
	return *_top == (MAX_SIZE - 1) ? STACK_FULL : STACK_NOT_FULL;
}

enum STACK isStackEmpty(int* _top)
{
	return *_top == -1 ? STACK_EMPTY : STACK_NOT_FULL;
}

enum STACK pushNumber(double* _stack, double* _num, int* _top)
{
	if (isStackFull(_top) == STACK_FULL)
	{
		return STACK_FULL;
	}
	(*_top)++;
	_stack[*_top] = *_num;
	return PUSH_SUCCESS;
}

enum STACK pushOperator(char* _stack, char* _operator, int* _top)
{
	if (isStackFull(_top) == STACK_FULL)
	{
		return STACK_FULL;
	}
	(*_top)++;
	_stack[*_top] = *_operator;
	return PUSH_SUCCESS;
}

double popNumber(double* _stack, int* _top)
{
	double _num;
	if (isStackEmpty(_top) == STACK_EMPTY)
	{
		return STACK_EMPTY;
	}
	_num = _stack[*_top];
	(*_top)--;
	return _num;
}

char popOperator(char* _stack, int* _top)
{
	char _operator;
	if (isStackEmpty(_top) == STACK_EMPTY)
	{
		return STACK_EMPTY;
	}
	_operator = _stack[*_top];
	(*_top)--;
	return _operator;
}

enum STACK comparePriority(char* _raw, char* _stackOperator, int* _topOperator, double* _stackNumber, int* _topNumber)
{
	double _num, _numAfter, _result;
	char _operator;
	// Last of the expression marked as '\0'
	if (*_raw == '\0')
	{
		return COM_SUCCESS;
	}
	if (isStackFull(_topOperator) == STACK_FULL)
	{
		return STACK_FULL;
	}
	// Start of the bracket
	else if (isStackEmpty(_topOperator) == STACK_EMPTY || *_raw == '(')
	{

		pushOperator(_stackOperator, _raw, _topOperator);
	}
	// End of the bracket, calculate the block result
	else if (*_raw == ')')
	{
		// Pop an operator
		_operator = popOperator(_stackOperator, _topOperator);
		while (_operator != '(')
		{
			// Pop two numbers
			_num = popNumber(_stackNumber, _topNumber);
			_numAfter = popNumber(_stackNumber, _topNumber);
			// Calculate the result
			_result = calculate(_numAfter, _num, _operator);
			// Save the result in number stack
			pushNumber(_stackNumber, &_result, _topNumber);
			_operator = popOperator(_stackOperator, _topOperator);
		}
	}
	// Non-brackets operators
	else
	{
		_operator = popOperator(_stackOperator, _topOperator);
		// The parsed operator '(' should be pushed into the stack
		if (_operator == '(')
		{
			pushOperator(_stackOperator, &_operator, _topOperator);
			pushOperator(_stackOperator, _raw, _topOperator);
			return COM_SUCCESS;
		}
		_num = priority(_operator);
		_numAfter = priority(*_raw);
		// If the priority of the parsed operator is greater than the priority of the element at the top of the stack, 
		// the parsed operator should be pushed into the stack
		if (_numAfter > _num)
		{
			pushOperator(_stackOperator, &_operator, _topOperator);
			pushOperator(_stackOperator, _raw, _topOperator);
		}
		// Pop the two numbers and the operator to calculate
		else
		{
			_num = popNumber(_stackNumber, _topNumber);
			_numAfter = popNumber(_stackNumber, _topNumber);
			_result = calculate(_numAfter, _num, _operator);
			// Save the result into the stack and continuing compare the priority
			pushNumber(_stackNumber, &_result, _topNumber);
			comparePriority(_raw, _stackOperator, _topOperator, _stackNumber, _topNumber);
		}
	}
	return COM_SUCCESS;
}

int machineToHuman(char* _machineExp, char* _humanExp) {
	// Human expression count
	int _count = 0;
	// Replace machine expression to human expression
	while (*_machineExp != '\0') {
		if (*_machineExp == '*') {
			*_humanExp = 'x';
		}
		else if (*_machineExp == 'e') {
			*_humanExp = '^';
		}
		else if (*_machineExp == 'p') {
			*_humanExp = 'P';
			_humanExp++;
			_count++;
			*_humanExp = 'I';
		}
		else if (*_machineExp == 'l') {
			// Determine how many digits before 'l'
			int _i = 1;
			int _j = 1;
			for (; (*(_machineExp - _i) >= '0' && *(_machineExp - _i) <= '9') || (*(_machineExp - _i) == '.'); _i++);
			_humanExp -= _i - 2;
			_count -= _i - 2;
			*(_humanExp - 1) = 'l';
			*_humanExp = 'o';
			*(_humanExp + 1) = 'g';
			_humanExp += 2;
			_count += 2;
			// Insert numbers before 'l'
			for (; _j <= _i - 1; _j++) {
				*_humanExp = *(_machineExp - _i + _j);
				_humanExp++;
				_count++;
			}
			*_humanExp = '(';
			_humanExp++;
			_count++;
			// Determine how many digits after 'l'
			_i = 1;
			for (; (*(_machineExp + _i) >= '0' && *(_machineExp + _i) <= '9') || (*(_machineExp + _i) == '.'); _i++);
			// Insert numbers after 'l'
			_j = 1;
			for (; _j <= _i - 1; _j++) {
				_machineExp++;
				*_humanExp = *_machineExp;
				_humanExp++;
				_count++;
			}
			*_humanExp = ')';
		}
		else if (*_machineExp == 'a') {
			*_humanExp = 'A';
			_humanExp++;
			_count++;
			*_humanExp = 'N';
			_humanExp++;
			_count++;
			*_humanExp = 'S';
		}


		else {
			*_humanExp = *_machineExp;
		}
		_machineExp++;
		_humanExp++;
		_count++;
	}
	(*_humanExp) = '\0';
	return _count + 1;
}

double removeZeros(double _num) {
	char _buff[48];
	int _len;
	_len = snprintf(_buff, sizeof(_buff), "%.6f", _num);
	char* p = _buff + _len - 1;
	while (*p == '0') {
		*p-- = 0;
	}
	if (*p == '.')
		*p = 0;
	return atof(_buff);
}


double startCalculator(double _last_result) {
	// Two calculating numbers, final result
	double num = 0.0f, numAfter = 0.0f, result = 0.0f;
	// Operator for each calculation
	char operatorC = 0;

	// An integer number (read in characters)
	char phrase0[MAX_SIZE] = { '\0' };
	char* phrase = phrase0;
	char* temp = phrase;

	// Initialize number stack
	double stackNumber[MAX_SIZE] = { 0.0f };
	int topNumber = 0;

	// Initialize Operator stack
	char stackOperator[MAX_SIZE] = { '\0' };
	int topOperator = 0;

	// Copy of bufferList
	unsigned char* bufferList = getBufferList();

	// Iterator
	int i = 0;

	// Number of digits of the result expression
	int resultExpDigits = 0;
	int resultDigits = 0;
	double resultDecimal = 0.0f;
	int resultDecimalDigits = 0;

	// Result flag
	int resultMinus = 0;

	// Initialize ANS
	globalANS = _last_result;

	// Transform integer number to string
	char resultString[MAX_SIZE] = { '\0' };

	initNumberStack(stackNumber, &topNumber);
	initOperatorStack(stackOperator, &topOperator);

	// Input
	while (bufferList[i] != '\0') {
		globalStr[i] = bufferList[i];
		i++;
	}
	globalStr[i] = '\0';

	while (*globalStr != '\0')
	{
		// Parse consecutive numeric characters as integers and push them into the number stack
		if (*globalStr >= '0' && *globalStr <= '9')
		{
			// A phrase 
			while (*globalStr >= '0' && *globalStr <= '9')
			{
				*temp = *globalStr;
				globalStr++;
				temp++;
			}
			// One integer is over
			*temp = '\0';
			temp = phrase;
			// Convert string to integer
			num = atoi(phrase);
			pushNumber(stackNumber, &num, &topNumber);
		}
		// Convert p to p(3.1415926)
		if (*globalStr == 'p') {
			double _temp = PI;
			pushNumber(stackNumber, &_temp, &topNumber);
			globalStr++;
		}
		// Convert ANS to corresponds value
		if (*globalStr == 'a') {
			double _temp = globalANS;
			pushNumber(stackNumber, &_temp, &topNumber);
			globalStr++;
		}
		// Compare the priorities among all operators, and push them into stack
		comparePriority(globalStr, stackOperator, &topOperator, stackNumber, &topNumber);

		if (*globalStr == '\0')
		{
			break;
		}
		globalStr++;
	}

	// Pop two numbers in number stack and calculate them using the top operator
	while (topOperator != -1)
	{
		num = popNumber(stackNumber, &topNumber);
		numAfter = popNumber(stackNumber, &topNumber);
		operatorC = popOperator(stackOperator, &topOperator);
		result = calculate(numAfter, num, operatorC);
		// Push the result back into the number stack
		// The last number in number stack is the expression calculation result
		pushNumber(stackNumber, &result, &topNumber);
	}

	// Convert machine code to human code
	resultExpDigits = machineToHuman(globalPtr, globalHtr);

	// Remove unnessary zeros, e.g. 2.3000 -> 2.3
	result = removeZeros(result);

	// Output

	// If the result is an integer
	if (floor(result + 0.5) == result) {
		// Clear the hand-write expression
		lcdClearScreen();
		// Show the machine-style expression
		lcdWriteString(globalHtr);

		resultMinus = result < 0 ? 1 : 0;
		result = abs((int)result);

		if ((int)result == 0) {
			resultDigits = 1;
		}
		else {
			resultDigits = log10((int)result) + 1;
		}

		// Convert int type into string type
		sprintf(resultString, "%d", (int)result);

		// Locate the position
		if (resultExpDigits <= 16) {
			// Add a '-' and '=' sign
			if (resultMinus == 1) {
				lcdPosition(2, 16 - resultDigits - 3);
				lcdWriteData('=');
				lcdWriteData(' ');
				lcdWriteData('-');
			}
			else {
				lcdPosition(2, 16 - resultDigits - 2);
				lcdWriteData('=');
				lcdWriteData(' ');
			}
		}
		else {
			// Add a '-' and '=' sign
			if (resultMinus == 1) {
				lcdPosition(2, resultExpDigits - resultDigits - 3 + 1);
				lcdWriteData('=');
				lcdWriteData(' ');
				lcdWriteData('-');
			}
			else {
				lcdPosition(2, resultExpDigits - resultDigits - 2 + 1);
				lcdWriteData('=');
				lcdWriteData(' ');
			}
		}
		// Show the result
		lcdWriteString(resultString);
	}
	// Or the float value
	else {
		lcdClearScreen();
		lcdWriteString(globalHtr);

		resultMinus = result < 0 ? 1 : 0;

		if (abs((int)result) == 0) {
			resultDigits = 1;
		}
		else {
			resultDigits = log10(abs((int)result)) + 1;
		}
		resultDecimal = result - (int)result;
		resultDecimal = resultDecimal > 0 ? resultDecimal : -resultDecimal;


		// Calculate the digits
		while (resultDecimal >= 0.00001 && resultDecimalDigits <= 6) {
			resultDecimal = resultDecimal * 10;
			resultDecimalDigits = resultDecimalDigits + 1;
			resultDecimal = resultDecimal - (int)resultDecimal;
		}

		// Don't forget the point
		resultDigits += (resultDecimalDigits + 1);

		// Convert float to string
		sprintf(resultString, "%f", result);

		// Locate the position
		if (resultExpDigits <= 16) {
			// Add a '-' and '=' sign
			lcdPosition(2, 16 - resultDigits - 2);
			lcdWriteData('=');
			lcdWriteData(' ');
		}
		else {
			// Add a '-' and '=' sign
			lcdPosition(2, resultExpDigits - resultDigits);
			lcdWriteData('=');
			lcdWriteData(' ');
		}

		// Show the result
		lcdWriteString(resultString);
	}

	// Initialize pointers
	globalHtr = globalHtr0;
	globalStr = globalStr0;

	// Save for ANS
	globalANS = result;

	return result;
}

