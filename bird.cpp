#include "bird.h"

Bird::Bird(QPoint& for_bird){

birdy.setX(for_bird.x());
birdy.setY(for_bird.y());
}

void Bird::create_bird(QPainter& painter, QImage* image){

   painter.drawImage(birdy, *image);
}


