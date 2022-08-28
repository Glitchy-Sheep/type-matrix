#include <iostream>
#include <curses.h>
#include <vector>
#include <thread>       // std::this_thread::sleep_for()
#include <chrono>       // std::chrono::milliseconds()

#include "conf.h"
#include "matrix.h"
#include "ncurses_control.h"
#include "keyboard_handler.h"

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

    Matrix matrix{wnd, conf};

    int key_event = 0;
    while(true)
    {
        key_event = wgetch(wnd);
        if (key_event == KEY_RESIZE)
            matrix.handle_terminal_resize(wnd);

        if (key_event == KEY_CTRL_('c') || key_event == KEY_ESCAPE)
        {
            ncurses_cleanup();
            exit(0);
        }

        if (key_event != ERR && conf.screensaver_mode)
        {
            ncurses_cleanup();
            exit(0);
        }

        matrix.spawn_lines(wnd, key_event);
        matrix.move_lines();
        matrix.print_user_message();
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/conf.fps));
    }

    return endwin();
}