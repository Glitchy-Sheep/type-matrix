#include <iostream>
#include <curses.h>
#include "conf.h"
#include "matrix.h"

#include <vector>


namespace cfg = config;


int main(int argc, char** argv)
{
    WINDOW *wnd = initscr();
    curs_set(0);

    cfg::TM_CONFIG conf = cfg::get_config(argc, argv);
    if (conf.colored_terminal)
        start_color();

    // Temp test of all the matrix
    std::vector<MatrixLine> lines;

    int max_x, max_y;
    getmaxyx(wnd, max_y, max_x);
    for (int n_lines = 0; n_lines < max_x; ++n_lines)
    {
        lines.push_back(
            MatrixLine{'A', n_lines, 0, COLOR_MAGENTA, DIRECTION_DOWN}
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