#include "minidraw.h"
#include "ui_minidraw.h"

#include<QToolButton>

void Minidraw::set_line_width(int width)
{
    controller -> current_line_width = width;
}

void Minidraw::set_line_color_red(void)
{
    controller -> current_line_color = Qt::red;
    controller-> current_figure_type = k_line; // also set figure type be line
}
void Minidraw::set_line_color_blue(void)
{
    controller->current_line_color = QColor(0x87CEFA);
    //controller -> current_line_color = Qt::blue;
}
void Minidraw::set_line_color_green(void)
{
    controller -> current_line_color = Qt::green;
}
void Minidraw::set_line_color_orange(void)
{
    controller->current_line_color = QColor(0xED553B);
}
void Minidraw::set_line_color_black(void)
{
    controller -> current_line_color = Qt::black;
}
void Minidraw::set_line_color_yellow(void)
{
    controller -> current_line_color = Qt::yellow;
}

void Minidraw::set_line_color_white(void)
{
    controller->current_line_color = Qt::white;
}

void Minidraw::set_figure_tool_line(void)
{
    controller -> current_figure_type = k_line;
}

void Minidraw::set_figure_tool_rect(void)
{
    controller -> current_figure_type = k_rect;
}

void Minidraw::set_figure_tool_circle(void)
{
    controller -> current_figure_type = k_circle;
}

void Minidraw::set_figure_tool_curve(void)
{
    controller -> current_figure_type = k_curve;
}

void Minidraw::set_figure_tool_ellipse(void)
{
    controller -> current_figure_type = k_ellipse;
}

void Minidraw::set_figure_tool_tri(void)
{
    controller -> current_figure_type = k_triangle;
}

void Minidraw::set_figure_tool_poly(void)
{
    controller -> current_figure_type = k_polygon;
}

void Minidraw::create_figure_toolbar()
{
    figure_toolbar = addToolBar(tr("Figure Tools"));
    // button for line
    choose_line_act = new QAction( QIcon(":/resources/line_icon.png"), tr("line tool"),this);
    connect(choose_line_act, &QAction::triggered, this, &Minidraw::set_figure_tool_line);
    figure_toolbar->addAction(choose_line_act);

    // button for curve
    choose_curve_act = new QAction( QIcon(":/resources/curve_icon.png"), tr("curve tool"),this);
    connect(choose_curve_act, &QAction::triggered, this, &Minidraw::set_figure_tool_curve);
    figure_toolbar->addAction(choose_curve_act);

    // button for circle
    choose_circle_act = new QAction( QIcon(":/resources/circle_icon.png"), tr("circle tool"),this);
    connect(choose_circle_act, &QAction::triggered, this, &Minidraw::set_figure_tool_circle);
    figure_toolbar->addAction(choose_circle_act);

    // button for ellipse
    choose_ellipse_act = new QAction(QIcon(":/resources/ellipse_icon.png"), tr("ellipse tool"),this);
    connect(choose_ellipse_act, &QAction::triggered, this, &Minidraw::set_figure_tool_ellipse);
    figure_toolbar->addAction(choose_ellipse_act);

    // button for rect
    QAction * choose_rect_act = new QAction( QIcon(":/resources/rect_icon.png"), tr("rect tool"),this);
    connect(choose_rect_act, &QAction::triggered, this, &Minidraw::set_figure_tool_rect);
    figure_toolbar->addAction(choose_rect_act);

    // button for triangle
    QAction * choose_tri_act = new QAction(QIcon(":/resources/tri_icon.png"), tr("tri tool"),this);
    connect(choose_tri_act, &QAction::triggered, this, &Minidraw::set_figure_tool_tri);
    // figure_toolbar->addAction(choose_tri_act);  // triangle simulation has bug now 

    // button for polygon
    choose_poly_act = new QAction(QIcon(":/resources/polygon_icon.png"), tr("poly tool"),this);
    connect(choose_poly_act, &QAction::triggered, this, &Minidraw::set_figure_tool_poly);
    figure_toolbar->addAction(choose_poly_act);

    // button for undo
    action_undo = new QAction(QIcon(":/resources/undo.png"), tr("undo"), this);
    connect(action_undo, &QAction::triggered, this, &Minidraw::undo);
    figure_toolbar->addAction(action_undo);

    // button for clear
    action_clear = new QAction(QIcon(":/resources/clear.jpg"), tr("clear"), this);
    connect(action_clear, &QAction::triggered, this, &Minidraw::clear);
    figure_toolbar->addAction(action_clear);
}
void Minidraw::undo()
{
    controller->undo();
}

