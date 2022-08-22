#pragma once

#include <curses.h>     // getmaxyx and types
#include <cstring>      // strlen
#include <cctype>       // tolower

void get_symbol_spawn_range(WINDOW* wnd, char symbol, int &min_x, int &max_x);