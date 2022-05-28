#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pipe.h"
#include "bird.h"

#include <QMainWindow>
#include<QPainter>
#include<QImage>
#include<QBrush>
#include <QTimer>
#include <QKeyEvent>
#include <random>
#include<QPaintEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

    ~MainWindow();

public slots:
  void moveObjects();
  void ActionBeforeTheStart();
  void StartOfGame();
  void Restart();
  void Death();

private slots:

  void on_pushButton_2_clicked();

  void on_horizontalSlider_valueChanged(int value);

  void on_horizontalSlider_2_valueChanged(int value);

  void on_pushButton_clicked();

  void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<QPoint> points;
    QPoint bird_;
    int pipe_speed;
    int bird_speed;
    int counter;    
    int anim_index;
    int amplitude;
    QTimer* objects_t = new QTimer(this);
    QTimer* start_timer = new QTimer(this);
    QString result;
    QImage* bird_images[3];
    std::vector<QString> phrases;
};
#endif // MAINWINDOW_H