void Minidraw::clear()
{
    controller->clearFigure();
}

void Minidraw::create_toolbar()
{
    slider_toolbar = addToolBar(tr("slider toolbar"));
    color_toolbar = addToolBar(tr("color toolbar"));

    // create slider for line width
    slider_line_width = new QSlider(Qt::Horizontal);
    slider_line_width->setRange(1,20); // set line width range be 1-20
    slider_line_width->setSingleStep(1);  // set line width change step be 1
    slider_line_width->setStatusTip(tr("线宽"));

    // connect slider value change with function set_line_width
    connect(slider_line_width,  SIGNAL(valueChanged(int)), this, SLOT(set_line_width(int)) );
    slider_toolbar -> addWidget(slider_line_width);

    // create button for color
    button_black = new QToolButton();
    button_black -> setIcon(QIcon(":/resources/solid.png")); // black --> stone
    color_toolbar -> addWidget(button_black);
    connect(button_black,  SIGNAL (released()), this, SLOT(set_line_color_black(void)) );

    button_white = new QToolButton();
    button_white -> setIcon(QIcon(":/resources/snow.png"));
    color_toolbar -> addWidget(button_white);
    connect(button_white,  SIGNAL (released()), this, SLOT(set_line_color_white(void)) );

    button_blue = new QToolButton();
    button_blue -> setIcon(QIcon(":/resources/fluid.png"));
    color_toolbar -> addWidget(button_blue);
    connect(button_blue,  SIGNAL (released()), this, SLOT(set_line_color_blue(void)) );

    button_yellow = new QToolButton();
    button_yellow -> setIcon(QIcon(":/resources/yellow.png"));
   // color_toolbar -> addWidget(button_yellow);
    //connect(button_yellow,  SIGNAL (released()), this, SLOT(set_line_color_yellow(void)) );

    button_orange = new QToolButton();
    button_orange -> setIcon(QIcon(":/resources/jelly.png"));
    color_toolbar -> addWidget(button_orange);
    connect(button_orange,  SIGNAL (released()), this, SLOT(set_line_color_orange(void)) );

    button_red = new QToolButton();
    button_red->setIcon(QIcon(":/resources/velocity.png"));
    color_toolbar->addWidget(button_red);
    connect(button_red, SIGNAL(released()), this, SLOT(set_line_color_red(void)));
}

void Minidraw::create_simulation_toolbar()
{
    Simulation_toolbar = addToolBar(tr("simulation toolbar"));
    action_simulate = new QAction(QIcon(":/resources/simulate.jpg"), tr("start simulation"), this);
    connect(action_simulate, &QAction::triggered, this, &Minidraw::start_simulation);
    Simulation_toolbar->addAction(action_simulate);

    action_pause_simul = new QAction(QIcon(":/resources/pause.png"), tr("pause simulation"), this);
    connect(action_pause_simul, &QAction::triggered, this, &Minidraw::pause_simulation);
    Simulation_toolbar->addAction(action_pause_simul);

    action_reset_simul = new QAction(QIcon(":/resources/reset.png"), tr("reset simulation"), this);
    connect(action_reset_simul, &QAction::triggered, this, &Minidraw::reset_simulation);
    Simulation_toolbar->addAction(action_reset_simul);

    action_clear_simul = new QAction(QIcon(":/resources/clear.png"), tr("clear simulation"), this);
    connect(action_clear_simul, &QAction::triggered, this, &Minidraw::clear_simulation);
    Simulation_toolbar->addAction(action_clear_simul);
}

