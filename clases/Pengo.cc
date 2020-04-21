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
  //entity.setSprite(0,0);
  
  destination=0;
  pushing=false;
  dying=false;
  maxMoveTimer=8000;
  
  entity.changeSpeed(100.0f);

  facing=4; //mirando hacia abajo

  //Animaciones
  entity.getAnimacion()->reset();

  animIdleDerecha[0][0] = 0; animIdleDerecha[0][1] = 0; 
  animIdleDerecha[1][0] = 0; animIdleDerecha[1][1] = 0; 
  animIdleDerecha[2][0] =-1; animIdleDerecha[2][1] =-1; 

  animIdleArriba[0][0] = 2; animIdleArriba[0][1] = 0; 
  animIdleArriba[1][0] = 2; animIdleArriba[1][1] = 0; 
  animIdleArriba[2][0] =-1; animIdleArriba[2][1] =-1; 

  animIdleAbajo[0][0] = 3; animIdleAbajo[0][1] = 0; 
  animIdleAbajo[1][0] = 3; animIdleAbajo[1][1] = 0; 
  animIdleAbajo[2][0] =-1; animIdleAbajo[2][1] =-1; 

  animAndarDerecha[0][0] = 0; animAndarDerecha[0][1] = 0;
  animAndarDerecha[1][0] = 1; animAndarDerecha[1][1] = 0;
  animAndarDerecha[2][0] =-1; animAndarDerecha[2][1] =-1;

  animAndarAbajo[0][0] = 3; animAndarAbajo[0][1] = 1;
  animAndarAbajo[1][0] = 3; animAndarAbajo[1][1] = 0;
  animAndarAbajo[2][0] =-1; animAndarAbajo[2][1] =-1;

  animAndarArriba[0][0] = 2; animAndarArriba[0][1] = 1;
  animAndarArriba[1][0] = 2; animAndarArriba[1][1] = 0;
  animAndarArriba[2][0] =-1; animAndarArriba[2][1] =-1;

  animEmpujarDerecha[0][0] = 4; animEmpujarDerecha[0][1] = 0;
  animEmpujarDerecha[1][0] = 5; animEmpujarDerecha[1][1] = 0;
  animEmpujarDerecha[2][0] = 4; animEmpujarDerecha[2][1] = 0;
  animEmpujarDerecha[3][0] = 5; animEmpujarDerecha[3][1] = 0;
  animEmpujarDerecha[4][0] =-1; animEmpujarDerecha[4][1] =-1;

  animEmpujarArriba[0][0] = 8; animEmpujarArriba[0][1] = 0;
  animEmpujarArriba[1][0] = 9; animEmpujarArriba[1][1] = 0;
  animEmpujarArriba[2][0] = 8; animEmpujarArriba[2][1] = 0;
  animEmpujarArriba[3][0] = 9; animEmpujarArriba[3][1] = 0;
  animEmpujarArriba[4][0] =-1; animEmpujarArriba[4][1] =-1;

  animEmpujarAbajo[0][0] = 6; animEmpujarAbajo[0][1] = 0;
  animEmpujarAbajo[1][0] = 7; animEmpujarAbajo[1][1] = 0;
  animEmpujarAbajo[2][0] = 6; animEmpujarAbajo[2][1] = 0;
  animEmpujarAbajo[3][0] = 7; animEmpujarAbajo[3][1] = 0;
  animEmpujarAbajo[4][0] =-1; animEmpujarAbajo[4][1] =-1;

  animMorir[0][0] = 0;   animMorir[0][1] = 1;
  animMorir[1][0] = 1;   animMorir[1][1] = 1;
  animMorir[2][0] = 0;   animMorir[2][1] = 1;
  animMorir[3][0] = 1;   animMorir[3][1] = 1;
  animMorir[4][0] = 0;   animMorir[4][1] = 1;
  animMorir[5][0] = 1;   animMorir[5][1] = 1;
  animMorir[6][0] = 0;   animMorir[6][1] = 1;
  animMorir[7][0] = 1;   animMorir[7][1] = 1;
  animMorir[8][0] = 0;   animMorir[8][1] = 1;
  animMorir[9][0] = 1;   animMorir[9][1] = 1;
  animMorir[10][0] = 0; animMorir[10][1] = 1;
  animMorir[11][0] = 1; animMorir[11][1] = 1;
  animMorir[12][0] =-1; animMorir[12][1] =-1;


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
  if( entity.getMovingState() != 0 || pushing || dying){
    return false;
  }

  GameManager* game = GameManager::instancia();

  facing = direction;
  
  switch (direction)
  {
  case 1:
    destination = entity.getX() + game->getUnitW();
    entity.getAnimacion()->setSecuencia(animAndarDerecha);
  break;

  case 2:
    destination = entity.getY() - game->getUnitH();
    entity.getAnimacion()->setSecuencia(animAndarArriba);
  break;

  case 3:
    destination = entity.getX() - game->getUnitW();
    entity.getAnimacion()->setSecuencia(animAndarDerecha);
  break;

  case 4:
    destination = entity.getY() + game->getUnitH();
    entity.getAnimacion()->setSecuencia(animAndarAbajo);
  break;
  
  default:
    break;
  }

  return entity.move(direction);
}

