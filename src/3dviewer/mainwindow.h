#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define GL_SILENCE_DEPRECATION

#include <QColor>
#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <vector>

#include "ima/qgifimage_p.h"
#include "myopenglwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT
  QImage mp[50];
  int check;
  QTimer *timer_gif;

 public:
  QSettings *settings;
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  QGifImage gif;

 public slots:
  void loadSettings();
  void saveSettings();

 private slots:

  void on_pushButton_choose_file_clicked();

  void on_doubleSpinBox_translations_x_valueChanged(double arg1);

  void on_doubleSpinBox_translations_y_valueChanged(double arg1);

  void on_doubleSpinBox_translations_z_valueChanged(double arg1);

  void on_doubleSpinBox_rotation_x_valueChanged(double arg1);

  void on_doubleSpinBox_rotation_y_valueChanged(double arg1);

  void on_doubleSpinBox_rotation_z_valueChanged(double arg1);

  void on_horizontalSlider_scale_valueChanged(int value);

  void on_pushButton_color_background_clicked();

  void on_pushButton_color_edge_clicked();

  void on_pushButton_color_verticles_clicked();

  void on_radioButton_central_clicked();

  void on_radioButton_parallel_clicked();

  void on_horizontalSlider_edge_size_valueChanged(int value);

  void on_radioButton_edge_none_clicked();

  void on_radioButton_edge_circle_clicked();

  void on_radioButton_edge_square_clicked();

  void on_horizontalSlider_verticles_size_valueChanged(int value);

  void on_radioButton_verticle_solid_clicked();

  void on_radioButton_verticle_dashed_clicked();

  void on_pushButton_screen_clicked();

  void on_pushButton_gif_clicked();

  void timer_grab();

  void print_grab();

 private:
  Ui::MainWindow *ui;
  MyOpenGLWidget *myopenglwidget;
};
#endif  // MAINWINDOW_H