void Minidraw::create_snow_type_toolbar()
{
    SnowType_toolbar = addToolBar(tr("snow type toolbar"));
    choose_snow_type[0] = new QAction(QIcon(":/resources/num1.jpg"), tr("Lower Hardening"), this);
    connect(choose_snow_type[0], &QAction::triggered, this, &Minidraw::set_snow_type_1);
    SnowType_toolbar->addAction(choose_snow_type[0]);
    
    choose_snow_type[1] = new QAction(QIcon(":/resources/num2.jpg"), tr("Lower Young's"), this);
    connect(choose_snow_type[1], &QAction::triggered, this, &Minidraw::set_snow_type_2);
    SnowType_toolbar->addAction(choose_snow_type[1]);

    choose_snow_type[2] = new QAction(QIcon(":/resources/num3.jpg"), tr("Lower Critical Compression"), this);
    connect(choose_snow_type[2], &QAction::triggered, this, &Minidraw::set_snow_type_3);
    SnowType_toolbar->addAction(choose_snow_type[2]);

    choose_snow_type[3] = new QAction(QIcon(":/resources/num4.jpg"), tr("Reference"), this);
    connect(choose_snow_type[3], &QAction::triggered, this, &Minidraw::set_snow_type_4);
    SnowType_toolbar->addAction(choose_snow_type[3]);

    choose_snow_type[4] = new QAction(QIcon(":/resources/num5.jpg"), tr("Lower Critical Compression & Stretch"), this);
    connect(choose_snow_type[4], &QAction::triggered, this, &Minidraw::set_snow_type_5);
    SnowType_toolbar->addAction(choose_snow_type[4]);

    choose_snow_type[5] = new QAction(QIcon(":/resources/num6.jpg"), tr("Lower Critical Stretch"), this);
    connect(choose_snow_type[5], &QAction::triggered, this, &Minidraw::set_snow_type_6);
    SnowType_toolbar->addAction(choose_snow_type[5]);
}

void Minidraw::set_snow_type_1()
{
    controller->set_snow_type(1);
}
void Minidraw::set_snow_type_2()
{
    controller->set_snow_type(2);
}
void Minidraw::set_snow_type_3()
{
    controller->set_snow_type(3);
}
void Minidraw::set_snow_type_4()
{
    controller->set_snow_type(4);
}
void Minidraw::set_snow_type_5()
{
    controller->set_snow_type(5);
}
void Minidraw::set_snow_type_6()
{
    controller->set_snow_type(6);
}

void Minidraw::start_simulation()
{
    controller->is_simulating = true;
    controller->simulate();
}

void Minidraw::pause_simulation()
{
    controller->is_simulating = false;
}
void Minidraw::reset_simulation()
{
    controller->is_simulating = false;
    controller->reset_simulation();
}

void Minidraw::clear_simulation()
{
    controller->is_simulating = false;
    controller->clear_simulation();
}


Minidraw::Minidraw(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Minidraw)
{
    ui->setupUi(this);
    controller = new Minidraw_controller();
    setCentralWidget(controller);
    setWindowTitle(tr("Qtaichi")); // add title
    setWindowIcon(QIcon(":/resources/icon.png")); // add icon

    create_toolbar();
    create_figure_toolbar();
    create_simulation_toolbar();
    create_snow_type_toolbar();
}

Minidraw::~Minidraw()
{
    delete ui;
    delete button_black;
    delete button_blue;
    delete button_green;
    delete button_red;
    delete button_yellow;
    delete choose_circle_act;
    delete choose_curve_act;
    delete choose_line_act;
    delete choose_ellipse_act;
    delete choose_poly_act;
    delete choose_rect_act;
    delete choose_tri_act;
}


