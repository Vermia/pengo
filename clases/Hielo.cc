#include "Hielo.h"
#include "GameManager.h"

#define hieloSpeed 300.0f

int Hielo::totalHuevos=0;
sf::Texture* Hielo::textura = new sf::Texture();

bool Hielo::giveTexture(String file){
  return textura->loadFromFile(file);
}

//CANON
Hielo::Hielo(){
    maxMoveTimer=1500;
    killme=false;
    entity.changeSpeed(hieloSpeed);
    hitboxV.setFillColor(Color(0,0,255,128));
    huevo=false;
}

Hielo::Hielo(int p_x, int p_y) : entity(p_x, p_y){
  entity.getSprite()->setTexture(*textura, true);
  entity.setSprite(0,0);

  maxMoveTimer=1500;
  killme=false;
  entity.changeSpeed(hieloSpeed);
  hitboxV.setFillColor(Color(0,0,255,128));
  huevo=false;
}

Hielo::~Hielo(){
  if(huevo) totalHuevos--;
}


//FUNCTIONALITY
void Hielo::draw(sf::RenderWindow &window) const{
  window.draw(entity);
}

bool Hielo::move(int direction){
  return entity.move(direction);
} 

void Hielo::destroy(){
  killme=true;
}

void Hielo::update(){
  GameManager* game = GameManager::instancia();

  switch (entity.getMovingState())
  {
  case 1:
    if(game->coliHieloHielo(this, 1)){
      entity.stop();
    }
  break;

  case 2:
    if(game->coliHieloHielo(this, 2)){
      entity.stop();
    }
  break;

  case 3:
    if(game->coliHieloHielo(this, 3)){
      entity.stop();
    }
  break;

  case 4:
    if(game->coliHieloHielo(this, 4)){
      entity.stop();
    }
  break;
  
  default:break;
  }
  
  updateHitbox();
  
  entity.update();
}

void Hielo::updateHitbox(){
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

void Hielo::eclosiona(){
  GameManager *game =GameManager::instancia();
  if(huevo){
    for(int i=0;i<maxEnemies;i++){
      if(game->bees[i]==NULL){
        game->bees[i]=new Snobee(entity.getX(), entity.getY());
        destroy();
        break;
      }
    }
  }
}

//GET
Entity Hielo::asEntity(){
    return entity;
}

//SET
void Hielo::tieneHuevo(){
  huevo=true;
  Hielo::totalHuevos++;
  entity.setSprite(1,0);
}