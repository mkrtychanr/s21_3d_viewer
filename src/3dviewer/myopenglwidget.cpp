#include "myopenglwidget.h"
#include <cmath>


extern "C" {
#include "../data_containers/headers/point_vector.h"
#include "../data_containers/headers/line_vector.h"
};



MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

void MyOpenGLWidget::initializeGL() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0 / 255.f, 0 / 255.f, 0 / 255.f, 1);
}

void MyOpenGLWidget::resizeGL(int w, int h) {
    glViewport(0,0,w,h);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void MyOpenGLWidget::paintGL() {
    if (!renderStatus) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        if (!perspective) {
          glOrtho(-1.5, 1.5, -1.5, 1.5, -2, 1000);
        } else {
          glFrustum(-1.5, 1.5, -1.5, 1.5, 0.8, 1000);
          glTranslatef(0, 0, -2);
        }
        glMatrixMode(GL_MODELVIEW);
        glClearColor(background_color.redF(), background_color.greenF(),background_color.blueF(), 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        rotate();
        if (edge_type) draw_points();
        draw_lines();
        update();
    }
}


void MyOpenGLWidget::draw_points() {
    glEnable(edge_type);
    glPointSize(edge_size);
    glColor3f(edge_color.redF(), edge_color.greenF(), edge_color.blueF());
    auto p = *((point_vector*)points_print);
    glBegin(GL_POINTS);
    for (size_t i = 0; i < p.size; i++) {
     glVertex3d((p.data[i].x + x_move) * scale, (p.data[i].y + y_move) * scale, (p.data[i].z + z_move) * scale);
    }
    glEnd();
    glDisable(edge_type);
}

void MyOpenGLWidget::draw_lines() {
    glLineStipple(3, 0x1C47);
    glEnable(vertical_type);
    glLineWidth(vertical_size);
    glColor3f(vertical_color.redF(), vertical_color.greenF(), vertical_color.blueF());
    auto p = *((point_vector*)points_print);
    auto l = *((line_vector*)lines);
    glBegin(GL_LINES);
    for (size_t i = 0; i < l.size; i++) {
        auto firstPoint = l.data[i].from - 1;
        auto secondPoint = l.data[i].to - 1;
        if (p.size <= firstPoint || p.size <= secondPoint) continue; 
        auto from = p.data[firstPoint];
        auto to = p.data[secondPoint];
        glVertex3d((from.x + x_move) * scale, (from.y + y_move) * scale, (from.z + z_move) * scale);
        glVertex3d((to.x + x_move) * scale, (to.y + y_move) * scale, (to.z + z_move) * scale);
    }

    glEnd();
    glDisable(vertical_type);
}

void MyOpenGLWidget::rotate() {
    if (x_rotate != last_x_rotate || y_rotate != last_y_rotate || z_rotate != last_z_rotate) {
        last_x_rotate = x_rotate;
        last_y_rotate = y_rotate;
        last_z_rotate = z_rotate;
        remove_point((point_vector*)points_print);
        points_print = copy_point((point_vector*)points);
        rotate_ox();
        rotate_oy();
        rotate_oz();
    }
}

void MyOpenGLWidget::rotate_ox() {
    double angle = x_rotate * (3.14f / 180.0f);
    auto p = (point_vector*)points_print;
    for (size_t i = 0; i < p -> size; i++) {
        double temp_y = p -> data[i].y;
        double temp_z = p -> data[i].z;
        p -> data[i].y = std::cos(angle) * temp_y - std::sin(angle) * temp_z;
        p -> data[i].z = std::sin(angle) * temp_y + std::cos(angle) * temp_z;
    }
}

void MyOpenGLWidget::rotate_oy() {
    double angle = y_rotate * (3.14f / 180.0f);
    auto p = (point_vector*)points_print;
    for (size_t i = 0; i < p -> size; i++) {
        double temp_x = p -> data[i].x;
        double temp_z = p -> data[i].z;
        p -> data[i].x = std::cos(angle) * temp_x - std::sin(angle) * temp_z;
        p -> data[i].z = std::sin(angle) * temp_x + std::cos(angle) * temp_z;
    }
}

void MyOpenGLWidget::rotate_oz() {
    double angle = z_rotate * (3.14f / 180.0f);
    auto p = (point_vector*)points_print;
    for (size_t i = 0; i < p -> size; i++) {
        double temp_x = p -> data[i].x;
        double temp_y = p -> data[i].y;
        p -> data[i].x = std::cos(angle) * temp_x - std::sin(angle) * temp_y;
        p -> data[i].y = std::sin(angle) * temp_x + std::cos(angle) * temp_y;
    }
}
