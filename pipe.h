#ifndef PIPE_H
#define PIPE_H

#include <QPainter>
#include <QImage>

class Pipe : public QObject
{
    Q_OBJECT

public:
    Pipe(QPoint& center);
    void create_pipe(QPainter& painter, QImage& image);

    QRect upper_pipe;
    QRect lower_pipe;

private:

QPoint center;
};


#endif // PIPE_H
