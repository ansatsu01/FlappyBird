#include "bird.h"

Bird::Bird(QPoint& for_bird){

birdy.setX(for_bird.x());
birdy.setY(for_bird.y());
}

void Bird::create_bird(QPainter& painter){

    QImage bird_Im("D:/Viktoria/BSU/programming/yellowbird-midflap1.png", "PNG");   //bird :  56x41

    painter.drawImage(birdy, bird_Im);
}


