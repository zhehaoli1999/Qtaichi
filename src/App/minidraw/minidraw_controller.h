#ifndef MINIDRAW_CONTROLLER_H
#define MINIDRAW_CONTROLLER_H

#include <QWidget>
#include <QVector>
#include "line.h"
#include <QColor>
#include <QSlider>

using namespace minidraw;

namespace Ui {
class Minidraw_controller;
}

enum FigureType
{
    k_line = 0,
    k_curve = 1,
    k_rect = 2,
    k_triangle = 3,
    k_circle = 4,
    k_ellipse = 5,
    k_polygon = 6,
};

class Minidraw_controller : public QWidget
{
    Q_OBJECT

public:
    explicit Minidraw_controller(QWidget *parent = nullptr);
    ~Minidraw_controller();

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    void paintEvent(QPaintEvent *event);
    
    void undo();
    void clearFigure();

    void simulate();
    void add_objects();
    void clear_simulation();
    void reset_simulation();
    void set_snow_type(int);

    // To make Minidraw able to change the width and color of line through slider and button.
    friend class Minidraw;

private:
    Ui::Minidraw_controller *ui;

    bool draw_status;
    QPoint current_point;

    QColor current_line_color;
    int current_line_width;
    FigureType current_figure_type;

    QVector<Figure*> figure_array;
    QVector<Figure*> figure_array_backup;

    Figure* p_current_figure;

    bool is_drawing_ploygon;
    bool is_simulating; 
};

#endif // MINIDRAW_CONTROLLER_H
