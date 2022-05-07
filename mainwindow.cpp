#include "mainwindow.h"
#include "./ui_mainwindow.h"

std::random_device rdGen;
std::mt19937 gen(rdGen());
std::uniform_int_distribution<> dis0_15(75, 350);

int betw_pipes = -50;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , bird_(100,200)
    , pipe_speed(0)
    ,bird_speed(0)
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

void MainWindow::moveObjects(){

for (int i = 0; i < points.size(); i++){
points[i].setX(points[i].x() - pipe_speed );
if(points[i].x() + 20 <= 0){

    points[i].setY(dis0_15(gen));

    points[i].setX(this->width() + 975);

}

}

bird_.setY(bird_.y() + bird_speed);
bird_speed+=1;


if (bird_.y() + 39 >= this->height()) {
   bird_speed = 0;
   pipe_speed = 0;
}


for (int i = 0; i < 5; i++) {    // bird: 39x52

    if ((bird_.x() + 52 >= points[i].x() - 30 && bird_.x() + 52 <= points[i].x() + 30) ||
            (bird_.x() >= points[i].x() - 30 && bird_.x() <= points[i].x() + 30)){


        if(bird_.y() + 39 >= points[i].y() + 65 ){
         bird_speed = 0;
        pipe_speed = 0;
 }
        if(bird_.y() <= points[i].y() - 65){
            bird_speed = 0;
            pipe_speed = 0;
        }
 else{
            counter++;
        }
 }
}

this-> update();
}



void MainWindow::keyPressEvent(QKeyEvent *event){


    if(event->key() == Qt::Key_Space){

        bird_speed = -10;
        pipe_speed = 5;
   }
}

void MainWindow::paintEvent(QPaintEvent *event){


    QPainter painter(this);

    QImage background("D:/Viktoria/BSU/programming/background.png", "PNG");
    QBrush background_brush(background);



    painter.fillRect(0, 0, this->width(), this->height(), background_brush);


   Bird bird(this->bird_);

    Pipe pipe1(this->points[0]);
    Pipe pipe2(this->points[1]);
    Pipe pipe3(this->points[2]);
    Pipe pipe4(this->points[3]);
    Pipe pipe5(this->points[4]);


    pipe1.create_pipe(painter);
    pipe2.create_pipe(painter);
    pipe3.create_pipe(painter);
    pipe4.create_pipe(painter);
    pipe5.create_pipe(painter);
    bird.create_bird(painter);

}
