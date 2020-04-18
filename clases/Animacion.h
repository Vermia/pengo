#pragma once

#define maxAnimationFrames 18

class Animacion
{
private:
    int iteracion;
    int secuencia[maxAnimationFrames][2]; 
    float timer;
    float maxTimer;

    int behavior; //0: Nada, 1: Loop, 2: Destroy, 3: pengo.pushing=false, 4: muerte de Pengo
                  

    int currentColumn;
    int currentRow;
public:
    //CANON
    Animacion();
    Animacion(float maxTimer);
    ~Animacion();

    //FUNCTIONALITY
    void update();
    void advance();
    void reset();

    //GET
    int getIteracion(){return iteracion;}
    int getSecuencia(int i,int j){return secuencia[i][j];}
    int getCurrentColumn(){{return currentColumn;}}
    int getCurrentRow(){{return currentRow;}}
    int getBehavior(){return behavior;}
    float getMaxTimer(){return maxTimer;}

    //SET
    void restartTimer();
    void setIteracion(int it){iteracion=it;}
    void setSecuencia(int (&p_secuencia)[18][2]);
    void setBehavior(int p_behavior){behavior=p_behavior;}
    void setMaxTimer(float p_max){maxTimer=p_max;}
};


