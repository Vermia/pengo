#ifndef ENTITY_H
#define ENTITY_H

#pragma once
#include <SFML/Graphics.hpp>
#include "Animacion.h"
using namespace sf;

class Entity : public sf::Drawable
{
protected:
    float x;
    float y;
    int moving;
    int moveTimer;
    float movespeedX;
    float movespeedY;
    sf::Sprite* sprite;
    sf::Texture texture;
    bool killme;
    bool movementImpaired;
    
    Animacion* animacion;
    
public:
    //CANON
    Entity();
    Entity(float p_x, float p_y);
    Entity(float p_x, float p_y, sf::Texture &p_texture);
    ~Entity();

    //FUNCTIONALITY
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool move(int direction);
    void update();
    bool stop();
    void updateHitbox();
    void normalizePosition();

    void updateAnimacion();

    //GET
    sf::Sprite* getSprite(){return sprite;};
    float getX(){return sprite->getPosition().x; };
    float getY(){return sprite->getPosition().y; }; 
    int getMovingState(){return moving; };
    int getMoveTimer(){return moveTimer; };
    float getMovespeedX(){return movespeedX; };
    float getMovespeedY(){return movespeedY; };
    Animacion* getAnimacion(){return animacion;}
    bool getKillme(){return killme;}

    sf::FloatRect  hitboxLeft;
    sf::FloatRect  hitboxRight;
    sf::FloatRect  hitboxDown;
    sf::FloatRect  hitboxUp;
    RectangleShape hitboxTLV;
    RectangleShape hitboxTRV;
    RectangleShape hitboxBLV;
    RectangleShape hitboxBRV;

    //SET
    void setPosition(float p_x, float p_y);
    void changeSpeed(float p_speed);
    bool setSprite(unsigned int column, unsigned int row);
    bool setTexture(sf::String file);
    void impairMovement(){movementImpaired=true;}
};

#endif