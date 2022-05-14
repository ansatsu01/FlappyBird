#ifndef BIRD_H
#define BIRD_H

#include <QPainter>
#include <QImage>

class Bird : public QObject
{
    Q_OBJECT

public:

Bird(QPoint& for_bird);
void create_bird(QPainter& painter, QImage* image);

private:
QPoint birdy;

};

#endif // BIRD_H
