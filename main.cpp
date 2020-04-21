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
  srand(time(0));
  GameManager* game = GameManager::instancia();
 

  //Crear terreno de juego
  sf::RenderWindow window(sf::VideoMode(game->getWindowW(), game->getWindowH()), game->getTitle());
  window.setView(*game->getVista());
  //Hielo hielo(40,0, spriteHielo);
  

  game->start( game->niveles[0] );
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
        break;

        // S : Aturdir a todos los Snobees. No deben estar ya aturdidos o no funcionara (no se
        //     resetea el temporizador)
        case sf::Keyboard::S:
          for (int i=0 ;i<maxEnemies; i++){ if(game->bees[i]==NULL) continue;
            game->bees[i]->becomeStunned();
          }
        break;

        // Q : Destruir mapa y mover Snobees al borde superior. Pensado para probar los 
        //     bordes y su funcion de aturdir
           
        case sf::Keyboard::Q:
          for (int i=0 ;i<maxHielo; i++){ if(game->hielo[i]==NULL) continue;
            game->hielo[i]->iniciarMuerte();
          }
          for(int i=0; i<maxEnemies; i++){ if(game->bees[i] == NULL) continue;
            game->bees[i]->asEntity()->setPosition( unitW*3 + unitW*2*i +unitW, unitH/2 );
            game->bees[i]->asEntity()->stop();
          }
        break;
        
        //Empujar!!!
        case sf::Keyboard::Space:
          game->push();
        break;

        //ESCAPE: Cerrar ventana
        case sf::Keyboard::Escape:
          window.close();
        break;

        // N : Pasar al siguiente nivel
        case sf::Keyboard::N:
          game->victoria();
        break;

        // X : Morir y despues reiniciar el nivel. Pone las vidas a 1 para perderla cuando
        //     termine la animacion de muerte
        case sf::Keyboard::X:
          game->pengo->iniciarMuerte();
          game->setVidas(1);
        break;

        // G :Inmortalidad. La X tiene prioridad sobre esto, y de hecho es la unica forma
        //                  de morir durante la inmortalidad. Pulsarlo de nuevo lo desactiva
        case sf::Keyboard::G:
          game->toggleGodMode();
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