#include "figure.h"
using namespace minidraw;
Figure::~Figure()
{
}

Figure::Figure()
{
}

Figure::Figure(QPoint start_point)
{
    p_point_array << start_point;
    start_x = static_cast<int>(p_point_array[0].rx());
    start_y = static_cast<int>(p_point_array[0].ry());
}

void Figure::set_color(QColor color)
{
    this->line_color = color;
}

void Figure::set_width(int width)
{
    this->line_width = width;
}

QColor Figure::get_color()
{
    return this->line_color;
}

int Figure::get_width()
{
    return this->line_width;
}

void Figure::add_point(QPoint new_point)
{
    p_point_array << new_point;
}

void Figure::draw_dynamic(QPainter & painter, QPoint)
{
    painter.drawPolyline(p_point_array);
}

void Figure::draw(QPainter & painter)
{
    painter.drawPolyline(p_point_array);
}

// return the vector of the line of the first two points
QPointF Figure::get_line_vector()
{
    return p_point_array[1] - p_point_array[0];
}
