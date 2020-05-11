#include "minidraw.h"
#include "ui_minidraw.h"

#include<QToolButton>

void Minidraw::set_line_width(int width)
{
    controller -> current_line_width = width;
}

void Minidraw::save_scene()
{
    controller->save_scene();
}

//******************************************************************************
//                            Set line colors
//******************************************************************************
void Minidraw::set_line_color_red(void)
{
    controller -> current_line_color = Qt::red;
    controller-> current_figure_type = k_line; // also set figure type be line
}
void Minidraw::set_line_color_blue(void)
{
    controller->current_line_color = QColor(0x87CEFA);
    controller->current_figure_type = k_curve; // also set figure type be free-hand
}
void Minidraw::set_line_color_green(void)
{
    controller -> current_line_color = Qt::green;
}
void Minidraw::set_line_color_orange(void)
{
    controller->current_line_color = QColor(0xED553B);
    controller->current_figure_type = k_curve; // also set figure type be free-hand
}
void Minidraw::set_line_color_black(void)
{
    controller -> current_line_color = Qt::black;
    controller->current_figure_type = k_curve; // also set figure type be free-hand
}
void Minidraw::set_line_color_yellow(void)
{
    controller -> current_line_color = Qt::yellow;
}

void Minidraw::set_line_color_white(void)
{
    controller->current_line_color = Qt::white;
    controller->current_figure_type = k_curve; // also set figure type be free-hand
}

//******************************************************************************
//                            Set figure type
//******************************************************************************
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


//******************************************************************************
//                            figure Type toolbar
//******************************************************************************
void Minidraw::create_figure_toolbar()
{
    figure_toolbar = addToolBar(tr("Figure Tools"));

    //// button for line
    //choose_line_act = new QAction( QIcon(":/resources/line_icon.png"), tr("line tool"),this);
    //connect(choose_line_act, &QAction::triggered, this, &Minidraw::set_figure_tool_line);
    //figure_toolbar->addAction(choose_line_act);

    // button for curve
    QAction*  choose_curve_act = new QAction( QIcon(":/resources/curve_icon.png"), tr("curve tool"),this);
    connect(choose_curve_act, &QAction::triggered, this, &Minidraw::set_figure_tool_curve);
    figure_toolbar->addAction(choose_curve_act);

    // button for circle
    QAction*  choose_circle_act = new QAction( QIcon(":/resources/circle_icon.png"), tr("circle tool"),this);
    connect(choose_circle_act, &QAction::triggered, this, &Minidraw::set_figure_tool_circle);
    figure_toolbar->addAction(choose_circle_act);

    //// button for ellipse
    //choose_ellipse_act = new QAction(QIcon(":/resources/ellipse_icon.png"), tr("ellipse tool"),this);
    //connect(choose_ellipse_act, &QAction::triggered, this, &Minidraw::set_figure_tool_ellipse);
    //figure_toolbar->addAction(choose_ellipse_act);

    // button for rect
    QAction * choose_rect_act = new QAction( QIcon(":/resources/rect_icon.png"), tr("rect tool"),this);
    connect(choose_rect_act, &QAction::triggered, this, &Minidraw::set_figure_tool_rect);
    figure_toolbar->addAction(choose_rect_act);

    // button for triangle
    QAction * choose_tri_act = new QAction(QIcon(":/resources/tri_icon.png"), tr("triangle tool"),this);
    connect(choose_tri_act, &QAction::triggered, this, &Minidraw::set_figure_tool_tri);
    figure_toolbar->addAction(choose_tri_act);  

    // button for polygon
    QAction*  choose_poly_act = new QAction(QIcon(":/resources/polygon_icon.png"), tr("poly tool"),this);
    connect(choose_poly_act, &QAction::triggered, this, &Minidraw::set_figure_tool_poly);
    figure_toolbar->addAction(choose_poly_act);

    // button for undo
    QAction*  action_undo = new QAction(QIcon(":/resources/undo.png"), tr("undo last painting"), this);
    connect(action_undo, &QAction::triggered, this, &Minidraw::undo);
    figure_toolbar->addAction(action_undo);

    // button for clear
    QAction*  action_clear = new QAction(QIcon(":/resources/clear.jpg"), tr("clear paintings"), this);
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


//******************************************************************************
//                         Material Type toolbar
//******************************************************************************
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
    QAction* button_black = new QAction(QIcon(":/resources/solid.png"), tr("Solid"), this);
    connect(button_black, &QAction::triggered, this, &Minidraw::set_line_color_black);
    color_toolbar->addAction(button_black);

    QAction* button_white = new QAction(QIcon(":/resources/snow.png"), tr("Snow"), this);
    connect(button_white, &QAction::triggered, this, &Minidraw::set_line_color_white);
    color_toolbar->addAction(button_white);

    QAction* button_blue = new QAction(QIcon(":/resources/fluid.png"), tr("Fluid"), this);
    connect(button_blue, &QAction::triggered, this, &Minidraw::set_line_color_blue);
    color_toolbar->addAction(button_blue);

    //button_yellow = new QToolButton();
    //button_yellow -> setIcon(QIcon(":/resources/yellow.png"));
   // color_toolbar -> addWidget(button_yellow);
    //connect(button_yellow,  SIGNAL (released()), this, SLOT(set_line_color_yellow(void)) );
    
    QAction* button_orange = new QAction(QIcon(":/resources/jelly.png"), tr("Jelly"), this);
    connect(button_orange, &QAction::triggered, this, &Minidraw::set_line_color_orange);
    color_toolbar->addAction(button_orange);

    QAction* button_red = new QAction(QIcon(":/resources/velocity.png"), tr("Draw Velocity Vector"), this);
    connect(button_red, &QAction::triggered, this, &Minidraw::set_line_color_red);
    color_toolbar->addAction(button_red);
}


//******************************************************************************
//                            Simulation Control toolbar
//******************************************************************************
void Minidraw::create_simulation_toolbar()
{
    Simulation_toolbar = addToolBar(tr("simulation toolbar"));
    QAction*  action_simulate = new QAction(QIcon(":/resources/simulate.jpg"), tr("start simulation"), this);
    connect(action_simulate, &QAction::triggered, this, &Minidraw::start_simulation);
    Simulation_toolbar->addAction(action_simulate);

    QAction*  action_pause_simul = new QAction(QIcon(":/resources/pause.png"), tr("pause simulation"), this);
    connect(action_pause_simul, &QAction::triggered, this, &Minidraw::pause_simulation);
    Simulation_toolbar->addAction(action_pause_simul);

    QAction* action_save_simul = new QAction(QIcon(":/resources/save.png"), tr("save current scene"), this);
    connect(action_save_simul, &QAction::triggered, this, &Minidraw::save_scene);
    Simulation_toolbar->addAction(action_save_simul);

    QAction*  action_reset_simul = new QAction(QIcon(":/resources/reset.png"), tr("reset simulation"), this);
    connect(action_reset_simul, &QAction::triggered, this, &Minidraw::reset_simulation);
    Simulation_toolbar->addAction(action_reset_simul);

    QAction* action_clear_simul = new QAction(QIcon(":/resources/clear.png"), tr("clear simulation"), this);
    connect(action_clear_simul, &QAction::triggered, this, &Minidraw::clear_simulation);
    Simulation_toolbar->addAction(action_clear_simul);
}


//******************************************************************************
//                           Snow Type toolbar
//******************************************************************************
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
}


