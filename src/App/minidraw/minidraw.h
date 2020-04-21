#ifndef MINIDRAW_H
#define MINIDRAW_H

#include <QMainWindow>
#include "minidraw_controller.h"
#include <QPushButton>
#include <QToolButton>
using namespace minidraw;
namespace Ui {
class Minidraw;
}

class Minidraw : public QMainWindow
{
    Q_OBJECT

public:
    explicit Minidraw(QWidget *parent = nullptr);
    ~Minidraw();

    void create_toolbar();
    void create_figure_toolbar();
    void create_simulation_toolbar();
    void create_snow_type_toolbar();

signals:
    void valueChanged(int value);

public slots:
    void set_line_width(int width);
    void set_line_color_red(void);
    void set_line_color_black(void);
    void set_line_color_yellow(void);
    void set_line_color_blue(void);
    void set_line_color_green(void);
    void set_line_color_white(void);
    void set_line_color_orange(void);

    void set_figure_tool_line(void);
    void set_figure_tool_rect(void);
    void set_figure_tool_circle(void);
    void set_figure_tool_ellipse(void);
    void set_figure_tool_curve(void);
    void set_figure_tool_tri(void);
    void set_figure_tool_poly(void);

    void set_snow_type_1();
    void set_snow_type_2();
    void set_snow_type_3();
    void set_snow_type_4();
    void set_snow_type_5();
    void set_snow_type_6();

    void start_simulation(void);
    void pause_simulation(void);
    void reset_simulation(void);
    void clear_simulation(void);

    void undo();
    void clear();

private:
    Ui::Minidraw *ui;
    Minidraw_controller *controller;
    QMenu* menu;
    QToolBar* slider_toolbar;
    QToolBar* color_toolbar;
    QToolBar* figure_toolbar;
    QToolBar* Simulation_toolbar;
    QToolBar* SnowType_toolbar;

    QSlider* slider_line_width;
    QToolButton *button_red;
    QToolButton *button_black;
    QToolButton *button_blue;
    QToolButton *button_yellow;
    QToolButton *button_green;
    QToolButton* button_white;
    QToolButton* button_orange;

    QAction * choose_line_act;
    QAction * choose_curve_act;
    QAction * choose_circle_act;
    QAction * choose_ellipse_act;
    QAction * choose_rect_act;
    QAction * choose_tri_act;
    QAction * choose_poly_act;

    QAction* choose_snow_type[6]; // for snow type choosing in paper MFM Fig 8.

    QAction* action_undo;
    QAction* action_clear;

    QAction* action_simulate;
    QAction* action_pause_simul;
    QAction* action_reset_simul;
    QAction* action_clear_simul;
};

#endif // MINIDRAW_H
