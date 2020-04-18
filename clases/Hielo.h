#ifndef HIELO_H
#define HIELO_H

#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Snobee.h"
using namespace sf;

#define maxHuevos 3
class Snobee;

class Hielo
{
private:
    static  sf::Texture* textura;

    Entity entity;
    int maxMoveTimer;
    bool killme;
    FloatRect hitbox;
    RectangleShape hitboxV;
    bool huevo;
    bool dying;

    Snobee* host;
public:
    //CANON
    Hielo();
    Hielo(int p_x, int p_y);
    ~Hielo();

    //FUNCTIONALITY
    static bool giveTexture(String file);

    void draw(sf::RenderWindow &window) const;
    bool move(int direction); // 1: right, 2: up, 3:left, 4:down, resto: stop
    void destroy();
    void update();
    void updateHitbox();
    void eclosiona();

    //GET
    Entity* asEntity();
    bool getKillme(){return killme;}
    FloatRect getHitbox(){return hitbox;}
    RectangleShape getHitboxV(){return hitboxV;}
    static int totalHuevos;
    bool getHuevo(){return huevo;}
    bool isDying(){return dying;}
    Snobee* getHost(){return host;}

    static int animSerDestruido[maxAnimationFrames][2];
    static void initAnimaciones();


    //SET
    void tieneHuevo();
    void iniciarMuerte();
    void setHost(Snobee* p_host){host=p_host;}
};


#endif