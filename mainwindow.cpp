#include "mainwindow.h"
#include "ui_mainwindow.h"

std::random_device rdGen;
std::mt19937 gen(rdGen());
std::uniform_int_distribution<> dis0_15(75, 350);


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , bird_(100,200)
    , background("D:/Viktoria/BSU/programming/background.png", "PNG")
    ,pipe_im("D:/Viktoria/BSU/programming/pipe-green.png")
    , pipe_speed(5)
    , bird_speed(-10)
    , counter(0)
     ,anim_index(1)
    ,amplitude(-10)
    ,ch_speed(5)
{

    bird_images[0] = new QImage("D:/Viktoria/BSU/programming/yellowbird-upflap.png", "PNG");  //bird :  52x39
    bird_images[1] = new QImage("D:/Viktoria/BSU/programming/yellowbird-midflap1.png", "PNG");
    bird_images[2] = new QImage("D:/Viktoria/BSU/programming/yellowbird-downflap.png", "PNG");

    connect(objects_t, SIGNAL(timeout()), SLOT(moveObjects()));
    connect (start_timer, SIGNAL(timeout()), SLOT(ActionBeforeTheStart()));

    QBrush brush_;
    QPalette palette_;
    brush_.setTextureImage( background);
    palette_.setBrush(QPalette::Window, brush_);
    this->setAutoFillBackground(true);
    this->setPalette(palette_);
    start_timer->start(25);

int betw_pipes = -50;

        for(int i=0; i < 5; ++i )
        {
            QPoint point(this->width() + betw_pipes, dis0_15(gen));
            points.push_back(point);
            betw_pipes += 300;
        }
 ui->setupUi(this);
 ui->groupBox_2->hide();
this->setWindowIcon(QPixmap("D:/Viktoria/BSU/programming/yellowbird-midflap1.png"));
}

void MainWindow::ActionBeforeTheStart(){
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->groupBox->hide();
    ui->lcdNumber->display(counter);
    ui->lcdNumber_2->display(counter);
    this->update();
}

void MainWindow::StartOfGame(){
    objects_t->start(25);
    start_timer->start(25);
    ui->pushButton->hide();
    ui->label_5->hide();
}


void MainWindow::Restart(){

    counter = 0;

    int betw_pipes_ = -50;

    std::random_device rdGen;
    std::mt19937 gen(rdGen());
    std::uniform_int_distribution<> dis0_15(75, 350);

    ui->lcdNumber->show();
    bird_.setX(100);
    bird_.setY(200);
    bird_speed = -10;
    pipe_speed = ch_speed;

    for(int i = 0; i < 5; i++)
    {
        points[i].setX(this->width()+betw_pipes_);
        points[i].setY(dis0_15(gen));
        betw_pipes_ += 300;

    }

    StartOfGame();

}

void MainWindow::Death(){

bird_speed = 0;
objects_t->stop();
start_timer->stop();
ui->lcdNumber->hide();
ui->pushButton->show();
ui->pushButton_2->show();
ui->pushButton_3->show();
ui->groupBox->show();
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

// checking collisions

if (bird_.y() + 39 >= this->height() - 40) {
  Death();
}

for (int i = 0; i < 5; i++) {       // bird: 39x52

    if ((bird_.x() + 52 >= points[i].x() - 30 && bird_.x() + 52 <= points[i].x() + 30) ||
            (bird_.x() >= points[i].x() - 30 && bird_.x() <= points[i].x() + 30)){


        if(bird_.y() + 39 >= points[i].y() + 65 || bird_.y() <= points[i].y() - 65){
        pipe_speed = 0;
        start_timer->stop();
}

        if(bird_.x() == points[i].x()){counter++;}
}
}

this-> update();
}


void MainWindow::keyPressEvent(QKeyEvent *event){

if(bird_speed != 0 && start_timer->isActive()){
    if(event->key() == Qt::Key_Space){

        bird_speed = amplitude;
   }
}

if(!objects_t->isActive() && bird_speed == -10)
    {
        if(event->key() == Qt::Key_Enter)
        {
             StartOfGame();
        }
    }
}
void MainWindow::paintEvent(QPaintEvent *event){

    QPainter painter(this);
    ui->centralwidget->grabKeyboard();

      Bird bird(this->bird_);
      Pipe pipe1(this->points[0]);
      Pipe pipe2(this->points[1]);
      Pipe pipe3(this->points[2]);
      Pipe pipe4(this->points[3]);
      Pipe pipe5(this->points[4]);

      pipe1.create_pipe(painter, pipe_im);
      pipe2.create_pipe(painter, pipe_im);
      pipe3.create_pipe(painter, pipe_im);
      pipe4.create_pipe(painter, pipe_im);
      pipe5.create_pipe(painter, pipe_im);
    bird.create_bird(painter, bird_images[anim_index]);
    anim_index = (anim_index + 1) % 3;

    QImage ground("D:/Viktoria/BSU/programming/ground.png", "PNG");
    painter.drawImage(0,this->height() - 40, ground);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->groupBox_2->isHidden()){
    ui->groupBox_2->show();
    }
    else{
        ui->groupBox_2->hide();

    }
}
void MainWindow::on_pushButton_2_clicked()
{
    Restart();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ch_speed = value;
}


void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    amplitude = -value;
}

void MainWindow::on_loadButton__clicked()
{
    QString fileName= QFileDialog::getOpenFileName(this, tr("Open file"), QDir::currentPath());
    if (!fileName.isEmpty()){
        QImage image(fileName);
        image= image.scaled(size() );
        if (image.isNull()){
            QMessageBox::information(this, tr("Open file"), tr("Can not load %1.").arg(fileName));
            return;
        }
        //brush= new QBrush;
        QBrush brush;
       // palette= new QPalette;
        QPalette palette;
        brush.setTextureImage( image);
        palette.setBrush(QPalette::Window, brush);
        this->setAutoFillBackground(true);
        this->setPalette(palette);
    }
}


void MainWindow::on_loadButton_2_clicked()
{
    QString fileName= QFileDialog::getOpenFileName(this, tr("Open file"), QDir::currentPath());
    if (!fileName.isEmpty()){
        QImage image(fileName);
        image= image.scaled(size() );
        if (image.isNull()){
            QMessageBox::information(this, tr("Open file"), tr("Can not load %1.").arg(fileName));
            return;
        }
        pipe_im = image;
}
}


void MainWindow::on_loadButton_3_clicked()
{
  for(int i = 0; i < 3; i++){

        QString fileName= QFileDialog::getOpenFileName(this, tr("Open file"), QDir::currentPath());
        if (!fileName.isEmpty()){
            QImage image(fileName);
            image= image.scaled(52,39, Qt::KeepAspectRatio);
            if (image.isNull()){
                QMessageBox::information(this, tr("Open file"), tr("Can not load %1.").arg(fileName));
                return;
            }
            bird_images[i] = new QImage(fileName);

}
  }
}
