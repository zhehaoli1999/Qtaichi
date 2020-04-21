#ifndef FIGURE_H
#define FIGURE_H

#include<QPainter>
#include<QColor>

namespace minidraw {
    class Figure
    {
    public:
        Figure(void);
        Figure(QPoint start_point);
        virtual ~Figure(void);

        virtual void draw_dynamic(QPainter& paint, QPoint current_point);
        virtual void draw(QPainter& paint);
        void add_point(QPoint new_point);

        void set_color(QColor color);
        void set_width(int width);
        QColor get_color(void);
        int get_width(void);

        // return the vector of the line when p_point_array.size() == 2
        QPointF get_line_vector();
       
        //int get_point_array_size(void);

    public:
        QPolygonF p_point_array;

    protected:
        int line_width;
        QColor line_color;
        int start_x, start_y, end_x, end_y;
    };

};
#endif // FIGURE_H
