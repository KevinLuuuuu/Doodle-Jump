#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <QLabel>
#include <QTimer>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(0, 0, 1201, 871)),
    timer(new QTimer),
    player_timer(new QTimer),
    stage_timer(new QTimer)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);

    ui->myscores->setStyleSheet("QLabel{ color: yellow; font: 18pt; font-weight:700; }");
    g->scores=0;
    ui->myscores->setNum(g->scores);

    timer->start(5);
    player_timer->start(7);
    stage_timer->start(7);

    g->setPixmap(QPixmap(":/pic/mario.png").scaled(40, 60));
    back_ground->setPixmap(QPixmap(":/pic/background.png").scaled(600, 700));
    scene->addItem(static_cast<QGraphicsPixmapItem*>(back_ground));
    back_ground->setPos(400, 130);
    //scene->addItem(g);
    //g->setPos(500, 500);
    scene->addItem(static_cast<QGraphicsPixmapItem*>(g));
    scene->addItem(static_cast<QGraphicsPixmapItem*>(g->game_over));
    print_map();
    print_monster();
    g->connect(player_timer, SIGNAL(timeout()), g, SLOT(jump()));

    connect(g, SIGNAL(Plus_signal()), this, SLOT(plus_score()));
    connect(ui->stop, SIGNAL(clicked()), g, SLOT(get_pause()));
    connect(ui->stop, SIGNAL(clicked()), this, SLOT(change_pause_pic()));
    connect(g, SIGNAL(change_rocket_signal()), this, SLOT(change_rocket()));
}

void MainWindow::shoot_monster(){
    for(unsigned int i=0;i<bullet_vec.size();i++){
        if(bullet_vec.at(i)->y() < g->monster->y()+60 && bullet_vec.at(i)->y() > g->monster->y()
           && (bullet_vec.at(i)->x()+ 50 >= g->monster->x() && bullet_vec.at(i)->x() <= g->monster->x()+60)){
            g->monster->setPos(1000, g->monster->y());
            //g->monster->set_new_stage=1;
            temp=bullet_vec.at(i);
            bullet_vec.erase(bullet_vec.begin()+i);
            scene->removeItem(temp);
            delete temp;
            break;
        }
        if(bullet_vec.at(i)->y()<0){
            temp=bullet_vec.at(i);
            bullet_vec.erase(bullet_vec.begin()+i);
            scene->removeItem(temp);
            delete temp;
        }

    }
}

void MainWindow::print_monster(){
    posX=rand() % 300+420;
    posY=300 - rand() % 1700;
    g->monster->setPos(posX, posY);
    g->monster->setPixmap(QPixmap(":/pic/venus.png").scaled(40, 60));
    scene->addItem(g->monster);
    g->monster->connect(stage_timer, SIGNAL(timeout()), g->monster, SLOT(move_stage()));

    posX=rand() % 300+420;
    posY=300 - rand() % 1700;
    g->blackhole->setPos(posX, posY);
    g->blackhole->setPixmap(QPixmap(":/pic/black-hole.png").scaled(40, 60));
    scene->addItem(g->blackhole);
    g->blackhole->connect(stage_timer, SIGNAL(timeout()), g->blackhole, SLOT(move_stage()));
}

void MainWindow::change_rocket(){
    if(g->change_rocket==0){
        g->setPixmap(QPixmap(":/pic/fire-rocket.png").scaled(30, 60));
    }
    else if(g->change_rocket==1){
        g->setPixmap(QPixmap(":/pic/mario.png").scaled(40, 60));
    }
    else if(g->change_rocket==2)
        g->setScale(0);
        //g->setPixmap(QPixmap(""));
    else if(g->change_rocket==3){
        g->setPixmap(QPixmap(":/pic/invincible-mario.png").scaled(40, 60));
        g->change_rocket=4;
        QTimer::singleShot(5000 , this, SLOT(change_rocket()));
    }
    else if(g->change_rocket==4){
        g->setPixmap(QPixmap(":/pic/mario.png").scaled(40, 60));
        //g->change_rocket=1;
        g->invincible_state=0;
    }

}

void MainWindow::change_pause_pic(){//feature
    if(g->pause==0){
        ui->stop->setIcon(QIcon(":/pic/stop.png"));
    }
    else {
        ui->stop->setIcon(QIcon(":/pic/start.png"));
    }
}

void MainWindow::plus_score(){
    ui->myscores->setNum(g->scores);
}

void MainWindow::print_map(){
    srand( static_cast<unsigned int>(time(nullptr)));
    posY=700;
    posX=rand() % 300+420;
    Platform *p = new Platform;
    g->setPos(posX, posY);
    p->setPos(posX, posY);
    p->setPixmap(QPixmap(":/pic/platform1.png").scaled(70, 10));
    scene->addItem(p);
    g->maps.push_back(p);
    g->maps.at(0)->connect(stage_timer, SIGNAL(timeout()), g->maps.at(0), SLOT(move_stage()));
    for(string::size_type i=0;i<19;i++){
        Platform *p = new Platform;
        posX=rand() % 300+420;
        posY-=rand() % 14+40;
        p->setPos(posX, posY);
        if(i==6||i==12||i==18){
            p->setPixmap(QPixmap(":/pic/platform2.png").scaled(70, 10));
            p->platform_num=1;
        }
        else{
            p->setPixmap(QPixmap(":/pic/platform1.png").scaled(70, 10));
            p->platform_num=0;
        }
        if(i==16){
            p->spring_platform=1;
            g->spring->setPixmap(QPixmap(":/pic/spring.png").scaled(30, 25));
            g->spring->setPos(posX+20, posY-25);
            scene->addItem(g->spring);
            g->spring->connect(stage_timer, SIGNAL(timeout()), g->spring, SLOT(move_stage()));
        }
        if(i==14){
            p->rocket_platform=1;
            g->rocket->setPixmap(QPixmap(":/pic/rocket.png").scaled(25, 30));
            g->rocket->setPos(posX+20, posY-25);
            scene->addItem(g->rocket);
            g->rocket->connect(stage_timer, SIGNAL(timeout()), g->rocket, SLOT(move_stage()));
        }
        if(i==17){
            p->star_platform=1;
            g->star->setPixmap(QPixmap(":/pic/star.png").scaled(25, 30));
            g->star->setPos(posX+20, posY-25);
            scene->addItem(g->star);
            g->star->connect(stage_timer, SIGNAL(timeout()), g->star, SLOT(move_stage()));
        }
        scene->addItem(p);
        g->maps.push_back(p);
        g->maps.at(i+1)->connect(stage_timer, SIGNAL(timeout()), g->maps.at(i+1), SLOT(move_stage()));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()) {

    case Qt::Key_Left:{
        if(g->pause==0)
            g->setPos(g->x() - 10, g->y());
        break;
    }
    case Qt::Key_Right:{
        if(g->pause==0)
            g->setPos(g->x() + 10, g->y());
        break;
    }
    case Qt::Key_Space:{
        if(g->pause==0 && g->gamerstate==0){
            bullet *b = new bullet;
            b->setPixmap(QPixmap(":/pic/fireball.png").scaled(50, 50));
            b->setPos(g->x() + g->pixmap().width() / 2 - g->pixmap().width() / 2, g->y() - b->pixmap().height());
            b->connect(timer, SIGNAL(timeout()), b, SLOT(fly()));
            b->connect(timer, SIGNAL(timeout()), this, SLOT(shoot_monster()));
            scene->addItem(static_cast<QGraphicsPixmapItem*>(b));
            bullet_vec.push_back(b);
        }
        break;
    }
    }

}


