#include <iostream>
#include <curses.h>
#include "conf.h"
#include "matrix.h"

#include <vector>


namespace cfg = config;

void init_all_color_pairs();

int main(int argc, char** argv)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    WINDOW *wnd = initscr();
    curs_set(0);

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
        matrix.spawn_line();
        matrix.move_lines();
        refresh();
        _sleep(1000/15);
    }

    return endwin();
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