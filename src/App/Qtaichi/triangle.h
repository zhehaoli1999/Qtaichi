#ifndef TRIANGLE_H
#define TRIANGLE_H

#include"polygon.h"

namespace minidraw {
    class Triangle : public Polygon
    {
    public:
        Triangle(QPoint start_point) : Polygon(start_point)
        {}
        ~Triangle() {}
        void draw_dynamic(QPainter& paint, QPoint current_point)
        {
            // convert qreal to int
            end_x = static_cast<int>(current_point.rx());
            end_y = static_cast<int>(current_point.ry());

            QPointF points[3] = {
                QPointF(start_x, start_y), // left_botton_point
                QPointF((start_x + end_x) / 2, end_y), // top_point
                QPointF(end_x, start_y), // right_bottom_point
            };
            paint.drawPolygon(points, 3);
        }

        void draw(QPainter& paint)
        {
            //end_x = static_cast<int>(p_point_array[1].rx()); // no need to re-calculate end_x, end_y here. 
            //end_y = static_cast<int>(p_point_array[1].ry());

            QPointF points[3] = {
                QPointF(start_x, start_y), // left_botton_point
                QPointF((start_x + end_x) / 2, end_y), // top_point
                QPointF(end_x, start_y), // right_bottom_point
            };
            // update p_point_array
            this->p_point_array = QPolygonF(QVector<QPointF>{points[0], points[1], points[2]});
            paint.drawPolygon(points, 3);
        }
    };
};
#endif // TRIANGLE_H
