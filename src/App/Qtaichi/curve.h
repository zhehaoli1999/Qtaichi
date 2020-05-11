#ifndef CURVE_H
#define CURVE_H

#include "figure.h"
namespace minidraw {
    class Curve : public Figure
    {
    public:
        Curve(QPoint start_point) : Figure(start_point)
        {}
        ~Curve()
        {
        }
        void draw_dynamic(QPainter& paint, QPoint current_point)
        {
            p_point_array << current_point;
            if (p_point_array.size() > 1) paint.drawPolyline(p_point_array);
            // only one point: without moving cursor, just click
            else paint.drawPoints(p_point_array);
        }
        void draw(QPainter& paint)
        {
            if (p_point_array.size() > 1) paint.drawPolyline(p_point_array);
            // only one point: without moving cursor, just click
            else paint.drawPoints(p_point_array);
        }

    };

};

#endif // CURVE_H
