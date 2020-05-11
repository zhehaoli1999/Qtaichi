#include "minidraw_controller.h"
#include "ui_minidraw_controller.h"
#include<QMouseEvent>
#include<QPainter>
#include <QFileDialog>
#include"line.h"
#include"rect.h"
#include"circle.h"
#include"triangle.h"
#include"curve.h"
#include"polygon.h"
#include "scanline.h"
#include "taichi.h"

using namespace taichi;
using namespace minidraw;
using Vec = Vector2;
using Mat = Matrix2;

//******************************************************************************
//                            Taichi Class & Variables 
//******************************************************************************

enum MatterType
{
    Fluid = 0,
    Jelly = 1,
    Snow = 2,
    Solid = 3
};

// const global variable 
const int n = 80; /*grid resolution (cells)*/  
int window_w = 600;
int window_h = 600;
const real dt = 1e-4_f, frame_dt = 1e-3_f, dx = 1.0_f / n, inv_dx = 1.0_f / dx;
int step = 0; // simulation step 
const int velocity_ratio = 10; // speed = ratio * velocity line length  
const float area_particle_ratio = 0.015; // num of particles = ratio * area
int snow_type = 4; // snow type

class Simulation
{
public:
    Simulation() {};
    ~Simulation() {};

public:
    real particle_mass = 1.0_f;
    real vol = 1.0_f;
    real hardening = 10.0_f;
    real E = 1e4_f;
    real nu = 0.2_f;

    real theta_c = 2.5e-2_f;
    real theta_s = 7.5e-3_f;
    bool plastic = true;
    
    struct Particle {
        Vec x, v; 
        Mat F, C; 
        real Jp; 
        QColor c;
        MatterType ptype;  /*0: fluid 1: jelly 2: snow 3: solid*/

        Particle(Vec x, Vec v = Vec(0), QColor c = Qt::red, MatterType ptype = Snow) :
            x(x), v(v), F(1), C(0),c(c), Jp(1), ptype(ptype)
        {}
    };

    std::vector<Particle> particles;
    Vector3 grid[n + 1][n + 1];   

public:

