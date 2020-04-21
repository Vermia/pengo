#include "Animacion.h"
#include "GameManager.h"

//CANON
Animacion::Animacion(){
    iteracion=0;
    behavior=1;
    maxTimer=0.175;

    for(int i=0; i<maxAnimationFrames ; i++){
        for(int j=0 ; j<2 ; j++){
            secuencia[i][0] = -1;
            secuencia[i][1] = -1;
        }
    }
    secuencia[0][1] = 0;
    secuencia[1][1] = 0;

    secuencia[2][1] = 0;
    secuencia[3][1] = 0;
}

Animacion::Animacion(float p_maxTimer){
    iteracion=0;
    behavior=1;
    maxTimer=p_maxTimer;

    for(int i=0; i<maxAnimationFrames ; i++){
        for(int j=0 ; j<2 ; j++){
            secuencia[i][j] = -1;
        }
    }
}

Animacion::~Animacion(){

}

//FUNCTIONALITY
void Animacion::update(){
    if(timer<=maxTimer){
        GameManager* game = GameManager::instancia();
        float deltaTime = game->deltaTime;

        currentColumn = secuencia[iteracion][0];
        currentRow    = secuencia[iteracion][1];
        
        timer -= deltaTime;
        //if(behavior==2) std::cout<<timer<<std::endl;
        if(timer <= 0){
            advance();
            restartTimer();
        }
    } else timer = maxTimer; //Esto es para quickfixear un bug que causa que "timer" sea NaN,
                             //y que por tanto la animacion se pare.
}

void Animacion::advance(){
    iteracion++;
    if(iteracion >= maxAnimationFrames) iteracion=0;

    currentColumn = secuencia[iteracion][0];
    currentRow    = secuencia[iteracion][1];

    
}

void Animacion::reset(){
    iteracion=0;
    currentColumn=0;
    currentRow=0;

    for(int i=0; i<maxAnimationFrames ; i++){
        for(int j=0 ; j<2 ; j++){
            secuencia[i][j] = -1;
        }
    }
}

void Animacion::setSecuencia(int (&p_secuencia)[maxAnimationFrames][2]){
    for (int i = 0; i < maxAnimationFrames; i++){
            secuencia[i][0] = p_secuencia[i][0];
            secuencia[i][1] = p_secuencia[i][1];
    }
    
}

void Animacion::restartTimer(){
    timer=maxTimer;
}