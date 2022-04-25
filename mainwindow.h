#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pipe.h"
#include "bird.h"

#include <QMainWindow>
#include<QPainter>
#include<QPixmap>
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
  void movePipes();
private:
    Ui::MainWindow *ui;
    std::vector<QPoint> points;
    QPoint bird_;
    double pipe_speed;
    double bird_speed;

};
#endif // MAINWINDOW_H
