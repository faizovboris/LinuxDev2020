/** @file roman.c
 * Implementation of utilities for working with roman numbers from `roman.h`.
 */
#ifndef ROMAN_C_INCLUDED
#define ROMAN_C_INCLUDED
#include "roman.h"

int CharToNum(char c) {
    switch (c) {
    case 'I':
        return 1;
    case 'V':
        return 5;
    case 'X':
        return 10;
    case 'L':
        return 50;
    case 'C':
        return 100;
    case 'D':
        return 500;
    case 'M':
        return 1000;
    }
    return -1;
}

int RomanToInteger(char* str) {
    int n = strlen(str);
    int ans = 0;
    int next_char_num = 0;
    for (int i = n - 1; i >= 0; --i) {
        int cur_char_num = CharToNum(str[n - 1]);
        if (cur_char_num == -1) {
            return -1;
        }
        if (cur_char_num < next_char_num) {
            ans -= cur_char_num;
        } else {
            ans += cur_char_num;
        }
        next_char_num = cur_char_num;
    }
    return ans;
}

char* IntegerToRoman(int n) {
    const char* thousands[] = {"", "M", "MM", "MMM"};
    const char* hundreds[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    const char* tens[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    const char* ones[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
    if (n >= 4000) {
        return NULL;
    }
    char *ans = malloc(4000 * sizeof(*ans));
    ans[0] = '\0';
    strcat(ans, thousands[n / 1000]);
    strcat(ans, hundreds[n % 1000 / 100]);
    strcat(ans, tens[n % 100 / 10]);
    strcat(ans, ones[n % 10]);
    ans = realloc(ans, strlen(ans) + 1);
    return ans;
}

void PrintNum(int n, int is_roman) {
    if (is_roman) {
        char* roman = IntegerToRoman(n);
        printf("%s", roman);
        free(roman);
    } else {
        printf("%d", n);
    }
}

#endif