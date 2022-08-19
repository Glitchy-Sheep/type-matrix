#pragma once
#include <curses.h>
#include "helpers.h"

// for ctrl-chr combination detection with getch()
#define KEY_CTRL_(chr) ((chr) & 037)

void init_all_color_pairs();
void init_ncurses_settings(WINDOW *wnd);
void ncurses_cleanup();
int get_random_ncurses_color();