void Pengo::update(){
  GameManager* game = GameManager::instancia();



  entity.update();
  if(entity.getKillme()) killme=true;

  

  //MOVIMIENTO
  if(!entity.getMovingState() && !pushing && !dying){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
      facing=1;
        //entity.setSprite(0,0);
        entity.getSprite()->setScale(1,1);
      if(game->canMove(1)){
        move(1);
      }
    } else
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
      facing=2;
        //entity.setSprite(2,0);
        entity.getSprite()->setScale(1,1);
      if(game->canMove(2)){
        move(2);
      }
    } else
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
      facing=3;
        //entity.setSprite(0,0);
        entity.getSprite()->setScale(-1,1);
      if(game->canMove(3)){
        move(3);
      }
    } else
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
      //entity.setSprite(3,0);
      entity.getSprite()->setScale(1,1);
      facing=4;
      if(game->canMove(4)){
        move(4);
      }
    }
  }



  //Parar si hemos llegado a la siguiente casilla
  stopCheck();
  
  /*for(int i=0; i<maxAnimationFrames; i++){
    std::cout<< anim->getSecuencia(i,0) <<" - " << anim->getSecuencia(i,1) << " ///// ";
    if(anim->getSecuencia(i,0)==-1){
      std::cout<<std::endl;
      break;
    } 
  }*/
  //std::cout<< anim->getIteracion() << " ----- " << anim->getCurrentColumn() << " ----- " << anim->getCurrentRow() <<std::endl;
}

void Pengo::stopCheck(){
  if(!dying){
      switch (entity.getMovingState())
  {
  case 0:
    if(pushing) break;
    if(entity.getAnimacion()==NULL) break;
    entity.getAnimacion()->reset();
    switch(facing){
      case 1: entity.getAnimacion()->setSecuencia(animIdleDerecha); break;
      case 2: entity.getAnimacion()->setSecuencia(animIdleArriba); break;
      case 3: entity.getAnimacion()->setSecuencia(animIdleDerecha); entity.getSprite()->setScale(-1,1); break;
      case 4: entity.getAnimacion()->setSecuencia(animIdleAbajo); break;
      default: break;
    }

  break;
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

}

void Pengo::morir(){
    GameManager* game = GameManager::instancia();
    game->perderVida();

    if(game->getVidas()>0){
      game->respawnPengo();
    } else{
      game->gameOver();
    }

}

//GET
Entity* Pengo::asEntity(){
    Entity* este = &entity;
    return este;
}

void Pengo::setPushing(bool push){
  pushing=push;
}

void Pengo::iniciarMuerte(){
  if(!dying){
    dying=true;
    entity.impairMovement();
    Animacion* anim = entity.getAnimacion();
    anim->reset();
    anim->setSecuencia(animMorir);
    anim->setBehavior(4);
    
  }
  
}
