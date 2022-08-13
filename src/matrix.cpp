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
    attron(COLOR_PAIR(m_color));
    mvaddch(m_y, m_x, m_symbol | m_additional_attribute);
    attroff(COLOR_PAIR(m_color));
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

    if (m_tail.size() > m_tail_max_length && m_tail.size() != 0)
    {
        m_tail.back().hide();
        m_tail.pop_back();
    }

    m_head.set_symbol(char('A' + rand() % 26));
    m_head.move();

    for (auto &symbol : m_tail)
        symbol.show();
}

bool MatrixLine::is_beyond_limits(int lim_x, int lim_y) const
{
    // A whole line is beyond terminal limits
    // only when the last symbol of the line is hidden
    // it's either last tail element or (if tail is empty) head
    if (m_tail.size() == 0)
        return m_head.is_beyond_limits(lim_x, lim_y);
    else
        return m_tail.back().is_beyond_limits(lim_x, lim_y);

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


//-------------------------------------------//
//       One matrix class realization        //
//-------------------------------------------//

Matrix::Matrix(config::TM_CONFIG cfg, int color, int max_x, int max_y)
    : m_main_cfg{cfg}, m_term_max_x{max_x}, m_term_max_y{max_y},
        m_lines_color{color}
{
}

Matrix::~Matrix()
{
    for (MatrixLine *line : m_lines)
        delete(line);
}

void Matrix::move_lines()
{
    std::list<MatrixLine *> for_removal;

    for (MatrixLine *line : m_lines)
    {
        if (!line) // should not ever happen
            continue;

        line->move();
        if (line->is_beyond_limits(m_term_max_x, m_term_max_y))
            for_removal.push_back(line);
    }

    // Remove trash only when all the lines are processed
    // so you don't have access memory violation
    for (MatrixLine *line : for_removal)
    {
        m_lines.remove(line);
        delete line;
    }
}

void Matrix::spawn_line()
{

    int rand_x = rand() % m_term_max_x;
    int rand_y = 0;

    MatrixLine *new_line =
            new MatrixLine{'a', rand_x, rand_y, m_lines_color, DIRECTION_DOWN};

    new_line->set_tail_max_length(m_lines_max_length);

    m_lines.push_back(new_line);
}