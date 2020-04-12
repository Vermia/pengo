#include "Pengo.h"
#include <iostream>
#include "GameManager.h"
using namespace sf;
using namespace std;

sf::Texture* Pengo::textura = new Texture();

bool Pengo::giveTexture(String file){
  return textura->loadFromFile(file);
}

//CANON
Pengo::Pengo(int p_x, int p_y) : entity(p_x, p_y){

  entity.getSprite()->setTexture(*textura, true);
  entity.setSprite(0,0);
  
  destination=0;

  maxMoveTimer=8000;
  
  entity.changeSpeed(100.0f);

  facing=4; //mirando hacia abajo

}

Pengo::~Pengo(){
  
}

//FUNCTIONALITY
void Pengo::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw( entity , states);
}

void Pengo::draw(sf::RenderWindow &window){
  window.draw(entity);
}

bool Pengo::move(int direction){
  if( entity.getMovingState() != 0 ){
    return false;
  }

  GameManager* game = GameManager::instancia();

  facing = direction;
  
  switch (direction)
  {
  case 1:
    destination = entity.getX() + game->getUnitW();
  break;

  case 2:
    destination = entity.getY() - game->getUnitH();
  break;

  case 3:
    destination = entity.getX() - game->getUnitW();
  break;

  case 4:
    destination = entity.getY() + game->getUnitH();
  break;
  
  default:
    break;
  }

  return entity.move(direction);
}

void Pengo::update(){
  GameManager* game = GameManager::instancia();


  entity.update();

  if(game->coliPengoSnobee() && !game->godmode){
    morir();
  }

  //MOVIMIENTO
  if(!entity.getMovingState()){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
      facing=1;
        entity.setSprite(0,0);
        entity.getSprite()->setScale(1,1);
      if(game->canMove(1)){
        move(1);
      }
    } else
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
      facing=2;
        entity.setSprite(2,0);
        entity.getSprite()->setScale(1,1);
      if(game->canMove(2)){
        move(2);
      }
    } else
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
      facing=3;
        entity.setSprite(0,0);
        entity.getSprite()->setScale(-1,1);
      if(game->canMove(3)){
        move(3);
      }
    } else
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
      entity.setSprite(3,0);
      entity.getSprite()->setScale(1,1);
      facing=4;
      if(game->canMove(4)){
        move(4);
      }
    }
  }

  //Parar si hemos llegado a la siguiente casilla
  stopCheck();
  
}

void Pengo::stopCheck(){
switch (entity.getMovingState())
  {
  case 1:
    if(entity.getX() >= destination){
      entity.getSprite()->setPosition(destination, entity.getY());
      entity.stop();
    }
  break;

  case 2:
    if(entity.getY() <= destination){
      entity.getSprite()->setPosition(entity.getX(), destination);
      entity.stop();
    }
  break;

  case 3:
    if(entity.getX() <= destination){
      entity.getSprite()->setPosition(destination, entity.getY());
      entity.stop();
    }
  break;

  case 4:
    if(entity.getY() >= destination){
      entity.getSprite()->setPosition(entity.getX(), destination);
      entity.stop();
    }
  break;
  
  default: break;
  }
}

void Pengo::morir(){
    GameManager* game = GameManager::instancia();
    game->perderVida();

    entity.setPosition(game->getUnitW()/2 + game->getUnitW()*7,game->getUnitH()/2 + game->getUnitH()*7);
    entity.stop();
}

//GET
Entity Pengo::asEntity(){
    return entity;
}