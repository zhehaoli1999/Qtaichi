#ifndef POLYGON_H
#define POLYGON_H

#include"figure.h"

namespace minidraw {
    class Polygon : public Figure
    {
    public:
        Polygon(QPoint start_point) : Figure(start_point)
        {}
        ~Polygon()
        {
        }
        void draw(QPainter& paint)
        {
            if (p_point_array.size() > 1)
                paint.drawPolygon(p_point_array);
            else
                paint.drawPoints(p_point_array);
        }
        void draw_dynamic(QPainter& paint, QPoint current_point)
        {
            QPolygonF p_temp_point_array = p_point_array;
            p_temp_point_array << current_point;
            if (p_temp_point_array.size() > 1)
                paint.drawPolyline(p_temp_point_array);
            if (p_temp_point_array.size() == 1)
                paint.drawPoint(p_temp_point_array[0]);
        }
    };
};
#endif // POLYGON_H
