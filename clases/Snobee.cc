#include "Snobee.h"

#include "GameManager.h"

#define enemySpeed 90.0f

sf::Texture* Snobee::textura = new sf::Texture();
const float Snobee::maxStunTimer = 12.5f;

bool Snobee::giveTexture(String file){
  return textura->loadFromFile(file);
}

//CANON

Snobee::Snobee(){
    entity.getSprite()->setTexture(*textura, true);
    entity.setSprite(0,0);
    dying=0;
    llevameContigo=NULL;
    killme=false;
    stunned=false;
    stunTimer=maxStunTimer;
    naciendo=false;
    entity.changeSpeed(enemySpeed);
    hitboxV.setFillColor(Color(255,0,0,128));

   entity.getAnimacion()->reset();


    animAndarDerecha[0][0] = 0; animAndarDerecha[0][1] = 0;
    animAndarDerecha[1][0] = 1; animAndarDerecha[1][1] = 0;
    animAndarDerecha[2][0] =-1; animAndarDerecha[2][1] =-1;

    animAndarAbajo[0][0] = 2; animAndarAbajo[0][1] = 1;
    animAndarAbajo[1][0] = 3; animAndarAbajo[1][1] = 1;
    animAndarAbajo[2][0] =-1; animAndarAbajo[2][1] =-1;

    animAndarArriba[0][0] = 2; animAndarArriba[0][1] = 0;
    animAndarArriba[1][0] = 3; animAndarArriba[1][1] = 0;
    animAndarArriba[2][0] =-1; animAndarArriba[2][1] =-1;

    animRomperDerecha[0][0] = 0; animRomperDerecha[0][1] = 2;
    animRomperDerecha[1][0] = 1; animRomperDerecha[1][1] = 2;
    animRomperDerecha[2][0] =-1; animRomperDerecha[2][1] =-1;

    animRomperAbajo[0][0] = 2; animRomperAbajo[0][1] = 3;
    animRomperAbajo[1][0] = 3; animRomperAbajo[1][1] = 3;
    animRomperAbajo[2][0] =-1; animRomperAbajo[2][1] =-1;

    animRomperArriba[0][0] = 2; animRomperArriba[0][1] = 2;
    animRomperArriba[1][0] = 3; animRomperArriba[1][1] = 2;
    animRomperArriba[2][0] =-1; animRomperArriba[2][1] =-1;

    animNacer[0][0] = 4; animNacer[0][1] = 0;
    animNacer[1][0] = 5; animNacer[1][1] = 0;
    animNacer[2][0] = 6; animNacer[2][1] = 0;
    animNacer[3][0] =-1; animNacer[3][1] =-1;
}

Snobee::Snobee(float p_x, float p_y) : entity(p_x, p_y){
    entity.getSprite()->setTexture(*textura, true);
    entity.setSprite(0,0);
    killme=false;
    dying=0;
    stunTimer=maxStunTimer;
    naciendo=false;

    hitboxV.setFillColor(Color(255,0,0,128));
    entity.changeSpeed(enemySpeed);
    stunned=false;
    //Animaciones
   entity.getAnimacion()->reset();


    animAndarDerecha[0][0] = 0; animAndarDerecha[0][1] = 0;
    animAndarDerecha[1][0] = 1; animAndarDerecha[1][1] = 0;
    animAndarDerecha[2][0] =-1; animAndarDerecha[2][1] =-1;

    animAndarAbajo[0][0] = 2; animAndarAbajo[0][1] = 1;
    animAndarAbajo[1][0] = 3; animAndarAbajo[1][1] = 1;
    animAndarAbajo[2][0] =-1; animAndarAbajo[2][1] =-1;

    animAndarArriba[0][0] = 2; animAndarArriba[0][1] = 0;
    animAndarArriba[1][0] = 3; animAndarArriba[1][1] = 0;
    animAndarArriba[2][0] =-1; animAndarArriba[2][1] =-1;

    animRomperDerecha[0][0] = 0; animRomperDerecha[0][1] = 2;
    animRomperDerecha[1][0] = 1; animRomperDerecha[1][1] = 2;
    animRomperDerecha[2][0] =-1; animRomperDerecha[2][1] =-1;

    animRomperAbajo[0][0] = 2; animRomperAbajo[0][1] = 3;
    animRomperAbajo[1][0] = 3; animRomperAbajo[1][1] = 3;
    animRomperAbajo[2][0] =-1; animRomperAbajo[2][1] =-1;

    animRomperArriba[0][0] = 2; animRomperArriba[0][1] = 2;
    animRomperArriba[1][0] = 3; animRomperArriba[1][1] = 2;
    animRomperArriba[2][0] =-1; animRomperArriba[2][1] =-1;

    animStun[0][0] = 0; animStun[0][1] = 1;
    animStun[1][0] = 1; animStun[1][1] = 1;
    animStun[2][0] =-1; animStun[2][1] =-1;

    animNacer[0][0] = 4; animNacer[0][1] = 0;
    animNacer[1][0] = 5; animNacer[1][1] = 0;
    animNacer[2][0] = 6; animNacer[2][1] = 0;
    animNacer[3][0] =-1; animNacer[3][1] =-1;

    
}

Snobee::~Snobee(){
  GameManager* game = GameManager::instancia();
  if(game->pengo!=NULL && !game->pengo->isDying()){
    if(!naciendo){
      if(stunned){
        game->incrementarPuntos(100);
      }else{
        game->incrementarPuntos(400);
      }
    }
    
  }
}

void Snobee::draw(RenderWindow &window){
    window.draw(entity);
}

