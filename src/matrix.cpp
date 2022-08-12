#include "matrix.h"


//---------------------------------------------//
//     One matrix symbol class realization     //
//---------------------------------------------//

MatrixSymbol::MatrixSymbol(char symbol, int x, int y, int color, int direction)
{
    m_symbol = symbol;
    m_x = x;
    m_y = y;
    m_color = color;
    m_direction = direction;
    m_additional_attribute = 0;
}

void MatrixSymbol::hide() const
{
    mvaddch(m_y, m_x, ' ');
}

void MatrixSymbol::show() const
{
    // [BUG] TODO: Attron doesn't work as expected:
    // Colors change every time you change pairs
    // so we need to change pairs, not colors in a pair.
    // Solution: INIT color pairs when program starts
    // each pair number according to its color number and vise versa

    init_pair(1, m_color, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    mvaddch(m_y, m_x, m_symbol | m_additional_attribute);
    attroff(COLOR_PAIR(1));
}

void MatrixSymbol::move()
{
    int dx, dy;
    switch (m_direction)
    {
    case DIRECTION_UP:
        dx = 0;
        dy = -1;
        break;
    case DIRECTION_DOWN:
        dx = 0;
        dy = 1;
        break;
    case DIRECTION_LEFT:
        dx = -1;
        dy = 0;
        break;
    case DIRECTION_RIGHT:
        dx = 1;
        dy = 0;
    }

    hide();
    m_x += dx;
    m_y += dy;
    show();
}

bool MatrixSymbol::is_beyond_limits(int lim_x, int lim_y) const
{
    return (m_x < 0 || m_y < 0) ||
            (m_x > lim_x || m_y > lim_y);
}

char MatrixSymbol::get_symbol() const
{
    return m_symbol;
}

int MatrixSymbol::get_color() const
{
    return m_color;
}

void MatrixSymbol::get_position(int &x, int &y) const
{
    x = m_x;
    y = m_y;
}

int MatrixSymbol::get_direction() const
{
    return m_direction;
}

void MatrixSymbol::set_symbol(char new_symbol)
{
    m_symbol = new_symbol;
}

void MatrixSymbol::set_direction(int new_direction)
{
    m_direction = new_direction;
}

void MatrixSymbol::set_additional_attribute(chtype new_attribute)
{
    m_additional_attribute = new_attribute;
}

void MatrixSymbol::set_color(int new_color)
{
    m_color = new_color;
}


//--------------------------------------------//
//     One matrix line class realization      //
//--------------------------------------------//

MatrixLine::MatrixLine(char init_head, int x, int y, int color, int direction)
    : m_head{init_head, x, y, color, direction}, m_tail{}
{
    m_tail_max_length = 0;
    m_direction = direction;

    m_head.set_additional_attribute(A_BOLD);
}

void MatrixLine::show() const
{
    m_head.show();
    for (auto &symbol : m_tail)
        symbol.show();
}

void MatrixLine::hide() const
{
    m_head.hide();
    for (auto &symbol : m_tail)
        symbol.hide();
}

void MatrixLine::move()
{
    m_tail.push_front(MatrixSymbol{m_head});
    m_tail.front().set_additional_attribute(A_NORMAL);

    if (m_tail.size() > m_tail_max_length)
    {
        m_tail.back().hide();
        m_tail.pop_back();
    }

    m_head.set_symbol(char('A' + rand() % 26));
    m_head.move();

    for (auto &symbol : m_tail)
        symbol.show();
}

void MatrixLine::set_tail_max_length(unsigned int new_max_length)
{
    if (new_max_length < 0)
        new_max_length = 0;
    m_tail_max_length = new_max_length;
}

void MatrixLine::set_direction(int new_direction)
{
    m_direction = new_direction;
    for (auto &symbol : m_tail)
        symbol.set_direction(new_direction);
}