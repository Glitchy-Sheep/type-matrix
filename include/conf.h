#pragma once
#include <argh.h>
#include <curses.h>         // for COLOR_X constants
#include "exit_errors.h"

namespace config
{
    struct TM_CONFIG {          // whole application config
        bool colored_terminal;
        bool rainbow_mode;

        int main_color;         // ncurses colors bit masks
        unsigned int speed;     // speed multiplier
    };

    TM_CONFIG get_config(int argc, char** argv);
    void print_help_msg();
};