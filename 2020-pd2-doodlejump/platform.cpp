#include "platform.h"
#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

void Platform::move_stage(){
    if(distance>=0){
        if(touch_rocket!=1){
            distance-=2;
            setPos(x(), y() + 2);
        }
        else{
            distance-=2;
            setPos(x(), y() + 4);
        }
    }
    else if(distance<0){
        touch_rocket=0;
    }
    if(y() > 720){
        set_new_stage=1;
    }
}
