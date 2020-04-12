#pragma once
#include <SFML/Graphics.hpp>

#include "Entity.h"
using namespace sf;

class Snobee
{
private:
    static sf::Texture* textura;

    Entity entity;
    bool killme;
    FloatRect hitbox;
    RectangleShape hitboxV;
    float destination;
    int facing;
public:
//CANON
    Snobee();
    Snobee(float, float);
    Snobee(const Snobee&);
    ~Snobee();
//FUNCTIONALITY
    static bool giveTexture(String file);

    void draw(RenderWindow& window);
    void update();
    bool move(int);
    void destroy();
    void stopCheck();
    void updateHitbox();

//GET
    Entity asEntity(){return entity;}
    bool getKillme(){return killme;}
    FloatRect getHitbox(){return hitbox;}
    RectangleShape getHitboxV(){return hitboxV;}
    
//SET

};

