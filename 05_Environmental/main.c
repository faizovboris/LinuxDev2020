#include <ncurses.h>
#include <config.h>
#include <locale.h>
#include <stdlib.h>
#include "pcre_ops.h"

#define DX 3
#define ONLELINE 3
#define MAXSTR 80

void main() {
    setlocale(LC_ALL, "");
    WINDOW *winA, *winB, *winO_for_box, *winO;
    char inA[MAXSTR], inB[MAXSTR];
    int c = 0;
    int half;

    initscr();
    cbreak();
    printw("Input:");
    refresh();

    half = (COLS-2*DX)/2;
    winA = newwin(ONLELINE, half, DX, DX);
    winB = newwin(ONLELINE, half, DX, DX+half);
    winO_for_box = newwin(LINES-ONLELINE-DX*2, (COLS-2*DX), DX+ONLELINE, DX);
    winO = newwin(LINES-ONLELINE-DX*2 - 2, (COLS-2*DX) - 2, DX+ONLELINE + 1, DX + 1);
    keypad(winA, TRUE);
    keypad(winB, TRUE);
    scrollok (winO, TRUE);
    int winO_for_box_drawn = 0;
    do {
        werase(winA); box(winA, 0, 0); wrefresh(winA);
        werase(winB); box(winB, 0, 0); wrefresh(winB);
        mvwgetnstr(winA, 1, 1, inA, MAXSTR);
        mvwgetnstr(winB, 1, 1, inB, MAXSTR);
#ifdef UTF
        struct PcreResult res = processString(inA, inB, 1);
#else
        struct PcreResult res = processString(inA, inB, 0);
#endif
        if (!winO_for_box_drawn) {
            box(winO_for_box, 0, 0);
            wrefresh(winO_for_box);
            winO_for_box_drawn = 1;
        }
        wprintw(winO, "`%s` : `%s`\n", inA, inB);
        wprintw(winO, res.answer);
        free(res.answer);
        wrefresh(winO);
    } while(*inA);

    endwin();

}
