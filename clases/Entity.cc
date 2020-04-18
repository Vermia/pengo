
#include "Entity.h"
#include "GameManager.h"
#include <iostream>

//CANON
Entity::Entity()      
{
    killme=false;
    moving=0;
    movespeedX=0;
    movespeedY=0;
    moveTimer=0;
    movementImpaired=false;
    setPosition(-500,-500); // lejos de la accion

    hitboxTLV.setFillColor(Color(255,0,0,128));
    hitboxTRV.setFillColor(Color(0,0,255,128));
    hitboxBLV.setFillColor(Color(0,255,0,128));
    hitboxBRV.setFillColor(Color(255,255,0,128));

    animacion=new Animacion();
}

Entity::Entity(float p_x, float p_y)
{
    killme=false;
    sprite = new Sprite();

    moving=0;
    movementImpaired=false;

    movespeedX=0;
    movespeedY=0;
    moveTimer=0;
    setPosition(p_x, p_y);

    hitboxTLV.setFillColor(Color(255,0,0,128));
    hitboxTRV.setFillColor(Color(0,0,255,128));
    hitboxBLV.setFillColor(Color(0,255,0,128));
    hitboxBRV.setFillColor(Color(255,255,0,128));

    animacion=new Animacion();
}

Entity::~Entity(){
    if(sprite!=NULL){
       // delete sprite;
    }
    
}


Entity::Entity(float p_x, float p_y, sf::Texture &p_texture){
    GameManager* game = GameManager::instancia();

    moving=0;
    movespeedX=0;
    movespeedY=0;
    moveTimer=0;
    texture=p_texture;
    sprite->setTexture(texture);
    sprite->setOrigin(game->getUnitW() / 2, game->getUnitH() / 2);
    setPosition(p_x, p_y);

    hitboxTLV.setFillColor(Color(255,0,0,128));
    hitboxTRV.setFillColor(Color(0,0,255,128));
    hitboxBLV.setFillColor(Color(0,255,0,128));
    hitboxBRV.setFillColor(Color(255,255,0,128));
}



//FUNCTIONALITY
void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*sprite, states);
}

bool Entity::move(int direction){
    if(moving==0){
        moving=direction;
        return true;
    } else return false;
}

bool Entity::stop(){
    if(moving!=0){
        moving=0;
        movementImpaired=false; //OJO
        normalizePosition();
        return true;
    }else return false;
}

void Entity::update(){

    GameManager* game = GameManager::instancia();
    float dt=game->deltaTime;
if(!movementImpaired){
switch(moving){
    case 0:
        
    break;
    case 1:
      sprite->move(movespeedX*dt, 0);
    break;
      
    case 2: 
      sprite->move(0, -movespeedY*dt);
    break;

    case 3: 
      sprite->move(-movespeedX*dt, 0);
    break;

    case 4:
      sprite->move(0, movespeedY*dt);
    break;

    default: break;
  }
}


  updateHitbox();
  updateAnimacion();
}




//SET
void Entity::setPosition(float p_x, float p_y){
    x=p_x;
    y=p_y;


    sprite->setPosition(sf::Vector2f(x,y));

    updateHitbox();

}

void Entity::changeSpeed(float p_speed){
    GameManager* game = GameManager::instancia();
    movespeedX=p_speed;
    movespeedY=p_speed*game->getUnitH()/game->getUnitW();
}

bool Entity::setTexture(sf::String file){
    GameManager* game = GameManager::instancia();

    if (texture.loadFromFile(file)) {
        sprite->setTexture(texture);
        sprite->setOrigin(sf::Vector2f(game->getUnitW() / 2, game->getUnitH() / 2));
        return true;
    }
    std::cout<<"Error de asignacion de textura"<<std::endl;
    return false;
}