    // MLS-MFM method from Taichi demo code
    void advance(real dt) {
        std::memset(grid, 0, sizeof(grid)); // Reset grid
        for (auto& p : particles) {  // P2G
            Vector2i base_coord = (p.x * inv_dx - Vec(0.5_f)).cast<int>();//element-wise floor
            Vec fx = p.x * inv_dx - base_coord.cast<real>();
            // Quadratic kernels  [http://mpm.graphics   Eqn. 123, with x=fx, fx-1,fx-2]
            Vec w[3]
            { 
                Vec(0.5) * sqr(Vec(1.5) - fx), 
                Vec(0.75) - sqr(fx - Vec(1.0)),
                Vec(0.5) * sqr(fx - Vec(0.5)) 
            };

            // set param according to type
            /**************************************************/
            if (p.ptype == Snow) 
            {
                set_snow_type(snow_type);
            }
            if (p.ptype == Solid) 
            { 
                E = 1.7e4_f;
                hardening = 30.0_f;  // TODO: make solid type more like solid  
            }

            auto e = std::exp(hardening * (1.0_f - p.Jp));
            if (p.ptype == Jelly) e = 0.3;

            real mu_0 = E / (2 * (1 + nu)), lambda_0 = E * nu / ((1 + nu) * (1 - 2 * nu));
            auto mu = mu_0 * e, lambda = lambda_0 * e;
            if (p.ptype == Fluid) mu = 0;
            /**************************************************/


            real J = determinant(p.F); //Current volume
            Mat r, s; polar_decomp(p.F, r, s); //Polar decomp. for fixed corotated model
            auto stress =                           // Cauchy stress times dt and inv_dx
                -4 * inv_dx * inv_dx * dt * vol * (2 * mu * (p.F - r) * transposed(p.F) + lambda * (J - 1) * J);
            auto affine = stress + particle_mass * p.C;
            for (int i = 0; i < 3; i++) 
                for (int j = 0; j < 3; j++) 
                {  // Scatter to grid
                    auto dpos = (Vec(i, j) - fx) * dx;
                    Vector3 mv(p.v * particle_mass, particle_mass); //translational momentum
                    grid[base_coord.x + i][base_coord.y + j] +=
                        w[i].x * w[j].y * (mv + Vector3(affine * dpos, 0));
                }
        }
        for (int i = 0; i <= n; i++) 
            for (int j = 0; j <= n; j++) 
            {   //For all grid nodes
                auto& g = grid[i][j];
                if (g[2] > 0) {                                // No need for epsilon here
                    g /= g[2];                                   //        Normalize by mass
                    g += dt * Vector3(0, 200, 0);               //                  Gravity
                    real boundary = 0.05, x = (real)i / n, y = real(j) / n; //boundary thick.,node coord
                    if (x < boundary || x > 1 - boundary || y > 1 - boundary) g = Vector3(0); //Sticky
                    if (y < boundary) g[1] = std::max(0.0_f, g[1]);             //"Separate"
                }
        }
        for (auto& p : particles) {                                // Grid to particle
            Vector2i base_coord = (p.x * inv_dx - Vec(0.5_f)).cast<int>();//element-wise floor
            Vec fx = p.x * inv_dx - base_coord.cast<real>();
            Vec w[3]{ Vec(0.5) * sqr(Vec(1.5) - fx), Vec(0.75) - sqr(fx - Vec(1.0)),
                     Vec(0.5) * sqr(fx - Vec(0.5)) };
            p.C = Mat(0); p.v = Vec(0);
            for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) {
                auto dpos = (Vec(i, j) - fx),
                    grid_v = Vec(grid[base_coord.x + i][base_coord.y + j]);
                auto weight = w[i].x * w[j].y;
                p.v += weight * grid_v;                                      // Velocity
                p.C += 4 * inv_dx * Mat::outer_product(weight * grid_v, dpos); // APIC C
            }
            p.x += dt * p.v;                                                // Advection
            auto F = (Mat(1) + dt * p.C) * p.F;                      // MLS-MPM F-update

            // set param according to type
            /*************************************************************/
            if (p.ptype == Fluid) { p.F = Mat(1) * sqrt(determinant(F)); }
            else if (p.ptype == Jelly) { p.F = F; }
            else if (p.ptype == Snow) 
            {
                Mat svd_u, sig, svd_v; svd(F, svd_u, sig, svd_v);
                for (int i = 0; i < 2 * int(plastic); i++)                // Snow Plasticity
                    sig[i][i] = clamp(sig[i][i], 1.0_f - theta_c, 1.0_f + theta_s);
                real oldJ = determinant(F); F = svd_u * sig * transposed(svd_v);
                real Jp_new = clamp(p.Jp * oldJ / determinant(F), 0.6_f, 20.0_f);
                p.Jp = Jp_new; p.F = F;
            }
            else if (p.ptype == Solid) { p.F = F ;  }
            /*************************************************************/
        }
    }

    // Add circle object in scene
    void add_object_circle(Vec center, real radius, QColor color, int num = 500, MatterType t = Snow, Vec velocity = Vec(0.0_f))
    {
        int i = 0;
        float area = pi * (radius * radius)*window_w*window_h; 
        num = (area * area_particle_ratio > num) ? area * area_particle_ratio : num;
        while (i < num) {
            auto pos = (Vec::rand() * 2.0_f - Vec(1)) * radius; // [-1, 1] * radius
            if (pos.x * pos.x + pos.y * pos.y < radius * radius) {
                particles.push_back(Particle(pos + center, velocity, color, t));
                i++;
            }
        }
    }
    
    // Add rectangle object in scene
    void add_object_rectangle(Vec v1, Vec v2, QColor color, int num = 500, MatterType t = Snow, Vec velocity = Vec(0.0_f))
    {
        Vec box_min(min(v1.x, v2.x), min(v1.y, v2.y)), box_max(max(v1.x, v2.x), max(v1.y, v2.y));
        int i = 0;
        float area = (box_max.x - box_min.x)*window_w * (box_max.y - box_min.y)*window_h; // get rect area
        num = (area * area_particle_ratio > num) ? area * area_particle_ratio : num;
        while (i < num) {
            auto pos = Vec::rand();
            if (pos.x > box_min.x&& pos.y > box_min.y&& pos.x < box_max.x && pos.y < box_max.y) {
                particles.push_back(Particle(pos, velocity, color, t));
                i++;
            }
        }
    }

    // Add polygon & free-hand object in scene
    void add_object_polygon(Figure* polygon, QColor color, int num = 500, MatterType t = Snow, Vec velocity = Vec(0.0_f))
    {
        CScanLine scanline(polygon); // use scanline method here 
        int i = 0;
        float area = scanline.GetRectArea();
        //std::cout << "w:" << scanline.width << "h:"<< scanline.height<<endl;
        //std::cout << "polygon area:"<<area << endl;
        num = (area * area_particle_ratio > num) ? area * area_particle_ratio : num;
        while (i < num) 
        {
            auto pos = Vec::rand();
            auto x0 = pos.x * window_w;
            auto y0 = pos.y * window_h;
            if (y0 <= scanline.top && y0 >= scanline.bottom && x0 >= scanline.left && x0 <= scanline.right)
            {
                if(scanline.mat_inside.at(std::pair<int,int>(int(x0), int(y0))))
                {
                    particles.push_back(Particle(pos, velocity, color, t));
                    i++;
                }
            }
        }

    }

    void simulateOnce()
    {
        advance(dt);
    }

    // Set different snow type according to SIGGRAPH2013 MPM paper. 
    void set_snow_type(int type)
    {
        switch (type)
        {
        case 1: // lower hardening
        {
            E = 1e4_f;
            theta_c = 2.5e-2_f;
            theta_s = 7.5e-3_f;
            hardening = 5.0_f;
            break;
        }
        case 2:// lower Young's modulus
        {
            E = 0.2e4_f;
            theta_c = 2.5e-2_f;
            theta_s = 7.5e-3_f;
            hardening = 10.0_f;
            break;
        }
        case 3:// lower critical compression
        {
            E = 1e4_f;
            real theta_c = 1.9e-2_f;
            real theta_s = 7.5e-3_f;
            hardening = 10.0_f;
            break;
        }
        case 4:// Reference
        {
            E = 1e4_f;
            real theta_c = 2.5e-2_f;
            real theta_s = 7.5e-3_f;
            hardening = 10.0_f;
            break;
        }
        case 5:// lower critical compression & strestch
        {
            E = 1e4_f;
            real theta_c = 1.9e-2_f;
            real theta_s = 5.0e-3_f;
            hardening = 10.0_f;
            break;
        }
        case 6:// lower critical  strestch
        {
            E = 1e4_f;
            real theta_c = 2.5e-2_f;
            real theta_s = 5.0e-3_f;
            hardening = 10.0_f;
            break;
        }
        default:break;

        }
    }
};

