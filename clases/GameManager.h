#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Hielo.h"
#include "Pengo.h"
#include "Snobee.h"
#include "Timer.h"

#define maxHielo 200
#define maxEnemies 4

class GameManager
{
public:
    static GameManager* instancia();
    Pengo* pengo;
    Hielo* hielo[maxHielo];
    Snobee* bees[maxEnemies];
    bool gameover;
    float deltaTime;
private:

    static GameManager* p_instancia;

    float windowW;
    float windowH;
    float gridW;
    float gridH;
    float unitW;
    float unitH;
    sf::String title;
    int vidas;
    int currentLevel;

    Timer bordesRosasTimer;

    sf::RectangleShape bordeDerecha;
    sf::RectangleShape bordeArriba;
    sf::RectangleShape bordeIzquierda;
    sf::RectangleShape bordeAbajo;

    sf::View vista;

protected:

    //CANON
    GameManager();
    GameManager(const GameManager& );
    GameManager &operator= (const GameManager& );

    public:
    ~GameManager();

    //FUNCTIONALITY
    bool start();  // Inicia una partida, creando pengo, bloques, etc
    bool start(int);
    void update(int); 
    bool canMove(int direction);
    Hielo* crearHielo(int, int);
    Snobee* crearSnobee(int, int);
    Pengo* crearPengo(int, int);

    Hielo* coliPengoHielo(int direction);
    bool coliHieloHielo(Hielo*, int direction);
    int coliPengoSnobee(); //0: Sin colision, 1: Pengo pierde, 2: Pengo gana
    int  coliHieloSnobee(Hielo&, Snobee&);
    bool coliPengoBorde(int direction);
    bool coliBorde(Entity*, int direction);

    void draw(RenderWindow&);
    bool push();
    bool stun(int direction);
    void gameOver();
    void victoria();
    void finish();
    void colisiones();
    void quitarHieloLinea(int, int, int, bool);
    void respawnPengo();

    int buscarHielo(int, int);
    Snobee* buscarSnobee(int, int);

    bool godmode;


    //GET
    float getWindowW(){return windowW;};
    float getWindowH(){return windowH;};
    float getGridW(){return gridW;};
    float getGridH(){return gridH;};
    float getUnitW(){return unitW;};
    float getUnitH(){return unitH;};
    int getVidas(){return vidas;}
    sf::String getTitle(){return title;};
    sf::View* getVista(){return &vista;};

    //SET
    bool setGrid( int p_gridW, int p_gridH );
    void perderVida(){vidas--; std::cout<<vidas<<std::endl;}
    void setVidas(int p_vidas){vidas=p_vidas;}
};



#endif