#include "gamer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Gamer::Gamer(){
    srand( static_cast<unsigned int>(time(nullptr)));
}

void Gamer::get_pause(){
    if(pause==0){
        pause=1;
    }
    else {
        pause=0;
    }
}

void Gamer::jump(){
    static int count;
    //static int touch_platform;
    if(pause!=1){
        if(count<100){

            if(monster->touch_rocket==0){
                if(distance<=60)
                    setPos(x(), y() - 2);
                else
                    setPos(x(), y() - num_of_minus);
            }
            else
               setPos(x(), y() - 0.5);

            if(x()<370){
                setPos(770, y());
            }
            else if(x()>770){
                setPos(380, y());
            }
            if(y() >= rocket->y() && y() <= rocket->y()+5
                    && x()+20 >= rocket->x() && x()+20 <= rocket->x()+30){
                for(string::size_type j=0;j<maps.size();j++){
                    maps.at(j)->touch_rocket=1;
                }
                count=-100;
                for(string::size_type j=0;j<maps.size();j++){
                    maps.at(j)->distance=400;
                    maps.at(j)->move=1;
                }
                rocket->distance=400;
                spring->distance=400;
                monster->distance=400;
                blackhole->distance=400;
                star->distance=400;
                monster->touch_rocket=1;
                star->touch_rocket=1;
                blackhole->touch_rocket=1;
                spring->touch_rocket=1;
                rocket->touch_rocket=1;
                rocket->setPixmap(QPixmap(""));
                change_rocket=0;
                emit change_rocket_signal();
                change_rocket=1;
            }
            if(monster->touch_rocket==0 && y() + 45 >= star->y() && y() + 45  <= star->y()+5
                    && x()+20 >= star->x() && x()+20 <= star->x()+30){
                invincible_state=1;
                star->setPos(0, 0);
                change_rocket=3;
                emit change_rocket_signal();
            }
            count++;
        }
        else{
            distance=0;
            if(change_rocket==1){
                emit change_rocket_signal();
                change_rocket=0;
            }
            setPos(x(), y() + 2);
            if(x()<370){
                setPos(770, y());
            }
            else if(x()>770){
                setPos(380, y());
            }
            for(string::size_type i = 0;i < maps.size();i++){
                if(y() + 45 >= spring->y() && y() + 45  <= spring->y()+5
                        && x()+20 >= spring->x() && x()+20 <= spring->x()+30){
                    count=-50;
                    for(string::size_type j=0;j<maps.size();j++){
                        maps.at(j)->distance=300;
                        maps.at(j)->move=1;
                    }
                    //touch_platform=1;
                    spring->distance=300;
                    rocket->distance=300;
                    monster->distance=300;
                    blackhole->distance=300;
                    star->distance=300;
                    spring->setPixmap(QPixmap(":/pic/spring-extend.png").scaled(25, 40));
                    spring->setPos(spring->x()+5, spring->y()-13);
                    break;
                }
                if(y() + 45 >= rocket->y() && y() + 45  <= rocket->y()+5
                        && x()+20 >= rocket->x() && x()+20 <= rocket->x()+30){
                    for(string::size_type j=0;j<maps.size();j++){
                        maps.at(j)->touch_rocket=1;
                    }
                    count=-100;
                    distance=400;
                    for(string::size_type j=0;j<maps.size();j++){
                        maps.at(j)->distance=distance;
                        maps.at(j)->move=1;
                    }
                    rocket->distance=distance;
                    spring->distance=distance;
                    monster->distance=distance;
                    blackhole->distance=distance;
                    star->distance=distance;
                    spring->touch_rocket=1;
                    rocket->touch_rocket=1;
                    monster->touch_rocket=1;
                    star->touch_rocket=1;
                    blackhole->touch_rocket=1;
                    rocket->setPixmap(QPixmap(""));
                    change_rocket=0;
                    emit change_rocket_signal();
                    change_rocket=1;
                    break;
                }
                if(monster->touch_rocket==0 && y() + 45 >= star->y() && y() + 45  <= star->y()+5
                        && x()+20 >= star->x() && x()+20 <= star->x()+30){
                    change_rocket=3;
                    invincible_state=1;
                    star->setPos(0, 0);
                    emit change_rocket_signal();
                    break;
                }
                if(y() + 45 >= maps.at(i)->y() - 5 && y() + 45  <= maps.at(i)->y() + 5
                   && x()+20 >= maps.at(i)->x() && x()+20 <= maps.at(i)->x() + 70 && maps.at(i) -> platform_num != 1){
                    //count=0;
                    distance=700-maps.at(i)->y();
                    count = (int) distance / 2;
                    if(count>30){
                        num_of_minus=(200 - (int)distance)/count;
                        count=100-count;
                    }
                    else {
                        count=0;
                    }
                    /*if(distance>0){
                        touch_platform=0;//people not move
                    }
                    else
                        touch_platform=2;*/
                    for(string::size_type j=0;j<maps.size();j++){
                        maps.at(j)->distance=distance;
                        maps.at(j)->move=1;
                    }
                    spring->distance=distance;
                    spring->move=1;
                    rocket->distance=distance;
                    rocket->move=1;
                    monster->distance=distance;
                    blackhole->distance=distance;
                    star->distance=distance;
                }
            }
        }
        while(maps.at(0)->set_new_stage==1){//roll the map
            if(gamerstate==0)
                scores+=200;
            emit Plus_signal();
            posX=rand() % 300+420;
            posY=maps.at(19)->y() - rand() % 14 - 40;
            maps.at(0)->setPos(posX, posY);
            maps.at(0)->set_new_stage=0;
            if(maps.at(0)->spring_platform==1){
                spring->setPixmap(QPixmap(":/pic/spring.png").scaled(30, 25));
                spring->setPos(posX+20, posY-25);
            }
            else if(maps.at(0)->rocket_platform==1){
                rocket->setPixmap(QPixmap(":/pic/rocket.png").scaled(25, 30));
                rocket->setPos(posX+20, posY-25);
            }
            else if(maps.at(0)->star_platform==1){
                star->setPixmap(QPixmap(":/pic/star.png").scaled(25, 30));
                star->setPos(posX+20, posY-25);
            }
            maps.push_back(maps.at(0));
            maps.erase(maps.begin());
        }
        if(monster->set_new_stage==1){
            posX=rand() % 300+420;
            posY=300 - rand() % 1700;
            monster->setPos(posX, posY);
            monster->set_new_stage=0;
        }
        if(blackhole->set_new_stage==1){
            posX=rand() % 300+420;
            posY=300 - rand() % 1700;
            blackhole->setPos(posX, posY);
            blackhole->set_new_stage=0;
        }
    }
    if(monster->touch_rocket==0){
        if(y()>720 || ((y()+45 < monster->y()+60 && y()+45 > monster->y()
                       && x()+20 >= monster->x() && x()+20 <= monster->x() + 60) ||
                       (y() < monster->y() + 60 && y() > monster->y()
                       && x()+20 >= monster->x() && x()+20 <= monster->x() + 60) ||
                       (invincible_state==0 &&
                       ((y()+45 < blackhole->y()+60 && y()+45 > blackhole->y()
                       && x()+20 >= blackhole->x() && x()+20 <= blackhole->x() + 60) ||
                       (y() < blackhole->y() + 60 && y() > blackhole->y()
                       && x()+20 >= blackhole->x() && x()+20 <= blackhole->x() + 60))))){
                        game_over->setPixmap(QPixmap(":/pic/game_over.jpg").scaled(400, 200));
                        game_over->setPos(400, 250);
                        for(string::size_type i=0;i<maps.size();i++){
                            maps.at(i)->setScale(0);
                        }
                        gamerstate=1;
                        monster->setScale(0);
                        star->setScale(0);
                        blackhole->setScale(0);
                        spring->setScale(0);
                        rocket->setScale(0);
                        change_rocket=2;//die
                        emit change_rocket_signal();
        }
    }
}
