#include "mainwindow.h"

#include <cstdio>
#include <cstring>
#include <iostream>

#include "ui_mainwindow.h"

extern "C" {
#include "../data_containers/headers/dynamic_string.h"
#include "../data_containers/headers/line_vector.h"
#include "../data_containers/headers/point_vector.h"
#include "../parser/parser.h"
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowTitle("3d viewer");
  loadSettings();
}

MainWindow::~MainWindow() {
  saveSettings();
  delete ui;
}

void MainWindow::saveSettings() {
  QSettings settings("settings_3D", "Conf");

  settings.setValue("X_translation", ui->doubleSpinBox_translations_x->value());
  settings.setValue("Y_translation", ui->doubleSpinBox_translations_y->value());
  settings.setValue("Z_translation", ui->doubleSpinBox_translations_z->value());

  settings.setValue("X_rotation", ui->doubleSpinBox_rotation_x->value());
  settings.setValue("Y_rotation", ui->doubleSpinBox_rotation_y->value());
  settings.setValue("Z_rotation", ui->doubleSpinBox_rotation_z->value());

  settings.setValue("scale", ui->horizontalSlider_scale->value());

  settings.setValue("parallel", ui->radioButton_parallel->isChecked());

  settings.setValue("vertices_format",
                    ui->radioButton_verticle_dashed->isChecked());

  settings.setValue("edges_format", ui->widget->edge_type);

  //  settings.setValue("vertical_color", ui->widget->vertical_color);
}

void MainWindow::loadSettings() {
  QSettings settings("settings_3D", "Conf");

  ui->doubleSpinBox_translations_x->setValue(
      settings.value("X_translation", 0).toInt());
  ui->widget->x_move = ui->doubleSpinBox_translations_x->value();
  ui->doubleSpinBox_translations_y->setValue(
      settings.value("Y_translation", 0).toInt());
  ui->widget->y_move = ui->doubleSpinBox_translations_y->value();
  ui->doubleSpinBox_translations_z->setValue(
      settings.value("Z_translation", 0).toInt());
  ui->widget->z_move = ui->doubleSpinBox_translations_z->value();

  ui->doubleSpinBox_rotation_x->setValue(
      settings.value("X_rotation", 0).toDouble());
  ui->widget->x_rotate = ui->doubleSpinBox_rotation_x->value();
  ui->doubleSpinBox_rotation_y->setValue(
      settings.value("Y_rotation", 0).toDouble());
  ui->widget->y_rotate = ui->doubleSpinBox_rotation_y->value();
  ui->doubleSpinBox_rotation_z->setValue(
      settings.value("Z_rotation", 0).toDouble());
  ui->widget->z_rotate = ui->doubleSpinBox_rotation_z->value();

  ui->horizontalSlider_scale->setValue(settings.value("scale", 0).toInt());
  ui->widget->scale = ui->horizontalSlider_scale->value() * 0.1;

  if (settings.value("parallel", 1).toInt())
    ui->radioButton_parallel->setChecked(1);
  else
    ui->radioButton_central->setChecked(1);
  ui->widget->perspective = ui->radioButton_parallel->isChecked();

  if (settings.value("vertices_format", 1).toInt())
    ui->radioButton_verticle_dashed->setChecked(1);
  else
    ui->radioButton_verticle_solid->setChecked(1);
  ui->widget->vertical_type = !ui->radioButton_verticle_dashed->isChecked();

  if (settings.value("edges_format", GL_POINT_SMOOTH).toInt() ==
      GL_POINT_SMOOTH) {
    ui->radioButton_edge_circle->setChecked(1);
    ui->widget->edge_type = GL_POINT_SMOOTH;
  } else if (settings.value("edges_format", GL_POINT).toInt() == GL_POINT) {
    ui->radioButton_edge_square->setChecked(1);
    ui->widget->edge_type = GL_POINT;
  } else {
    ui->radioButton_edge_none->setChecked(1);
    ui->widget->edge_type = 0;
  }

  //    ui->widget->vertical_color = settings.value("vertical_color");
}

