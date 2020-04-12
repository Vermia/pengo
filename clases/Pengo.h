#ifndef PENGO_H
#define PENGO_H

#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"


class Pengo
{
private:
    static sf::Texture* textura;

    Entity entity;
    int maxMoveTimer;
    int facing;
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
    void morir();

    //GET
    Entity asEntity();
    int getFacing(){return facing;}
    bool getKillme(){return killme;}
    static sf::Texture* getTextura(){return textura;};


    //SET
    void face(int direction){facing=direction;}
};

#endif