Simulation taichi_simulation;
/***************************************************************************************/


//******************************************************************************
//                           Minidraw_controllers 
//******************************************************************************

Minidraw_controller::Minidraw_controller(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Minidraw_controller)
{
    ui->setupUi(this);
    current_line_width = 7; // line width be 7 initially
    current_line_color = Qt::white; // set line color be white initially
    current_figure_type = k_curve; // set figure type be free hand initially

    p_current_figure = nullptr;
    is_drawing_ploygon = false; // set is_drawing_polygon be false initially
    is_simulating = false;
}

Minidraw_controller::~Minidraw_controller()
{
    delete ui;

    // delete all figures at the end
    for (int i = 0; i < figure_array.size(); i++)
    {
        if (figure_array[i])
        {
            delete figure_array[i];
            figure_array[i] = nullptr;
        }
    }
}

void Minidraw_controller::mousePressEvent(QMouseEvent *event)
{
    // Judge if the left button is pressed
    if(Qt::LeftButton == event->button())
    {
        draw_status = true; // set draw_status be true;
        current_point = event->pos();
    }
    if(true == draw_status){
        switch (current_figure_type) {
            default: //k_line
                p_current_figure = new Line(current_point);
                break;
            case k_rect:
                p_current_figure  = new Rect(current_point);
                break;
            case k_circle:
                p_current_figure = new Circle(current_point);
                break;
            case k_ellipse:
                p_current_figure = new minidraw::Ellipse(current_point);
                break;
            case k_triangle:
                p_current_figure = new minidraw::Triangle(current_point);
                break;
            case k_curve:
                p_current_figure = new Curve(current_point);
                break;
            case k_polygon:
                if(false == is_drawing_ploygon)
                {
                    p_current_figure = new minidraw::Polygon(current_point);
                    is_drawing_ploygon = true;
                }
                // if is drawing polygon and polygon has already be instanced, add new point:
                else p_current_figure -> add_point(current_point);
                break;
        }

    }
    // if right button is pressed and is drawing polygon, then finish drawing polygon.
    if(Qt::RightButton == event->button())
    {
        if(true == is_drawing_ploygon)
        {
            is_drawing_ploygon = false;
            // polygon drawing over, store polygon
            if (p_current_figure != nullptr){
                figure_array.push_back(p_current_figure);
                // after store: reset p_current_figure
                p_current_figure = nullptr;

            }
        }
    }

}

