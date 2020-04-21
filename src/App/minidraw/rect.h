#ifndef RECT_H
#define RECT_H

#include"polygon.h"

namespace minidraw {
    class Rect : public Polygon
    {
    public:
        Rect(QPoint start_point) : Polygon(start_point)
        {}

        ~Rect() {}
        void draw_dynamic(QPainter& paint, QPoint current_point)
        {
            // convert qreal to int
            end_x = static_cast<int>(current_point.rx());
            end_y = static_cast<int>(current_point.ry());
            paint.drawRect(start_x, start_y, end_x - start_x, end_y - start_y);
        }

        void draw(QPainter& paint)
        {
            end_x = static_cast<int>(p_point_array[1].rx());
            end_y = static_cast<int>(p_point_array[1].ry());

            paint.drawRect(start_x, start_y, end_x - start_x, end_y - start_y);
        }
    };
};
#endif // RECT_H
