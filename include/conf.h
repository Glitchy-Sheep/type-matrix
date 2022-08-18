#pragma once
#include <string>
#include <argh.h>
#include <curses.h>         // for COLOR_X constants
#include "exit_errors.h"
#include "ncurses_control.h"

namespace config
{
    struct TM_CONFIG {          // whole application config
        bool colored_terminal;
        bool rainbow_mode;

        int main_color;                         // ncurses colors bit masks
        unsigned int fps;                       // matrix update frame rate
        unsigned int max_line_length;
        unsigned int min_line_length_deviation;
        std::string alphabet;                   // for random symbol generation
    };

    TM_CONFIG get_config(int argc, char** argv);
    void print_help_msg(argh::parser &cmdl);
};