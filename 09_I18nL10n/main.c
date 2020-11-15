#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "."

#define MIN_NUM 0
#define MAX_NUM 100

int main(int argc, char *argv[])
{
    setlocale (LC_ALL, "");
    if (getenv("PO_LOCAL"))
        bindtextdomain("guesser", LOCALE_PATH);
    else
        bindtextdomain("guesser", "usr/share/locale");
    textdomain ("guesser");

    printf("%s %d %s %d.\n", _("Guess number between"), MIN_NUM, _("and"), MAX_NUM);

    int left = MIN_NUM - 1, right = MAX_NUM;
    char ans[11];
    while (right - left > 1) {
        int mid = (left + right) / 2;
        int is_ok_input = 0;
        while (!is_ok_input) {
            is_ok_input = 1;
            printf("%s %d? %s/%s: ", _("Is number greater than"), mid, _("yes"), _("no"));
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
    printf("%s %d\n", _("Number is"), right);
    return 0;
}

