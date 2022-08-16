#pragma once
#include <curses.h>
#include <list>

#include "conf.h"

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
    chtype m_additional_attribute; // A_BOLD, A_BLINK, etc...
public:
    MatrixSymbol(char symbol, int x, int y, int color,
                            int direction = DIRECTION_DOWN);
    void move();
    void show() const;
    void hide() const;

    char get_symbol() const;
    int  get_color() const;
    int  get_direction() const;
    void get_position(int &x, int &y) const;
    bool is_beyond_limits(int lim_x, int lim_y) const;

    void set_color(int new_color);
    void set_symbol(char new_symbol);
    void set_direction(int new_direction);
    void set_additional_attribute(chtype new_attribute);
};



class MatrixLine {
    MatrixSymbol m_head;
    std::list<MatrixSymbol> m_tail;
    unsigned int m_tail_max_length;
    int m_direction;
public:
    MatrixLine(char init_head, int x, int y, int color,
                            int direction = DIRECTION_DOWN);
    void show() const;
    void hide() const;

    void move();
    bool is_beyond_limits(int lim_x, int lim_y) const;

    void set_tail_max_length(unsigned int new_max_length);
    void set_direction(int new_direction);
};


class Matrix {
    std::list<MatrixLine *> m_lines;
    config::TM_CONFIG m_main_cfg;
    int m_term_max_x, m_term_max_y;
    int m_lines_max_length = 8;     // TODO generate 0-8 length each time
    int m_lines_color;
public:
    Matrix(WINDOW *wnd, config::TM_CONFIG cfg);

    void spawn_line();
    void move_lines();

    void handle_terminal_resize(WINDOW *wnd);

    ~Matrix();
};