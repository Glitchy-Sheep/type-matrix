#include "matrix.h"

MatrixSymbol::MatrixSymbol(char symbol, int x, int y, int color, int direction)
{
    m_symbol = symbol;
    m_x = x;
    m_y = y;
    m_color = color;
    m_direction = direction;
    m_additional_attribute = 0;
}

void MatrixSymbol::hide()
{
    mvaddch(m_y, m_x, ' ');
}

void MatrixSymbol::show()
{
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

bool MatrixSymbol::is_beyond_limits(int lim_x, int lim_y)
{
    return (m_x < 0 || m_y < 0) ||
            (m_x > lim_x || m_y > lim_y);
}

void MatrixSymbol::set_additional_attribute(int mask)
{
    m_additional_attribute = mask;
}