#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>
#include <QKeyEvent>
#include <vector>
#include "bullet.h"
#include "gamer.h"
#include "platform.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void print_map();
    void print_monster();
    ~MainWindow();

public slots:
    virtual void keyPressEvent(QKeyEvent *e);
    void plus_score();
    void change_pause_pic();
    void change_rocket();
    void shoot_monster();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *player;
    QTimer *timer;
    QTimer *player_timer;
    QTimer *stage_timer;
    Gamer *g = new Gamer;
    Platform *back_ground = new Platform;
    Platform *score_board = new Platform;
    bullet* temp;
    vector <bullet*> bullet_vec;
    int posX;
    int posY;
};




#endif // MAINWINDOW_H
