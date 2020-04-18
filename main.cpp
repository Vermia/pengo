#include <SFML/Graphics.hpp>
#include <iostream>

#include "clases/GameManager.h"
#include "clases/Pengo.h"
#include "clases/Entity.h"
#include "clases/Hielo.h"
#include "clases/Snobee.h"

using namespace sf;


#define maxCiclos 120

// W: Width (ancho), H: Height (alto)
#define unitW 40
#define unitH 36
#define gridW 13
#define gridH 15

#define game_title "Fundamentos de los videopengos"

int main() {
  //////////////////
  //INITIAL STATE//
  /////////////////
  GameManager* game = GameManager::instancia();
 

  //Crear terreno de juego
  sf::RenderWindow window(sf::VideoMode(game->getWindowW(), game->getWindowH()), game->getTitle());
  window.setView(*game->getVista());
  //Hielo hielo(40,0, spriteHielo);
  srand(time(0));

  game->start( rand()%1000+3601 );
  int cycle = 0;
  bool showHitboxes=false;

  Clock clock;

  /////////////
  //GAMELOOP//
  ///////////
  while(window.isOpen()){
    ////////////////
    //HANDLE INPUT//
    ////////////////
    sf::Event event;
    while(window.pollEvent(event)){
      switch (event.type)
      {
      //Para poder cerrar la ventana se necesita:
      case sf::Event::EventType::Closed :
        window.close();
      break;

      case sf::Event::EventType::KeyPressed:

        switch (event.key.code) {
          
        
        //Mostrar los rectangulos de colision de todas las entidades
        case sf::Keyboard::M:
          if(showHitboxes){
            showHitboxes=false;
          } else showHitboxes=true;
        break;

        case sf::Keyboard::S:
          for (int i=0 ;i<maxEnemies; i++){ if(game->bees[i]==NULL) continue;
            game->bees[i]->becomeStunned();
          }
        break;

        case sf::Keyboard::Q:
          for (int i=0 ;i<maxHielo; i++){ if(game->hielo[i]==NULL) continue;
            game->hielo[i]->iniciarMuerte();
          }
        break;

        //Movimiento
        /*case sf::Keyboard::Right:
        game->pengo->face(1);
          if(game->canMove(1)){
            game->pengo->move(1);
          }
        break;

        case sf::Keyboard::Up:
        game->pengo->face(2);
          if(game->canMove(2)){
            game->pengo->move(2);
          }
        break;

        case sf::Keyboard::Left:
        game->pengo->face(3);
          if(game->canMove(3)){
            game->pengo->move(3);
          }
        break;

        case sf::Keyboard::Down:
        game->pengo->face(4);
          if(game->canMove(4)){
            game->pengo->move(4);
          }
        break;*/
        
        //Empujar!!!
        case sf::Keyboard::Space:
          game->push();
        break;

        case sf::Keyboard::Escape:
          window.close();
        break;

        case sf::Keyboard::N:
          game->victoria();
        break;

        case sf::Keyboard::X:
          game->pengo->iniciarMuerte();
          game->setVidas(1);
        break;

        case sf::Keyboard::G:
          if(game->godmode){
            game->godmode=false;
          } else {
            game->godmode=true;
          }
        break;

        default:
          break;
        }

      break; // de KeyPressed
      
      default:
        break;
      }
    }
    ////////////////
    //UPDATE STATE//
    ////////////////
    game->deltaTime=clock.restart().asSeconds();
    game->update(cycle++);
    if(cycle>=maxCiclos) cycle=0;

    if(game->gameover){
      window.close();
    }

    //////////
    //RENDER//
    //////////
    window.clear(sf::Color::Black);

    game->draw(window);


    if(showHitboxes){
      window.draw(game->pengo->asEntity()->hitboxTLV);
      window.draw(game->pengo->asEntity()->hitboxTRV);
      window.draw(game->pengo->asEntity()->hitboxBLV);
      window.draw(game->pengo->asEntity()->hitboxBRV);

      /*for(int i=0;i<180 ; i++){
        if(game->hielo[i]!=NULL){
          window.draw(game->hielo[i]->asEntity().hitboxTLV);
          window.draw(game->hielo[i]->asEntity().hitboxTRV);
          window.draw(game->hielo[i]->asEntity().hitboxBLV);
          window.draw(game->hielo[i]->asEntity().hitboxBRV);
        }
        
      }
*/
      for(int i=0 ; i<4 ; i++){ if(game->bees[i] == NULL) continue; 
        window.draw(game->bees[i]->getHitboxV());
      }
    }

    

    window.display();

    
  } // del gameloop

  return 0;
}