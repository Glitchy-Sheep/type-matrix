#include <iostream>
#include <curses.h>
#include "conf.h"

namespace cfg = config;

int main(int argc, char** argv)
{
    WINDOW *wnd = initscr();

    cfg::TM_CONFIG conf = cfg::get_config(argc, argv);

    // Config test
    std::cout << "CONFIG:\n";
    std::cout << "--------------------\n";
    std::cout << "colored: \t" << conf.colored_terminal << std::endl;
    std::cout << "main color: \t" << conf.main_color << std::endl;
    std::cout << "rainbow: \t" << conf.rainbow_mode << std::endl;
    std::cout << "speed: \t\t" << conf.speed << std::endl;

    return endwin();
}