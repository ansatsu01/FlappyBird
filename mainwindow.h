#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    ~MainWindow();

public slots:
  void movePipes();
private:
    Ui::MainWindow *ui;
    std::vector<QPoint> points;


};


class Pipe : public QMainWindow
{
    Q_OBJECT

public:
    Pipe(QPoint& center);
    void create_pipe(QPainter& painter);


    QRect upper_pipe;
    QRect lower_pipe;

private:

QPoint center;
};
#endif // MAINWINDOW_H
