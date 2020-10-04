#include <ncurses.h>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

#define MIN(a, b) (((a)<(b))?(a):(b))

#define MAX(a, b) (((a)>(b))?(a):(b))

struct FileState {
    FILE *f;
    fpos_t *line_start_positions;
    int *line_lengths;
    int total_lines;
    int lines_capacity;
    int linenumber_digits;
};

struct ScreenInfo {
    WINDOW *win;
    int total_lines;
    int total_cols;
    int cur_top_fileline;
    int cur_left_filecursor;
};

struct FileState* open_file(const char* filename) {
    struct FileState* file_info = malloc(sizeof(*file_info));
    file_info->f = fopen(filename, "r");
    fwide(file_info->f, 1);

    file_info->lines_capacity = 1;
    file_info->total_lines = 0;
    file_info->line_start_positions = malloc(file_info->lines_capacity * sizeof(*file_info->line_start_positions));
    file_info->line_lengths = malloc(file_info->lines_capacity * sizeof(*file_info->line_lengths));

    wint_t cur_char = 0;
    do {
        if (file_info->total_lines == file_info->lines_capacity) {
            file_info->lines_capacity <<= 1;
            file_info->line_start_positions = realloc(file_info->line_start_positions,
                                                      file_info->lines_capacity * sizeof(*file_info->line_start_positions));
            file_info->line_lengths = realloc(file_info->line_lengths,
                                              file_info->lines_capacity * sizeof(*file_info->line_lengths));
        }
        fgetpos(file_info->f, &file_info->line_start_positions[file_info->total_lines]);
        int cur_len = 0;
        do {
            cur_char = fgetwc(file_info->f);
            ++cur_len;
        } while (cur_char != '\n' && cur_char != WEOF);
        --cur_len;
        file_info->line_lengths[file_info->total_lines] = cur_len;
        ++file_info->total_lines;
    } while (cur_char != WEOF);

    file_info->linenumber_digits = 0;
    int cur = file_info->total_lines;
    do {
        cur /= 10;
        ++file_info->linenumber_digits;
    } while (cur > 0);
    return file_info;
}

void close_file(struct FileState* file_info) {
    fclose(file_info->f);
    free(file_info->line_start_positions);
    free(file_info->line_lengths);
    free(file_info);
}

struct ScreenInfo* init_screen(int padding, int linenumber_digits) {
    struct ScreenInfo* screen = malloc(sizeof(*screen));
    screen->win = newwin(LINES - 2 * padding, COLS - 2 * padding, padding, padding);
    getmaxyx(screen->win, screen->total_lines, screen->total_cols);
    screen->total_lines -= 2;
    screen->total_cols -= 2 + linenumber_digits + 2;
    screen->cur_top_fileline = 0;
    screen->cur_left_filecursor = 0;
    keypad(screen->win, TRUE);
    scrollok(screen->win, TRUE);
    return screen;
}

void close_screen(struct ScreenInfo* screen) {
    free(screen);
}

void print_file_screen(struct ScreenInfo* screen, struct FileState* file_info) {
    wchar_t *cur_line = malloc((screen->total_cols + 1) * sizeof(*cur_line));
    for (int i = 0; i < MIN(file_info->total_lines - screen->cur_top_fileline, screen->total_lines); ++i) {
        if (screen->cur_left_filecursor >= file_info->line_lengths[screen->cur_top_fileline + i]) {
            mvwprintw(screen->win, i + 1, 1, "%*d:",
                      file_info->linenumber_digits, screen->cur_top_fileline + i + 1);
            continue;
        }
        fsetpos(file_info->f, &file_info->line_start_positions[screen->cur_top_fileline + i]);
        int cur_pos = 0;
        while (cur_pos < screen->cur_left_filecursor) {
            fgetwc(file_info->f);
            ++cur_pos;
        }
        fgetws(cur_line, screen->total_cols + 1, file_info->f);
        mvwprintw(screen->win, i + 1, 1, "%*d: %S",
                  file_info->linenumber_digits, screen->cur_top_fileline + i + 1,
                  cur_line);
    }
    mvwprintw(screen->win, 0, 0, "");
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");
    if (argc != 2) {
        wprintf(L"Неправильное число аргументов командной строки!\n");
        return 1;
    }
    struct FileState* file_info = open_file(argv[1]);
    initscr();
    noecho();
    cbreak();
    set_escdelay(0);
    struct ScreenInfo* screen = init_screen(3, file_info->linenumber_digits);
    WINDOW *info_win = newwin(1, COLS, 0, 0);

    wchar_t c = 0;
    refresh();
    while (c != 27) {
        werase(info_win);
        mvwprintw(info_win, 0, 0, "File: %s; size: %d; cursor: %d:%d",
                  argv[1],
                  file_info->total_lines,
                  screen->cur_top_fileline + 1,
                  screen->cur_left_filecursor + 1);
        wrefresh(info_win);

        werase(screen->win);
        print_file_screen(screen, file_info);
        box(screen->win, 0, 0);
        wrefresh(screen->win);

        c = wgetch(screen->win);
        switch(c) {
            case KEY_UP:
                screen->cur_top_fileline = MAX(screen->cur_top_fileline - 1, 0);
                break;
            case ' ':
            case KEY_DOWN:
                screen->cur_top_fileline = MIN(screen->cur_top_fileline + 1,
                                               file_info->total_lines - 1);
                break;
            case KEY_PPAGE:
                screen->cur_top_fileline = MAX(screen->cur_top_fileline - screen->total_lines, 0);
                break;
            case KEY_NPAGE:
                screen->cur_top_fileline = MIN(screen->cur_top_fileline + screen->total_lines,
                                               file_info->total_lines - 1);
                break;
            case KEY_RIGHT:
            {
                int max_length = 1;
                for (int i = 0; i < MIN(file_info->total_lines - screen->cur_top_fileline, screen->total_lines); ++i) {
                    max_length = MAX(max_length,
                                     file_info->line_lengths[screen->cur_top_fileline + i]);
                }
                screen->cur_left_filecursor = MIN(screen->cur_left_filecursor + 1, max_length - 1);
            }
                break;
            case KEY_LEFT:
                screen->cur_left_filecursor = MAX(screen->cur_left_filecursor - 1, 0);
                break;
        }
    }

    close_screen(screen);
    close_file(file_info);
    endwin();
    return 0;
}
