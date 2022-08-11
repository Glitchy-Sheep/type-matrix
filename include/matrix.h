#pragma once
#include <curses.h>
#include <vector>

enum
{
    DIRECTION_UP,
    DIRECTION_DOWN,
    DIRECTION_LEFT,
    DIRECTION_RIGHT
};



class MatrixSymbol {
    char m_symbol;
    int m_color;
    int m_x, m_y;
    int m_direction;
    int m_additional_attribute; // A_BOLD, A_BLINK, etc...
public:
    MatrixSymbol(char symbol, int x, int y, int color,
                    int direction = DIRECTION_DOWN);
    void move();
    void show();
    void hide();

    bool is_beyond_limits(int lim_x, int lim_y);
    void set_additional_attribute(int mask);
};