#include <iostream>
#include <curses.h>
#include "conf.h"
#include "matrix.h"

#include <vector>


namespace cfg = config;

void init_all_color_pairs();

int main(int argc, char** argv)
{
    WINDOW *wnd = initscr();
    curs_set(0);

    cfg::TM_CONFIG conf = cfg::get_config(argc, argv);
    if (conf.colored_terminal)
    {
        start_color();
        init_all_color_pairs();
    }

    // Temp test of all the matrix (with fixed color changing)
    srand(static_cast<unsigned int>(time(nullptr)));
    std::vector<MatrixLine> lines;

    int max_x, max_y;
    getmaxyx(wnd, max_y, max_x);
    for (int n_lines = 0; n_lines < max_x; ++n_lines)
    {
        lines.push_back(
            MatrixLine{'A', n_lines, 0, rand()%8, DIRECTION_DOWN}
        );
        lines[n_lines].set_tail_max_length(max_y);
    }

    for (int n_rows = 0; n_rows < max_y; ++n_rows)
    {
        for (int n_lines = 0; n_lines < max_x; ++n_lines)
            lines[n_lines].move();
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