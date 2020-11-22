/** @file main.c
 * Guesser program main file.
 * Thus utility knows your number!
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>
#include "roman.h"
#include "config.h"

/** Macro for string localization */
#define _(STRING) gettext(STRING)

/** Path to localizations */
#define LOCALE_PATH "."

/** Minimum possible number to guess */
#define MIN_NUM 1

/** Maximum possible number to guess */
#define MAX_NUM 3999

/** Help string */
#define MANUAL _("Guesser is utility for guessing number\n\
\n\
Usage: guesser [OPTIONS]\n\
\n\
    --help      print this help, then exit\n\
    --version   print version number, then exit\n\
    -r          use roman numbers instead of ususal integers\n\
\n\
This program knows your number!\n\
It can work with integer and roman numbers\n\
")


/**
 * Tries to guess user number
 * 
 * @param is_roman It is a flag. It equals to 0 if need print numbers as integer and equals to 1 if need print numbers as roman.
 */
void NumberGuesser(int is_roman) {
    printf("%s ", _("Guess number between"));
    PrintNum(MIN_NUM, is_roman);
    printf(" %s ", _("and"));
    PrintNum(MAX_NUM, is_roman);
    printf(".\n");
    int left = MIN_NUM - 1, right = MAX_NUM;
    char ans[11];
    while (right - left > 1) {
        int mid = (left + right) / 2;
        int is_ok_input = 0;
        while (!is_ok_input) {
            is_ok_input = 1;
            printf("%s ", _("Is number greater than"));
            PrintNum(mid, is_roman);
            printf("? %s/%s: ", _("yes"), _("no"));
            scanf("%10s", ans);
            if (!strcmp(ans, _("yes"))) {
                left = mid;
            } else if (!strcmp(ans, _("no"))) {
                right = mid;
            } else {
                fprintf(stderr, _("Bad input, try again\n"));
                is_ok_input = 0;
            }
        }
    }
    printf("%s ", _("Number is"));
    PrintNum(right, is_roman);
    printf("\n");
}

/**
 * Main function
 */
int main(int argc, char *argv[])
{
    setlocale (LC_ALL, "");
    bindtextdomain("guesser", ".");
    textdomain ("guesser");

    int is_roman = 0;

    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "--help")) {
            return !printf("%s\n", MANUAL);
        } else if (!strcmp(argv[i], "--version")) {
            return !printf("guesser %s\n", VERSION);
        } else if (!strcmp(argv[i], "-r")) {
            is_roman = 1;
        }
    }

    NumberGuesser(is_roman);
    return 0;
}

