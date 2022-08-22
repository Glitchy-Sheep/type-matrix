#include "keyboard_handler.h"

static const char* layout_ascii[] = {
    "qwertyuiop[]",
    "asdfghjkl;'",
    "zxcvbnm,./"
};

static const unsigned int layout_rows_count = sizeof(layout_ascii)
                                                / sizeof(*layout_ascii);


static bool layout_get_row_and_col(char symbol, int &res_row, int &res_col)
{
    char lowercased_symbol = tolower(symbol);

    for (int row = 0; row < layout_rows_count; ++row)
    {
        const char *found_symbol = strchr(layout_ascii[row], lowercased_symbol);
        if (found_symbol)
        {
            res_row = row+1;
            res_col = found_symbol - layout_ascii[row] + 1;
            return true;
        }
    }

    return false;
}

void get_symbol_spawn_range(WINDOW* wnd, char symbol, int &min_x, int &max_x)
{
    int max_term_x, max_term_y;
    getmaxyx(wnd, max_term_y, max_term_x);

    int symbol_row, symbol_col;
    if (layout_get_row_and_col(symbol, symbol_row, symbol_col))
    {
        /*  (example) Terminal and 3 buttons (ABC row) on keyboard:
             ____A_______B________C____
            |........|........|........| = max_term_x = 24 chars (3 by 8)
            |        |        |        | therefore one range size = rows / letters
        */
        int range_size = max_term_x / strlen(layout_ascii[symbol_row-1]);
        min_x = 0 + (range_size * symbol_col - range_size);
        max_x = 0 + (range_size * symbol_col);
    }
    else // symbol is not a-Z - choose the whole range
    {
        min_x = 0;
        max_x = max_term_x;
    }
}