void Minidraw_controller::mouseMoveEvent(QMouseEvent *event)
{
    if (true == draw_status) {
        // Want to have the figure be drawn when user moves cursor, so store current point
       current_point = event->pos();
    }
    repaint();
}

void Minidraw_controller::mouseReleaseEvent(QMouseEvent *event)
{
    draw_status = false; // when release mouse, stop drawing.
    current_point = event -> pos();

    // store the color and width for all figure types
    if (p_current_figure != nullptr){
        p_current_figure -> set_width(current_line_width);
        p_current_figure -> set_color(current_line_color);

        // if not polygon, then add current point as the end point of figure
        // for polygon, this point is not endpoint
        p_current_figure -> add_point(current_point);

        if(current_figure_type != k_polygon)
        {
            // store the figure into figure array
            figure_array.push_back(p_current_figure);
            // reset p_current_figure = nullptr
            p_current_figure = nullptr;
        }
    }
    repaint();
}

void Minidraw_controller::paintEvent(QPaintEvent*)
{
    QPainter painter(this); // 定义painter在this指向的控件（此例为Maindraw_controller）中绘图

    // get window height and width, and allows set window_w == window_h
    window_h = this->height();
    window_w = this->width();
    int min_size = (window_h > window_w) ? window_w : window_h;
    window_h = window_w = min_size;

    // draw boundary 
    painter.setPen(QPen(QColor(0x4FB99F), 4));
    QRect rectBoundary(window_w * 0.04, window_h * 0.04 - 3, window_w * 0.92 - 6, window_h * 0.92 + 3);
    painter.drawRect(rectBoundary);
    QPalette pal = palette();

    // set darkcyan background
    pal.setColor(QPalette::Background, 0x112F41);
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    // when simulating, we can also draw figures !
    painter.setPen(QPen(current_line_color, current_line_width));

    if (p_current_figure != nullptr) p_current_figure->draw_dynamic(painter, current_point);

    for (int i = 0; i < figure_array.size(); i++)
    {
        painter.setPen(QPen(figure_array[i]->get_color(), figure_array[i]->get_width()));
        figure_array[i]->draw(painter);
    }

    // Another situation: user doesn't click right button, instead click other figure tool:
    // need to finish the drawing of polygon and store polygon at this time.
    if (current_figure_type != k_polygon) {
        if (is_drawing_ploygon == true)
        {
            is_drawing_ploygon = false;
            // store polygon
            if (p_current_figure != nullptr) {
                figure_array.push_back(p_current_figure);
                // after store: reset p_current_figure
                p_current_figure = nullptr;
            }
        }
    }

    // always draw particles 
    for (auto p : taichi_simulation.particles)
    {
        painter.setPen(QPen(p.c, 1));
        painter.setBrush(QBrush(p.c));
        QRect rectangle(p.x[0] * window_w, p.x[1] * window_h,4, 4);
        painter.drawEllipse(rectangle);
    }
}

