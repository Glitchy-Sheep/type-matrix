#include "ncurses_control.h"

void init_ncurses_settings(WINDOW *wnd)
{
    cbreak();
    timeout(0);     // getch will check events without blocking
    noecho();
    curs_set(0);    // Remove nasty cursor
    keypad(wnd, 1); // Ensures that getch() will return KEY_RESIZE
}

void init_all_color_pairs()
{
    init_pair(COLOR_BLACK,   COLOR_BLACK,   COLOR_BLACK);
    init_pair(COLOR_BLUE,    COLOR_BLUE,    COLOR_BLACK);
    init_pair(COLOR_CYAN,    COLOR_CYAN,    COLOR_BLACK);
    init_pair(COLOR_GREEN,   COLOR_GREEN,   COLOR_BLACK);
    init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(COLOR_RED,     COLOR_RED,     COLOR_BLACK);
    init_pair(COLOR_WHITE,   COLOR_WHITE,   COLOR_BLACK);
    init_pair(COLOR_YELLOW,  COLOR_YELLOW,  COLOR_BLACK);
}

void ncurses_cleanup()
{
    curs_set(1);
    clear();
    refresh();
    resetty();
    endwin();
}