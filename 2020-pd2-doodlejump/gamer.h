#ifndef GAMER_H
#define GAMER_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>
#include <vector>
#include "platform.h"

using namespace std;

class Gamer : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Gamer();
    vector <Platform*> maps;
    double distance=0.0;
    double posX;
    double posY;
    int scores=0;
    Platform *game_over=new Platform;
    Platform* spring=new Platform;
    Platform* rocket=new Platform;
    Platform* monster=new Platform;
    Platform* blackhole=new Platform;
    Platform* star=new Platform;
    int pause=0;
    int change_rocket=0;
    int invincible_state=0;
    int touch_platform=0;
    int num_of_minus=0;
    int gamerstate=0;//live

public slots:
    void jump();
    void get_pause();
signals:
    void Plus_signal();
    void change_rocket_signal();

};


#endif // GAMER_H