void Snobee::update(){
  GameManager* game = GameManager::instancia();
    if(!dying && !stunned && !naciendo && !allClogged()){
        if(!entity.getMovingState()){

        int direction = rand()%4+1;
        while (clogged(direction)){
          direction = rand()%4+1;
        }
        move(direction);
      }
      entity.update();
    } 

    //ATURDIDO
    if(stunned){
      entity.updateAnimacion();
      stunTimer -= game->deltaTime;
      if(stunTimer <= 0){
        stunTimer = maxStunTimer;
        stunned=false;
      } 
      //entity.getSprite()->setColor(Color(0,0,255));
    } else{
      //entity.getSprite()->setColor(Color(0,255,0));
    }

    //MORIR
    if(dying && llevameContigo!=NULL && llevameContigo->asEntity()!=NULL){
      updateMuerte();
    }

    if(naciendo){
      entity.impairMovement();
      updateBirth();
    }

    //std::cout<< entity.getAnimacion()->getIteracion()<< " ----- "<< entity.getAnimacion()->getCurrentColumn()<< " ----- " << entity.getAnimacion()->getCurrentRow()<<std::endl;

    

    

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
  float snobeeSpeed = 45.0f;
  GameManager* game = GameManager::instancia();

  facing = direction;
  
  switch (direction)
  {
  case 1:
    destination = entity.getX() + game->getUnitW();
    entity.getAnimacion()->setSecuencia(animAndarDerecha);
    entity.changeSpeed(snobeeSpeed);
    entity.getSprite()->setScale(1,1);
  break;

  case 2:
    destination = entity.getY() - game->getUnitH();
    entity.getAnimacion()->setSecuencia(animAndarArriba);
    entity.changeSpeed(snobeeSpeed);
    entity.getSprite()->setScale(1,1);
  break;

  case 3:
    destination = entity.getX() - game->getUnitW();
    entity.getAnimacion()->setSecuencia(animAndarDerecha);
    entity.changeSpeed(snobeeSpeed);
    entity.getSprite()->setScale(-1,1);
  break;

  case 4:
    destination = entity.getY() + game->getUnitH();
    entity.getAnimacion()->setSecuencia(animAndarAbajo);
    entity.changeSpeed(snobeeSpeed);
    entity.getSprite()->setScale(1,1);
  break;
  
  default:
    break;
  }

  return entity.move(direction);
}

void Snobee::iniciarMuerte(Hielo* asesino){
  llevameContigo=asesino;
  float diffX = llevameContigo->asEntity()->getX() - entity.getX();
  float diffY = llevameContigo->asEntity()->getY() - entity.getY(); 
  float squishRatio= 0.25;

  if(abs(diffX)>abs(diffY)){
      
    if(diffX<0){
      dying=1;
      entity.getSprite()->setScale(squishRatio,1);
    } else if (diffX>0){
      dying=3;
      entity.getSprite()->setScale(squishRatio,1);
    }
  }else{
    if (diffY<0){
      dying=4;
      entity.getSprite()->setScale(1,squishRatio);
    } else if(diffY>0){
      entity.getSprite()->setScale(1,squishRatio);
      dying=2;
    }
  }

  
}

void Snobee::updateMuerte(){
  GameManager* game = GameManager::instancia();

  if(llevameContigo->asEntity()->getMovingState()!=0){
    switch(dying){
      case 1:
        entity.setPosition(llevameContigo->asEntity()->getX() + game->getUnitW()/2 ,llevameContigo->asEntity()->getY()  );
      break;

      case 2:
        entity.setPosition(llevameContigo->asEntity()->getX(),llevameContigo->asEntity()->getY() - game->getUnitH()/2 );
      break;
      
      case 3:
        entity.setPosition(llevameContigo->asEntity()->getX() - game->getUnitW()/2 ,llevameContigo->asEntity()->getY());
      break;

      case 4:
        entity.setPosition(llevameContigo->asEntity()->getX(),llevameContigo->asEntity()->getY() + game->getUnitH()/2 );
      break;
    }
  }else {
    destroy();
  }
}

void Snobee::becomeStunned(){
  if(!naciendo){
    stunned=true;
    entity.getAnimacion()->reset();
    entity.getAnimacion()->setSecuencia( animStun );
  }
}

void Snobee::birth(Hielo* lugar){
  naciendo=true;
  entity.getAnimacion()->reset();
  entity.getAnimacion()->setBehavior(5);
  entity.getAnimacion()->setSecuencia( animNacer );
  entity.getAnimacion()->setMaxTimer(5.0f);
  lugar->setHost(this);
}

void Snobee::updateBirth(){
  GameManager* game = GameManager::instancia(); 
  Hielo* hielo = NULL;
  for(int i; i<maxHielo ; i++){ if(game->hielo[i]==NULL) continue;
    if(this==game->hielo[i]->getHost()){
      hielo=game->hielo[i];
      break;
    }
  }
  if(hielo!=NULL){
    entity.setPosition( hielo->asEntity()->getX(), hielo->asEntity()->getY() );
  }
  entity.updateAnimacion();
}

void Snobee::eclosiona(){
  GameManager* game = GameManager::instancia();

  for(int i=0 ; i<maxEnemies ; i++){
    if(game->bees[i]==this){
      delete this;
      game->bees[i] = new Snobee( entity.getX(), entity.getY() );
    }
  }
}

bool Snobee::clogged(int direction){
  GameManager* game = GameManager::instancia();
  if(game->coliSnobeeSnobee(this, direction)){
    return true;
  }

  if(game->coliBorde(asEntity(), direction)){
    return true;
  }

  if(game->HayDiamante(this, direction)){
    return true;
  }

  return false;
}

bool Snobee::allClogged(){
  if(clogged(1) && clogged(2) && clogged(3) && clogged(4)){
    return true;
  }

  return false;
}