#include "Timer.h"
#include "GameManager.h"

Timer::Timer(){
    max=5.0f;
}

Timer::Timer(float p_max){
    max=p_max;
}

Timer::~Timer(){

}

float Timer::advance(){
    GameManager* game = GameManager::instancia();
    if(current>0){
        current -= game->deltaTime;
    }else current = 0;
    
    return current;
}

float Timer::reset(){
    float aux=current;
    current = max;
    return aux;
}
