#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "figure.h"

namespace minidraw {
    class Ellipse : public Figure
    {
    public:
        Ellipse(QPoint start_point) : Figure(start_point)
        {}
        ~Ellipse() {}
        void draw_dynamic(QPainter& paint, QPoint current_point)
        {
            // convert qreal to int
            end_x = static_cast<int>(current_point.rx());
            end_y = static_cast<int>(current_point.ry());
            QRect rectangle(start_x, start_y, end_x - start_x, end_y - start_y);
            paint.drawEllipse(rectangle);
        }

        void draw(QPainter& paint)
        {
            end_x = static_cast<int>(p_point_array[1].rx());
            end_y = static_cast<int>(p_point_array[1].ry());

            QRect rectangle(start_x, start_y, end_x - start_x, end_y - start_y);
            paint.drawEllipse(rectangle);
        }
    };

};
#endif // ELLIPSE_H
