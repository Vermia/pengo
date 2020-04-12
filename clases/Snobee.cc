#include "Snobee.h"

#include "GameManager.h"

#define enemySpeed 30.0f

sf::Texture* Snobee::textura = new sf::Texture();

bool Snobee::giveTexture(String file){
  return textura->loadFromFile(file);
}

//CANON

Snobee::Snobee(){
    entity.getSprite()->setTexture(*textura, true);
    entity.setSprite(0,0);
    killme=false;

    entity.changeSpeed(enemySpeed);
    hitboxV.setFillColor(Color(255,0,0,128));
}

Snobee::Snobee(float p_x, float p_y) : entity(p_x, p_y){
    entity.getSprite()->setTexture(*textura, true);
    entity.setSprite(0,0);
    killme=false;

    hitboxV.setFillColor(Color(255,0,0,128));
    entity.changeSpeed(enemySpeed);

}

Snobee::~Snobee(){

}

void Snobee::draw(RenderWindow &window){
    window.draw(entity);
}

void Snobee::update(){
    entity.update();

    if(!entity.getMovingState()){
      int direction = rand()%4+1;
        move(direction);
    }

    stopCheck();

    updateHitbox();
}

void Snobee::updateHitbox(){
    GameManager* game = GameManager::instancia();
    float uw = game->getUnitW();
    float uh = game->getUnitH();
    Vector2f pos = entity.getSprite()->getPosition();
    float cota = 5.0f;

    hitbox.left = pos.x - uw/2 + cota;
    hitbox.top = pos.y - uh/2 + cota;
    hitbox.width = uw - 2*cota;
    hitbox.height = uh - 2*cota;

    hitboxV.setPosition(hitbox.left, hitbox.top);
    hitboxV.setSize(Vector2f(hitbox.width, hitbox.height));
}

void Snobee::destroy(){
    killme=true;
}

void Snobee::stopCheck(){
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

bool Snobee::move(int direction){
  if( entity.getMovingState() != 0 ){
    return false;
  }

  GameManager* game = GameManager::instancia();

  facing = direction;
  
  switch (direction)
  {
  case 1:
    destination = entity.getX() + game->getUnitW();
    entity.setSprite(0,0);
    entity.getSprite()->setScale(1,1);
  break;

  case 2:
    destination = entity.getY() - game->getUnitH();
    entity.setSprite(2,0);
    entity.getSprite()->setScale(1,1);
  break;

  case 3:
    destination = entity.getX() - game->getUnitW();
    entity.setSprite(0,0);
    entity.getSprite()->setScale(-1,1);
  break;

  case 4:
    destination = entity.getY() + game->getUnitH();
    entity.setSprite(2,1);
    entity.getSprite()->setScale(1,1);
  break;
  
  default:
    break;
  }

  return entity.move(direction);
}