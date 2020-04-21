#ifndef HUEVO_H
#define HUEVO_H

#pragma once
#include "Entity.h"
#include "Hielo.h"
using namespace sf;

class Huevo
{
private:
    static sf::Texture* textura;
    Entity entity;
    int animNacer[maxAnimationFrames][2];

    Timer birthTimer;
public:
    //CANON
    Huevo(float p_x, float p_y);
    ~Huevo();

    //FUNCTIONALITY
    void update();
    static bool giveTexture(String file);
    void draw(RenderWindow &window);

    //GET


    //SET


};



#endif 