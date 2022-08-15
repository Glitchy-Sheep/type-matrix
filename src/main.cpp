#include <iostream>
#include <curses.h>
#include <vector>
#include <thread>       // std::this_thread::sleep_for()
#include <chrono>       // std::chrono::milliseconds()

#include "conf.h"
#include "matrix.h"
#include "ncurses_control.h"

namespace cfg = config;

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
    Matrix matrix{conf, conf.main_color, max_x, max_y};

    int event = 0;
    while(true)
    {
        event = wgetch(wnd);
        if (event == KEY_RESIZE)
            matrix.handle_terminal_resize(wnd);
        if (event == KEY_CTRL_('c'))
        {
            ncurses_cleanup();
            exit(0);
        }

        matrix.spawn_line();
        matrix.move_lines();
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/conf.fps));
    }

    return endwin();
}