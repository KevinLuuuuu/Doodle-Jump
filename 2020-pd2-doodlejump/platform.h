#ifndef PLATFORM_H
#define PLATFORM_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QObject>

class Platform : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Platform(){}
    double distance=0.0;
    int move=0;
    int set_new_stage=0;
    int platform_num;
    int spring_platform=0;
    int rocket_platform=0;
    int star_platform=0;
    int touch_rocket=0;
public slots:
    void move_stage();

};

#endif // PLATFORM_H
