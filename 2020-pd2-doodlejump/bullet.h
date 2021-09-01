#ifndef BULLET_H
#define BULLET_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>

class bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    bullet(){}

public slots:
    void fly();
};

#endif // BULLET_H
