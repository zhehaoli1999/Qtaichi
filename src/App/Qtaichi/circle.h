#ifndef CIRCLE_H
#define CIRCLE_H

#include "ellipse.h"

namespace minidraw {
    class Circle : public Ellipse
    {
    public:
        Circle(QPoint start_point) : Ellipse(start_point)
        {}

        void draw_dynamic(QPainter& paint, QPoint current_point)
        {
            // convert qreal to int
            end_x = static_cast<int>(current_point.rx());

            QRect rectangle(start_x, start_y, end_x - start_x, end_x - start_x);
            paint.drawEllipse(rectangle);
        }

        void draw(QPainter& paint)
        {
            end_x = static_cast<int>(p_point_array[1].rx());

            QRect rectangle(start_x, start_y, end_x - start_x, end_x - start_x);
            paint.drawEllipse(rectangle);
        }
    };
};

#endif // CIRCLE_H
