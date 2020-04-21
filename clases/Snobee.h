#ifndef SNOBEE_H
#define SNOBEE_H
#pragma once
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Hielo.h"
#include "Timer.h"
using namespace sf;
class Hielo;

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
    int dying;
    bool stunned;
    float stunTimer;
    static const float maxStunTimer;
    Hielo* llevameContigo;
    bool naciendo;

    

    int animStun[maxAnimationFrames][2];
    int animNacer[maxAnimationFrames][2];
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
    void iniciarMuerte(Hielo*);
    void updateMuerte();
    void becomeStunned();
    void birth(Hielo*);
    void eclosiona();
    void updateBirth();
    bool clogged(int direction);
    bool allClogged();

//GET
    Entity* asEntity(){return &entity;} 
    bool getKillme(){return killme;}
    FloatRect getHitbox(){return hitbox;}
    RectangleShape getHitboxV(){return hitboxV;}
    int isDying(){return dying;}
    int getFacing(){return facing;}
    bool isStunned(){return stunned;}
    bool isBirthing(){return naciendo;}
    Hielo* getAnfitrion();


    int animAndarDerecha[maxAnimationFrames][2];
    int animAndarAbajo[maxAnimationFrames][2];
    int animAndarArriba[maxAnimationFrames][2];

    int animRomperDerecha[maxAnimationFrames][2];
    int animRomperArriba[maxAnimationFrames][2];
    int animRomperAbajo[maxAnimationFrames][2];
    
//SET
    void stopBirthing(){naciendo=false;}

};

#endif