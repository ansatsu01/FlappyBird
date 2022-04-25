#include "pipe.h"

Pipe::Pipe(QPoint& center){

    upper_pipe.setX(center.x() - 30);
    upper_pipe.setY(0);
    upper_pipe.setWidth(60);
    upper_pipe.setHeight(center.y() - 60);

    lower_pipe.setX(center.x() - 30);
    lower_pipe.setY(center.y() + 60);
    lower_pipe.setWidth(60);
    lower_pipe.setHeight(600);


}

void Pipe::create_pipe(QPainter& painter){

QImage low_pipeIm("D:/Viktoria/BSU/programming/pipe-green.png", "PNG");

//painter.setBrush(Qt::red);
painter.drawImage(upper_pipe, low_pipeIm);
painter.drawImage(lower_pipe, low_pipeIm);

}
