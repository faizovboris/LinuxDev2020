/** @file roman.h
 * Utilities for working with roman numbers.
 * This lib consists of four functions.
 */
#ifndef ROMAN_H_INCLUDED
#define ROMAN_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Get representation of roman char as integer number
 * 
 * @param c roman char
 * @returns Integer number equal to given roman char. "-1" if roman char is invalid.
 */
int CharToNum(char c);

/**
 * Get representation of roman number string as integer number
 * 
 * @param str roman number string
 * @returns Integer number equal to given string with roman number.
 */
int RomanToInteger(char* str);

/**
 * Get representation of integer number as roman number string
 * 
 * @param n integer number
 * @returns String with roman number equal to given integer. "NULL" if integer number is invalid and do not have representation.
 */
char* IntegerToRoman(int n);

/**
 * Prints integer as roman number or as integer number depending on parameter is_roman.
 * 
 * @param n number to pring
 * @param is_roman It is a flag. It equals to 0 if need print as integer and equals to 1 if need print as roman.
 */
void PrintNum(int n, int is_roman);

#endif