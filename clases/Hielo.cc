#include "Hielo.h"
#include "GameManager.h"

#define hieloSpeed 300.0f

int Hielo::totalHuevos=0;
int Hielo::totalDiamantes=0;
sf::Texture* Hielo::textura = new sf::Texture();

int Hielo::animSerDestruido[maxAnimationFrames][2];

bool Hielo::giveTexture(String file){
  return textura->loadFromFile(file);
}

void Hielo::initAnimaciones(){
  animSerDestruido[0][0]=0; animSerDestruido[0][1]=1;
  animSerDestruido[1][0]=1; animSerDestruido[1][1]=1;
  animSerDestruido[2][0]=2; animSerDestruido[2][1]=1;
  animSerDestruido[3][0]=3; animSerDestruido[3][1]=1;
  animSerDestruido[4][0]=4; animSerDestruido[4][1]=1;
  animSerDestruido[5][0]=-1; animSerDestruido[5][1]=-1;
}

//CANON
Hielo::Hielo(){
    maxMoveTimer=1500;
    killme=false;
    entity.changeSpeed(hieloSpeed);
    hitboxV.setFillColor(Color(0,0,255,128));
    huevo=false;
    dying=false;
}

Hielo::Hielo(int p_x, int p_y) : entity(p_x, p_y){
  entity.getSprite()->setTexture(*textura, true);
  entity.setSprite(0,0);

    host=NULL;
  maxMoveTimer=1500;
  killme=false;
  entity.changeSpeed(hieloSpeed);
  hitboxV.setFillColor(Color(0,0,255,128));
  huevo=false;
  diamante=false;
  dying=false;
}

Hielo::~Hielo(){
  if(huevo && host==NULL) totalHuevos--;

  GameManager* game = GameManager::instancia();
  if(host && host->isBirthing()) {
    for(int i=0 ; i<maxEnemies ; i++){
      if(host==game->bees[i]){
        delete game->bees[i];
        game->bees[i]=NULL;
        break;
      }
    }
  }
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
  if(!dying && !huevo) { //bugfix (un bug muy raro)
    entity.setSprite(0,0); 
  } else if (!dying && huevo){
    entity.setSprite(1,0);
  }
  if(diamante){
    entity.setSprite(2,0);
  }

if(!huevo)
  host=NULL;

  if(entity.getKillme()) killme=true;

  switch (entity.getMovingState())
  {
  case 1:
    if( game->coliHieloHielo(this, 1) || game->coliBorde(&entity, 1) ){
      entity.stop();
    }
  break;

  case 2:
    if(game->coliHieloHielo(this, 2) || game->coliBorde(&entity, 2)){
      entity.stop();
    }
  break;

  case 3:
    if(game->coliHieloHielo(this, 3) || game->coliBorde(&entity, 3)){
      entity.stop();
    }
  break;

  case 4:
    if(game->coliHieloHielo(this, 4) || game->coliBorde(&entity, 4)){
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

  if(entity.getAnimacion()->getBehavior()==2){
    //std::cout<<entity.getSprite()->getTextureRect().left << "...." <<entity.getSprite()->getTextureRect().top<<std::endl;
  } 

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
        
        break;
      }
    }
  }
}

//GET
Entity* Hielo::asEntity(){
    Entity* este = &entity;
    return este;
}

//SET
void Hielo::tieneHuevo(){
  huevo=true;
  Hielo::totalHuevos++;
  entity.setSprite(1,0);
}

void Hielo::iniciarMuerte(){
  dying=true;
  entity.getAnimacion()->reset();
  entity.getAnimacion()->setSecuencia(Hielo::animSerDestruido);
  entity.getAnimacion()->setBehavior(2);
}

void Hielo::tieneDiamante(){
  if(totalDiamantes<maxDiamantes){
    diamante=true;
    Hielo::totalDiamantes++;
    entity.setSprite(2,0);
  }
}