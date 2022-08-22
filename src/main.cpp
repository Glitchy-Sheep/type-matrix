#include <iostream>
#include <curses.h>
#include <vector>
#include <thread>       // std::this_thread::sleep_for()
#include <chrono>       // std::chrono::milliseconds()

#include "conf.h"
#include "matrix.h"
#include "ncurses_control.h"

namespace cfg = config;

#include "keyboard_handler.h"

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

    Matrix matrix{wnd, conf};

    int event = 0;
    while(true)
    {
        event = wgetch(wnd);
        if (event == KEY_RESIZE)
            matrix.handle_terminal_resize(wnd);
        if (event == KEY_CTRL_('c') || event == KEY_ESCAPE)
        {
            ncurses_cleanup();
            exit(0);
        }

        if (conf.interactive_mode)
        {
            if (event != ERR)
            {
                int min_x, max_x;
                get_symbol_spawn_range(wnd, event, min_x, max_x);
                int spawn_x = get_rand(min_x, max_x);
                int spawn_y = 0;
                matrix.spawn_line(spawn_x, spawn_y);
            }
        }
        else
        {
            int spawn_x = rand() % matrix.get_terminal_max_x();
            int spawn_y = 0;
            matrix.spawn_line(spawn_x, spawn_y);
        }

        matrix.move_lines();
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/conf.fps));
    }

    return endwin();
}