void MainWindow::on_pushButton_choose_file_clicked() {
  QString fileName =
      QFileDialog::getOpenFileName(this, "Open a file", "/Users", "*.obj");
  if (fileName != "") {
    string legacy_path;
    init_string(&legacy_path);
    auto path = fileName.toStdString();
    for (auto i : path) {
      push_back_string(&legacy_path, i);
    }
    ui->widget->points = (void *)get_points_from_file(legacy_path.data);
    ui->widget->lines = (void *)get_polygons_from_file(legacy_path.data);
    std::cout << "Here" << std::endl;
    ui->widget->points_print = copy_point((point_vector *)ui->widget->points);
    std::cout << "And here" << std::endl;
    ui->widget->renderStatus = false;
    remove_string(&legacy_path);
    ui->textEdit_edges_count->setText("0");
    ui->textEdit_verticles_count->setText("0");
    ui->textEdit_filename->setText(fileName.split('/').last());
    ui->textEdit_verticles_count->setText(
        QString::number((((point_vector *)ui->widget->points)->size)));
    ui->textEdit_edges_count->setText(
        QString::number((((line_vector *)ui->widget->lines)->size)));
  }
}

void MainWindow::on_doubleSpinBox_translations_x_valueChanged(double arg1) {
  ui->widget->x_move = arg1;
}

void MainWindow::on_doubleSpinBox_translations_y_valueChanged(double arg1) {
  ui->widget->y_move = arg1;
}

void MainWindow::on_doubleSpinBox_translations_z_valueChanged(double arg1) {
  ui->widget->z_move = arg1;
}

void MainWindow::on_doubleSpinBox_rotation_x_valueChanged(double arg1) {
  ui->widget->x_rotate = arg1;
}

void MainWindow::on_doubleSpinBox_rotation_y_valueChanged(double arg1) {
  ui->widget->y_rotate = arg1;
}

void MainWindow::on_doubleSpinBox_rotation_z_valueChanged(double arg1) {
  ui->widget->z_rotate = arg1;
}

void MainWindow::on_horizontalSlider_scale_valueChanged(int value) {
  ui->widget->scale = value * 0.1;
}

void MainWindow::on_pushButton_color_background_clicked() {
  ui->widget->background_color =
      QColorDialog::getColor(Qt::white, this, tr("Select Color"));
}

void MainWindow::on_pushButton_color_edge_clicked() {
  ui->widget->edge_color =
      QColorDialog::getColor(Qt::white, this, tr("Select Color"));
}

void MainWindow::on_pushButton_color_verticles_clicked() {
  ui->widget->vertical_color =
      QColorDialog::getColor(Qt::white, this, tr("Select Color"));
}

void MainWindow::on_radioButton_central_clicked() {
  ui->widget->perspective = 0;
}

void MainWindow::on_radioButton_parallel_clicked() {
  ui->widget->perspective = 1;
}

void MainWindow::on_horizontalSlider_edge_size_valueChanged(int value) {
  ui->widget->edge_size = value;
}

void MainWindow::on_radioButton_edge_none_clicked() {
  ui->widget->edge_type = 0;
}

void MainWindow::on_radioButton_edge_circle_clicked() {
  ui->widget->edge_type = GL_POINT_SMOOTH;
}

void MainWindow::on_radioButton_edge_square_clicked() {
  ui->widget->edge_type = GL_POINT;
}

void MainWindow::on_horizontalSlider_verticles_size_valueChanged(int value) {
  ui->widget->vertical_size = value;
}

void MainWindow::on_radioButton_verticle_solid_clicked() {
  ui->widget->vertical_type = GL_LINES;
}

void MainWindow::on_radioButton_verticle_dashed_clicked() {
  ui->widget->vertical_type = GL_LINE_STIPPLE;
}

void MainWindow::on_pushButton_screen_clicked() {
  QString str = QFileDialog::getSaveFileName();

  if (!str.isEmpty()) {
    ui->widget->grab().save(str);
  }
}

void MainWindow::on_pushButton_gif_clicked() {
  check = 0;
  timer_gif = new QTimer();
  connect(timer_gif, SIGNAL(timeout()), this, SLOT(timer_grab()));
  timer_gif->start(100);
  ui->pushButton_gif->setEnabled(0);
}

void MainWindow::timer_grab() {
  if (check > 49) {
    timer_gif->stop();
    disconnect(timer_gif);
    check = 0;
    for (int i = 0; i < 50; gif.addFrame(mp[i++], 200)) {
    }
    QString str =
        QFileDialog::getSaveFileName(0, "Сохранить файл как", "", "*.gif");
    gif.save(str);
    ui->pushButton_gif->setText("GIF");
    ui->pushButton_gif->setEnabled(1);
  } else {
    mp[check] = ui->widget->grab().toImage();
    check += 1;
    ui->pushButton_gif->setText(QString::number(check / 10));
  }
}

void MainWindow::print_grab() {
  if (check > 49) {
    timer_gif->stop();
    disconnect(timer_gif);
  } else {
    gif.addFrame(mp[check]);
    check += 1;
  }
}