void Minidraw_controller::add_objects()
{    
    for (int i = 0; i < figure_array.size(); i++)
    {
        auto p_figure = figure_array[i];
        bool has_init_velocity = false;

        // 1. wrong type, just ignore it.
        if (!dynamic_cast <minidraw::Line*>(p_figure)
            && p_figure->get_color() == Qt::red)
        {
            continue; 
        }

        // 2. get next figure: if next figure is velocity line, then can set velocity 
        auto p_next_figure = figure_array[(i + 1) % figure_array.size()];
        if (dynamic_cast <minidraw::Line*>(p_next_figure) 
            && p_next_figure->get_color() == Qt::red)
        {
            has_init_velocity = true;
        }

        MatterType ptype;
        
        // 3. get type of particles according to line color: 
        //  black: solid
        //  white: snow
        //  orange: jelly
        //  blue: fluid
        auto figure_color = p_figure->get_color();
        if (figure_color == Qt::black) ptype = Solid;
        else if (figure_color == Qt::white) ptype = Snow;
        else if (figure_color == QColor(0xED553B)) ptype = Jelly;
        else ptype = Fluid;

        auto p_points = p_figure->p_point_array;
        
        // get object shape and create object
        // if figure type is rectangle
        if (dynamic_cast <minidraw::Rect*>(p_figure) ) 
        {
            assert(p_points.size() == 2);
            auto x0 = float(p_points[0].x()) / window_w;
            auto y0 = float(p_points[0].y()) / window_h;
            auto x1 = float(p_points[1].x()) / window_w;
            auto y1 = float(p_points[1].y()) / window_h;
            if (has_init_velocity) 
            {
                auto velocity_vector = p_next_figure->get_line_vector();
                taichi_simulation.add_object_rectangle(
                    Vec(x0, y0), Vec(x1, y1), figure_color, 800, ptype,
                    Vec(velocity_vector.x() /velocity_ratio, velocity_vector.y() / velocity_ratio)
                );
            }
            else 
            {
                taichi_simulation.add_object_rectangle(
                    Vec(x0, y0), Vec(x1, y1), figure_color, 800, ptype
                );
            }
        }

        // if figure type is polygon, triangle or free-hand 
        else if (dynamic_cast <minidraw::Polygon*>(p_figure) ||  
            dynamic_cast <minidraw::Triangle*>(p_figure) ||
            dynamic_cast <minidraw::Curve*>(p_figure))
        {

            auto x0 = float(p_points[0].x()) / window_w;
            auto y0 = float(p_points[0].y()) / window_h;
            auto x1 = float(p_points[1].x()) / window_w;
            auto y1 = float(p_points[1].y()) / window_h;

            //std::cout << "(" << x0 << ", " << y0 << "),( " << x1 << ", " << y1 << ")" << endl;
            
            if (has_init_velocity) 
            {
                auto velocity_vector = p_next_figure->get_line_vector();
                taichi_simulation.add_object_polygon(
                    p_figure, figure_color, 800, ptype,
                    Vec(velocity_vector.x()/ velocity_ratio, velocity_vector.y() / velocity_ratio)
                );
            }
            else 
            {
                taichi_simulation.add_object_polygon(
                    p_figure, figure_color, 800, ptype
                );
            }
        }

        // if figure type is circle 
        else if (dynamic_cast <Circle*>(p_figure)) 
        {
            auto p_points = p_figure->p_point_array;
            assert(p_points.size() == 2);
            auto x0 = float(p_points[0].x()) / window_w;
            auto y0 = float(p_points[0].y()) / window_h;
            auto x1 = float(p_points[1].x()) / window_w;
            auto y1 = float(p_points[1].y()) / window_h;
            if (has_init_velocity) 
            {
                auto velocity_vector = p_next_figure->get_line_vector();
                taichi_simulation.add_object_circle(
                    Vec((x0 + x1) / 2, (y0 + y1) / 2), (x1 - x0) / 2, figure_color, 800, ptype,
                    Vec(velocity_vector.x() / velocity_ratio, velocity_vector.y() / velocity_ratio)
                );
            }
            else 
            {
                taichi_simulation.add_object_circle(
                    Vec((x0 + x1) / 2, (y0 + y1) / 2), (x1 - x0) / 2, figure_color, 800, ptype
                );
            }
        }
    }
    
    // insert figure_array to the end of figure_array_backup, NOTE: no need to clear figure_Array_backup here
    figure_array_backup.insert(figure_array_backup.end(), figure_array.begin(), figure_array.end());

    // the end, clear figure_array
    figure_array.clear(); 
}

void Minidraw_controller::simulate()
{
    // 1. create objects and add them to particles 
    add_objects();  

    // 2. start simulation
    for (int step = 0; ; step++) 
    {
        QCoreApplication::processEvents(); // response to new message 
        if (is_simulating == false) 
        { 
            break;  
        }
        taichi_simulation.simulateOnce();

        // 3. update frame, draw the particles in the window
        if (step % int(frame_dt / dt) == 0) {
            repaint();
        }
    }
}

void Minidraw_controller::reset_simulation()
{
    is_simulating = false;
    figure_array.clear();
    taichi_simulation.particles.clear();

    figure_array = figure_array_backup;
    figure_array_backup.clear(); // clear backup figure array here;
    repaint();
}

void Minidraw_controller::clear_simulation()
{
    is_simulating = false;
    figure_array.clear();
    figure_array_backup.clear();
    taichi_simulation.particles.clear();
    repaint();
}

void Minidraw_controller::undo()
{
    if (figure_array.size() > 0)
    {
        figure_array.pop_back();
    }
    repaint();
}

void Minidraw_controller::clearFigure()
{
    figure_array.clear();
    repaint();
}

void Minidraw_controller::set_snow_type(int type)
{
    if(type <= 6 && type >=1) snow_type = type;
}

void Minidraw_controller::save_scene()
{
    QPixmap pix = this->grab(); // get screen shot
    QString img_name = "temp.png";
    QString img_path = QFileDialog::getSaveFileName(this, tr("Save Scene"), img_name, "Image Files (*.png *.jpg *.bmp)");
    if (!img_path.isNull())
    {
        pix.save(img_path);
    }
}