#ifndef LINE_H
#define LINE_H

#include<qpainter.h>
#include<QColor>
#include"figure.h"

namespace minidraw {
    class Line : public Figure
    {
    public:
        Line(QPoint start_point): Figure(start_point)
        {}

        ~Line(void)
        {

        }
        void draw_dynamic(QPainter &paint, QPoint current_point)
        {
            paint.drawLine(p_point_array[0], current_point);
        }
        void draw(QPainter &paint)
        {
            if(p_point_array.size() > 1)
                paint.drawPolyline(p_point_array);
            else
                paint.drawPoint(p_point_array[0]);
        }

    };
};

#endif // LINE_H
