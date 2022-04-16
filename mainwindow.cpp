#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include<QPainter>
#include<QImage>
#include<QBrush>
#include <QTimer>
#include <random>

std::random_device rdGen;
std::mt19937 gen(rdGen());
std::uniform_int_distribution<> dis0_15(75, 350);

int betw_pipes = -50;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   QTimer* ptimer = new QTimer(this);
    connect(ptimer, SIGNAL(timeout()), SLOT(movePipes()));
    ptimer->start(25);


        for(int i=0; i < 5; ++i )
        {
            QPoint point(this->width() + betw_pipes, dis0_15(gen));
            points.push_back(point);
            betw_pipes += 300;
        }

}

MainWindow::~MainWindow()
{
    delete ui;
}

Pipe::Pipe(QPoint& center){

    upper_pipe.setX(center.x() - 30);
    upper_pipe.setY(0);
    upper_pipe.setWidth(60);
    upper_pipe.setHeight(center.y() - 75);

    lower_pipe.setX(center.x() - 30);
    lower_pipe.setY(center.y() + 75);
    lower_pipe.setWidth(60);
    lower_pipe.setHeight(this->height());


}

void Pipe::create_pipe(QPainter& painter){

painter.setBrush(Qt::red);
painter.drawRect(upper_pipe);
painter.drawRect(lower_pipe);

}

void MainWindow::movePipes(){

for (int i = 0; i < points.size(); i++){
points[i].setX(points[i].x() - 3);
if(points[i].x() + 20 <= 0){

    points[i].setY(dis0_15(gen));

    points[i].setX(this->width() + 975);

}
}


this-> update();

}


void MainWindow::paintEvent(QPaintEvent *event){

    Pipe pipe1(this->points[0]);
    Pipe pipe2(this->points[1]);
    Pipe pipe3(this->points[2]);
    Pipe pipe4(this->points[3]);
    Pipe pipe5(this->points[4]);


    QPainter painter(this);

    QImage background("D:/Viktoria/BSU/programming/labs_2s/pixilart-drawing.png", "PNG");
    QBrush background_brush(background);
    painter.fillRect(0, 0, this->width(), this->height(), background_brush);

    painter.setBrush(Qt::red);

    pipe1.create_pipe(painter);
    pipe2.create_pipe(painter);
    pipe3.create_pipe(painter);
    pipe4.create_pipe(painter);
    pipe5.create_pipe(painter);


}
