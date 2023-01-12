#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#define GL_SILENCE_DEPRECATION
#include <QKeyEvent>
#include <QtOpenGLWidgets/QtOpenGLWidgets>

class MyOpenGLWidget : public QOpenGLWidget {
  Q_OBJECT
 public:
  MyOpenGLWidget(QWidget *parent = nullptr);

  // масштаб
  double scale = 1;

  // перемещение
  double x_move = 0;
  double y_move = 0;
  double z_move = 0;

  // вращение
  double x_rotate = 0;
  double last_x_rotate = 0;
  double y_rotate = 0;
  double last_y_rotate = 0;
  double z_rotate = 0;
  double last_z_rotate = 0;

  // перспектива
  int perspective = 1;

  // цвета
  QColor background_color = QColorConstants::White;
  QColor edge_color;
  QColor vertical_color;

  // размер
  int edge_size = 1;
  int vertical_size = 1;

  // тип
  int edge_type = GL_POINT;
  int vertical_type = GL_LINES;


  void *points;
  void *lines;
  void *points_print;

  bool renderStatus = true;

 protected:
  /**
   * @brief Инициализация окна
   */
  void initializeGL() override;

  /**
   * @brief Изменение размера окна
   *
   * @param w Ширина
   * @param h Высота
   */
  void resizeGL(int w, int h) override;

  /**
   * @brief Отрисовка окна. В данном методе задаётся
   * перспектива,цвет фона, и вызываются методы отрисовки
   * точек и линий
   */
  void paintGL() override;

  /**
   * @brief Отрисовка точек
   */
  void draw_points();

  /**
   * @brief Отрисовка линий
   */
  void draw_lines();

  /**
   * @brief Вращение модели
   */
  void rotate();

  /**
   * @brief Вращение по оси x
   */
  void rotate_ox();

  /**
   * @brief Вращение по оси y
   */
  void rotate_oy();

  /**
   * @brief Вращение по оси z
   */
  void rotate_oz();
};

#endif  // MYOPENGLWIDGET_H
