#ifndef PENGO_H
#define PENGO_H

#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"


class Pengo
{
private:
    static sf::Texture* textura;
    int animAndarDerecha[maxAnimationFrames][2];
    int animAndarAbajo[maxAnimationFrames][2];
    int animAndarArriba[maxAnimationFrames][2];

    int animIdleDerecha[maxAnimationFrames][2];
    int animIdleArriba[maxAnimationFrames][2];
    int animIdleAbajo[maxAnimationFrames][2];
    
    

    Entity entity;
    int maxMoveTimer;
    int facing;
    bool pushing;
    bool dying;
    float destination;
    bool killme;
public:
    //CANON
    Pengo(int p_x, int p_y);
    ~Pengo();

    //FUNCTIONALITY
    static bool giveTexture(String file);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool move(int direction); // 1: right, 2: up, 3:left, 4:down, resto: stop
    void update();
    void draw(sf::RenderWindow &window);
    void stopCheck();
    void iniciarMuerte();
    void morir();
    

    //GET
    Entity* asEntity();
    int getFacing(){return facing;}
    bool getKillme(){return killme;}
    static sf::Texture* getTextura(){return textura;};

    int animEmpujarDerecha[maxAnimationFrames][2];
    int animEmpujarArriba[maxAnimationFrames][2];
    int animEmpujarAbajo[maxAnimationFrames][2];
    int animMorir[maxAnimationFrames][2];

    bool isDying(){return dying;}
    bool getPushing() {return pushing;}

    //SET
    void face(int direction){facing=direction;}
    void setPushing(bool);
};

#endif