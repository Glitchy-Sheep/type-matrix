#include <iostream>
#include <curses.h>
#include "conf.h"
#include "matrix.h"

#include <vector>


namespace cfg = config;

void init_all_color_pairs();
void init_ncurses_settings(WINDOW *wnd);

int main(int argc, char** argv)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    WINDOW *wnd = initscr();
    init_ncurses_settings(wnd);

    cfg::TM_CONFIG conf = cfg::get_config(argc, argv);
    if (conf.colored_terminal)
    {
        start_color();
        init_all_color_pairs();
    }

    int max_x, max_y;
    getmaxyx(wnd, max_y, max_x);
    Matrix matrix{conf, COLOR_GREEN, max_x, max_y};

    while(true)
    {
        if (wgetch(wnd) == (KEY_RESIZE))
            matrix.handle_terminal_resize(wnd);

        matrix.spawn_line();
        matrix.move_lines();
        refresh();
        _sleep(1000/15);
    }

    return endwin();
}

void init_ncurses_settings(WINDOW *wnd)
{
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