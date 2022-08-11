#include <iostream>
#include <curses.h>
#include "conf.h"
#include "matrix.h"


namespace cfg = config;


int main(int argc, char** argv)
{
    WINDOW *wnd = initscr();

    cfg::TM_CONFIG conf = cfg::get_config(argc, argv);
    if (conf.colored_terminal)
        start_color();


    // Temp test
    std::vector<MatrixSymbol> symbols;
    int max_x, max_y;
    getmaxyx(wnd, max_y, max_x);

    for (int i = 0; i < max_x; i++)
    {
        symbols.push_back(
            MatrixSymbol{'A', i, 0, COLOR_RED, DIRECTION_DOWN}
        );
        if (i % 2 == 0)
            symbols[i].set_additional_attribute(A_BOLD | A_UNDERLINE);
    }

    for (int x = 0; x < max_y; ++x)
    {
        for (int i = 0; i < max_x; ++i)
            symbols[i].move();
        refresh();
        _sleep(1000 / 10);
    }

    return endwin();
}