void Entity::updateHitbox(){
    GameManager* game = GameManager::instancia();

    float xpos = sprite->getPosition().x;
    float ypos = sprite->getPosition().y;

    float uw = game->getUnitW() / 2;
    float uh = game->getUnitH() / 2;

    float cota=2.0f;

    hitboxLeft.left = xpos-uw-cota; //-cota = Arreglo chapucero para que intersecte por la izquierda
    hitboxLeft.top = ypos-uh+cota;
    hitboxLeft.width = 5;
    hitboxLeft.height = uh*2-cota;

    hitboxRight.left = xpos+uw;
    hitboxRight.top = ypos-uh+cota;
    hitboxRight.width = -5;
    hitboxRight.height = uh*2-cota;

    hitboxDown.left = xpos-uw+cota;
    hitboxDown.top = ypos+uw;
    hitboxDown.width = uw*2-cota;
    hitboxDown.height = -5;

    hitboxUp.left = xpos-uw+cota; 
    hitboxUp.top = ypos-uw;
    hitboxUp.width = uw*2-cota;
    hitboxUp.height = 5;

    hitboxTLV.setPosition(hitboxLeft.left, hitboxLeft.top);
    hitboxTLV.setSize(Vector2f(hitboxLeft.width, hitboxLeft.height));

    hitboxTRV.setPosition(hitboxRight.left, hitboxRight.top);
    hitboxTRV.setSize(Vector2f(hitboxRight.width, hitboxRight.height));

    hitboxBLV.setPosition(hitboxDown.left, hitboxDown.top);
    hitboxBLV.setSize(Vector2f(hitboxDown.width, hitboxDown.height));

    hitboxBRV.setPosition(hitboxUp.left, hitboxUp.top);
    hitboxBRV.setSize(Vector2f(hitboxUp.width, hitboxUp.height));
}

void Entity::updateAnimacion(){
    GameManager* game = GameManager::instancia();
    animacion->update();
    int it  = animacion->getIteracion();
    int col = animacion->getCurrentColumn();
    int row = animacion->getCurrentRow();

    //std::cout<< it << " ----- " << col << " ---- " << row << std::endl;

    if(col != -1 && row != -1){
        setSprite(col, row);
    } else {
        switch (animacion->getBehavior())
        {
        case 1:
            animacion->setIteracion(0);
        break;

        case 2:
            killme=true;
        break;

        case 3:
            game->pengo->setPushing(false);
            game->pengo->asEntity()->getAnimacion()->reset();
            game->pengo->asEntity()->getAnimacion()->setBehavior(1);
        break;

        case 4: 
            game->pengo->morir();
        break;
        
        default:
            break;
        }
    }
}

void Entity::normalizePosition(){
    float x0=sprite->getPosition().x;
    float y0=sprite->getPosition().y;
    GameManager* game = GameManager::instancia();
    float uw = game->getUnitW();
    float uh = game->getUnitH();
    float gw = game->getGridW();
    float gh = game->getGridH();

    float dx = __FLT_MAX__;
    float dy = __FLT_MAX__;
    float x=0;
    float y=0;

    float finalX=x0;
    float finalY=y0;

    for(int px=0 ; px<gw; px++){
        x = uw/2 + px*uw;
        if( abs(x0-x) < dx){
            dx=abs(x0-x);
            finalX=x;
        }
    }

    for(int py=0 ; py<gh; py++){
        y = uh/2 + py*uh;
        if( abs(y0-y) < dy){
            dy=abs(y0-y);
            finalY=y;
        }
    }

    sprite->setPosition(Vector2f(finalX, finalY));
}

bool Entity::setSprite(unsigned int column, unsigned int row){
    GameManager* game = GameManager::instancia();

    float unitW = game->getUnitW();
    float unitH = game->getUnitH();

    //sprite->setTexture(*Pengo::getTextura());
    sprite->setTextureRect(sf::IntRect(column*unitW, row*unitH, unitW, unitH));
    sprite->setOrigin(sf::Vector2f(game->getUnitW() / 2, game->getUnitH() / 2));

    return true;
}