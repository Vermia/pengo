#include "Huevo.h"

sf::Texture* Huevo::textura = new sf::Texture();
bool Huevo::giveTexture(String file){
  return textura->loadFromFile(file);
}

Huevo::Huevo(float p_x, float p_y) : entity(p_x, p_y){
    entity.getAnimacion()->reset();
    entity.getAnimacion()->setBehavior(5);
    entity.getAnimacion()->setMaxTimer(3.0f);

    animNacer[0][0] = 4; animNacer[0][1] = 0;
    animNacer[1][0] = 5; animNacer[1][1] = 0;
    animNacer[2][0] = 6; animNacer[2][1] = 0;
    animNacer[3][0] =-1; animNacer[3][1] =-1;

    entity.getAnimacion()->setSecuencia(animNacer);
}

Huevo::~Huevo(){

}

void Huevo::draw(RenderWindow &window){
    window.draw(entity);
}

void Huevo::update(){
  entity.update();
}