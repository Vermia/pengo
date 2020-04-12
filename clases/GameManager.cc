#include "GameManager.h"
#include <SFML/Graphics.hpp>

   GameManager* GameManager::p_instancia = 0;

   GameManager* GameManager::instancia(){
       if(p_instancia == 0){
           p_instancia = new GameManager;
       }

       return p_instancia;
   }

GameManager::GameManager() {
    gridW=13.0f;
    gridH=15.0f;
    unitW=40.0f;
    unitH=36.0f;
    windowW=gridW*unitW;
    windowH=gridH*unitH;
    sf::String title = "El compilador me vacila";
    gameover=false;
    vidas=3;
    godmode=false;

    for(int i=0 ; i<maxHielo ; i++){
        hielo[i]=NULL;
    }

    for(int i=0 ; i<maxEnemies ; i++){
        bees[i]=NULL;
    }


    if( ! Pengo::giveTexture("resources/sheet_Pengo.png")) std::cout << "Error cargando textura de Pengo" << std::endl;
    if( ! Hielo::giveTexture("resources/sheet_Hielo.png")) std::cout << "Error cargando textura de Hielo" << std::endl;
    if(!Snobee::giveTexture("resources/sheet_Snobee.png")) std::cout << "Error cargando textura de Snobee" << std::endl;
}

bool GameManager::start(){
    pengo = new Pengo(windowW/2, windowH/2);
    vidas=3;

    ////// CREAR MAPA DE HIELOS ///////
    int a = 0;
    for(int i=0 ; i<gridW ; i++){
        for(int j=0 ; j<gridH ; j++){
            if(i==0 || i>=gridW-1 || j==0 || j>=gridH-1){
                hielo[a++] = crearHielo(i,j);
            }
        }
    }
    for(int i=1 ; i<gridW-1 ; i++){
        hielo[a++] = crearHielo(i,4);
    }
    //////////// MAPA DE HIELOS CREADO //////////

    /////////// CREAR SNOBEES ///////////////
    bees[0] = crearSnobee(2,2);
    bees[1] = crearSnobee(10,2);
    bees[2] = crearSnobee(10, 13);
    bees[3] = crearSnobee(2, 13);
    ////////// SNOBEES CREADOS //////////
    return true;
}

bool GameManager::start(int seed){
    int pengoX=7, pengoY=6;
    pengo = crearPengo(pengoX, pengoY);
    vidas=3;
    currentLevel=seed;


    /////////// CREAR SNOBEES ///////////////

    Vector2i casillasSnobee[maxEnemies];

    casillasSnobee[0].x=seed%101%4+1; casillasSnobee[0].y=seed%239%4+1;
    casillasSnobee[1].x=seed%102%4+8; casillasSnobee[1].y=seed%62%4+1;
    casillasSnobee[2].x=seed%4+1; casillasSnobee[2].y=seed%80%3+10;
    casillasSnobee[3].x=seed%67%4+8; casillasSnobee[3].y=seed%1234%3+10;


    bees[0]=crearSnobee(casillasSnobee[0].x, casillasSnobee[0].y);
    bees[1]=crearSnobee(casillasSnobee[1].x, casillasSnobee[1].y);
    bees[2]=crearSnobee(casillasSnobee[2].x, casillasSnobee[2].y);
    bees[3]=crearSnobee(casillasSnobee[3].x, casillasSnobee[3].y);
    
    ////////// SNOBEES CREADOS //////////

    //////// CREAR MAPA DE HIELOS /////////
    int a=0;

    int tipoMapa=0;
    if(seed%6000<=1200) tipoMapa=1;
    else if(seed%6000>1200 && seed%6000<2400) tipoMapa=2;
    //si es 2400, tipoMapa=0
    else if(seed%6000>2400) tipoMapa=3;

    //Leyenda tipoMapa: 0=especial, 1=Shape (20%), 2=Scarce(20%), 3=plentiful(60%)
    switch(tipoMapa){
        case 1: //SHAPE
            
        break;

        case 2: //SCARCE

        break;

        case 3: //PLENTIFUL
        //Llenamos el mapa de hielo
        for(int i=0 ; i<gridW ; i++){
            for(int j=0 ; j<gridH ; j++){
                if(i==pengoX && j==pengoY) continue;
                if(i==casillasSnobee[0].x && j==casillasSnobee[0].y) continue;
                if(i==casillasSnobee[1].x && j==casillasSnobee[1].y) continue;
                if(i==casillasSnobee[2].x && j==casillasSnobee[2].y) continue;
                if(i==casillasSnobee[3].x && j==casillasSnobee[3].y) continue;
                hielo[a++]=crearHielo(i,j);
            }
        }
        hielo[a++]=crearHielo(0,0);


        quitarHieloLinea(casillasSnobee[0].x, casillasSnobee[0].y-seed%56%3, pengoY, false);
        quitarHieloLinea(casillasSnobee[0].x, pengoY, casillasSnobee[3].x, true);
        quitarHieloLinea(casillasSnobee[2].x, casillasSnobee[2].y, casillasSnobee[3].x, true);
        quitarHieloLinea(casillasSnobee[3].x, pengoY, casillasSnobee[3].y, false);
        quitarHieloLinea(casillasSnobee[0].x, casillasSnobee[1].y, casillasSnobee[1].x, true);
        quitarHieloLinea(pengoX, pengoY, casillasSnobee[2].y, false);
        quitarHieloLinea(pengoX+seed%555%2+1,casillasSnobee[1].y, pengoY+seed%457%3, false);
        if(seed%973%3!=0) quitarHieloLinea( casillasSnobee[2].x+seed%532%5, casillasSnobee[2].y, gridH, false  );
        if(seed%339%5==0) quitarHieloLinea(0, seed%29%(int)gridH, gridW, true );
        if(seed%336%34%4==0) quitarHieloLinea(seed%294%(int)gridW, 0, gridH, false );


        
        break;

        default: //ESPECIAL
            start();
        break;
    }


        ////////////MAPA GENERADO/////////
        int variance=2;
        //Poner huevos
        while(Hielo::totalHuevos<maxHuevos){
            for(int i=0; i<maxHielo ; i++){ if(hielo[i]==NULL) continue;
                if(Hielo::totalHuevos>=maxHuevos) break;;
                if(seed%(10+variance)<2){
                    hielo[i]->tieneHuevo();
                }
                variance++;
            }
        }

    for(int i=0 ; i<gridW ; i++){
        for(int j=0 ; j<gridH ; j++){
            if(i==6 && j==7) continue;
            if(i==casillasSnobee[0].x && j==casillasSnobee[0].y) continue;
            if(i==casillasSnobee[1].x && j==casillasSnobee[1].y) continue;
            if(i==casillasSnobee[2].x && j==casillasSnobee[2].y) continue;
            if(i==casillasSnobee[3].x && j==casillasSnobee[3].y) continue;


        }
    }
    //////////// MAPA DE HIELOS CREADO //////////

    return true;

}
Pengo* GameManager::crearPengo(int columna, int fila){
    return new Pengo(unitW/2+unitW*columna, unitH/2 +unitH*fila);
}

Hielo* GameManager::crearHielo(int columna, int fila){
    return new Hielo(unitW/2+unitW*columna, unitH/2 +unitH*fila);
}

Snobee* GameManager::crearSnobee(int columna, int fila){
    return new Snobee(unitW/2+unitW*columna, unitH/2 +unitH*fila);
}

GameManager::~GameManager(){
    delete pengo;
    pengo=NULL;
}

void GameManager::update(int ciclo){
    int afortunada=ciclo%4;

    //It's over, Anakin. I have the high ground.
    if(!vidas) gameOver();
    bool todosmuertos=true;
    for(int i=0 ; i<maxEnemies ; i++){
        if(bees[i]!=NULL){
            todosmuertos=false; break;
        }
    }
    if(todosmuertos) victoria();

    if(ciclo%10==0){
        for(int i=0;i<maxHielo;i++){ if(hielo[i]==NULL) continue;
            hielo[i]->eclosiona();
        }
    }

    //Colisiones
    for(int i=0; i<maxHielo ; i++){ 
        if(hielo[i]==NULL) continue; 
        if(hielo[i]->getKillme()) continue;
        //Buscamos una snobee para hacerle el update
        if(bees[afortunada]==NULL){
            afortunada++; if(afortunada>=maxEnemies)afortunada=0;
            if(bees[afortunada]==NULL){
                afortunada++; if(afortunada>=maxEnemies)afortunada=0; 
                if(bees[afortunada]==NULL){
                    break;
                }
            }
        }
        coliHieloSnobee(*hielo[i], *bees[afortunada]);
    }

    //Updates de las cosas
    pengo->update();

    for(int i=0 ; i<maxHielo ; i++){ if(hielo[i]==NULL) continue;
        hielo[i]->update();
        if(hielo[i]->getKillme()){
            delete hielo[i];
            hielo[i]=NULL;
        }
    }

    for(int i=0 ; i<maxEnemies ; i++){ if(bees[i]==NULL) continue;
        bees[i]->update();
        if(bees[i]->getKillme()){
            delete bees[i];
            bees[i]=NULL;
        }
    }

    
}

bool GameManager::canMove(int direction){
    bool puede = true;

    if(coliPengoHielo(direction)!=NULL){
        puede=false;
    }
    
    return puede;
}

void GameManager::draw(RenderWindow& window){
    

    for (int i = 0; i < maxHielo; i++){
        if(hielo[i]!=NULL){
            hielo[i]->draw(window);
        }
    }

    pengo->draw(window);
    
    for (int i = 0; i < maxEnemies; i++){
        if(bees[i]!=NULL){
            bees[i]->draw(window);
        }
    }
}

bool GameManager::push(){
    int facing = pengo->getFacing();

    Hielo* colisionante = coliPengoHielo(facing);

    if(colisionante==NULL){
        return false;
    }

    if(coliHieloHielo(colisionante, facing)){
        colisionante->destroy();
        return true;
    }else{
        colisionante->move(facing);
        return true;
    }
    

    return false;
}

Hielo* GameManager::coliPengoHielo(int direction){
    Hielo* colisionante = NULL;

    sf::FloatRect pengoLeft = pengo->asEntity().hitboxLeft;
    sf::FloatRect pengoRight = pengo->asEntity().hitboxRight;
    sf::FloatRect pengoDown = pengo->asEntity().hitboxDown;
    sf::FloatRect pengoUp = pengo->asEntity().hitboxUp;

    switch(direction){
        case 1: //Pengo intenta moverse hacia la derecha
        for(int i=0 ; i<maxHielo ; i++){
            if(hielo[i]!=NULL && pengoRight.intersects(hielo[i]->asEntity().hitboxLeft)){
                colisionante = hielo[i];
                break;
            }
        }
            
        break;
            
        case 2://Pengo intenta moverse hacia arriba
            for(int i=0 ; i<maxHielo ; i++){
                if(hielo[i]!=NULL && pengoUp.intersects(hielo[i]->asEntity().hitboxDown)){
                   colisionante = hielo[i];
                   break;
                }
            }
        break;

        case 3: //Pengo intenta moverse hacia la izquierda
            for(int i=0 ; i<maxHielo ; i++){
                if(hielo[i]!=NULL && pengoLeft.intersects(hielo[i]->asEntity().hitboxRight)){
                    colisionante = hielo[i];
                    break;
                }
            }
        break;

        case 4: //Pengo intenta moverse hacia abajo
            for(int i=0 ; i<maxHielo ; i++){
                if(hielo[i]!=NULL && pengoDown.intersects(hielo[i]->asEntity().hitboxUp)){
                    colisionante = hielo[i];
                    break;
                }
            }
        break;

        default:break;
    }

    return colisionante;
}

bool GameManager::coliHieloHielo(Hielo* hieloBase, int direction){
    bool hayColision = false;

    sf::FloatRect pengoLeft = hieloBase->asEntity().hitboxLeft;
    sf::FloatRect pengoRight = hieloBase->asEntity().hitboxRight;
    sf::FloatRect pengoDown = hieloBase->asEntity().hitboxDown;
    sf::FloatRect pengoUp = hieloBase->asEntity().hitboxUp;

    switch(direction){
        case 1: //Pengo intenta moverse hacia la derecha
        for(int i=0 ; i<maxHielo ; i++){
            if(hielo[i]!=NULL && pengoRight.intersects(hielo[i]->asEntity().hitboxLeft)){
                hayColision=true;
                break;
            }
        }
            
        break;
            
        case 2://Pengo intenta moverse hacia arriba
            for(int i=0 ; i<maxHielo ; i++){
                if(hielo[i]!=NULL && pengoUp.intersects(hielo[i]->asEntity().hitboxDown)){
                   hayColision=true;
                   break;
                }
            }
        break;

        case 3: //Pengo intenta moverse hacia la izquierda
            for(int i=0 ; i<maxHielo ; i++){
                if(hielo[i]!=NULL && pengoLeft.intersects(hielo[i]->asEntity().hitboxRight)){
                    hayColision=true;
                    break;
                }
            }
        break;

        case 4: //Pengo intenta moverse hacia abajo
            for(int i=0 ; i<maxHielo ; i++){
                if(hielo[i]!=NULL && pengoDown.intersects(hielo[i]->asEntity().hitboxUp)){
                    hayColision=true;
                    break;
                }
            }
        break;

        default:break;
    }

    return hayColision;
}

bool GameManager::coliPengoSnobee(){
    for(int i=0 ; i<maxEnemies; i++){ if(bees[i]==NULL) continue;
        if(pengo->asEntity().hitboxLeft.intersects(bees[i]->getHitbox())
        || pengo->asEntity().hitboxDown.intersects(bees[i]->getHitbox())
        || pengo->asEntity().hitboxRight.intersects(bees[i]->getHitbox())
        || pengo->asEntity().hitboxUp.intersects(bees[i]->getHitbox())
        ){
            return true;
        }
    }

    return false;
}

int GameManager::coliHieloSnobee(Hielo& hielo0, Snobee& snobee0){
    int hMoving = hielo0.asEntity().getMovingState();
    FloatRect beebox=snobee0.getHitbox();
    FloatRect hielobox=hielo0.getHitbox();
    if(beebox.intersects(hielobox)){
        if(hMoving){
            snobee0.destroy();
            return 1;
        } else{
            hielo0.destroy();
            return 2;
        }
    }

    return 0;
}




void GameManager::finish(){
    delete pengo;
    pengo = NULL;

    for(int i=0 ; i<maxHielo ; i++){ if(hielo[i]==NULL) continue;
        delete hielo[i];
        hielo[i]=NULL;
    }

    for(int i=0 ; i<maxEnemies ; i++){ if(bees[i]==NULL) continue;
        delete bees[i];
        bees[i]=NULL;
    }
}

int GameManager::buscarHielo(int columna, int fila){
    int encontrado=0;

    float x = unitW/2 + unitW*columna;
    float y = unitH/2 + unitH*fila;

    for(int i=0 ; i<maxHielo ; i++){ if(hielo[i]==NULL) continue;
        if(hielo[i]->asEntity().getX() == x && hielo[i]->asEntity().getY() == y){
            encontrado=i;
            break;
        }
    }

    return encontrado;
}

Snobee* GameManager::buscarSnobee(int columna, int fila){
    Snobee* encontrado=NULL;

    float x = unitW/2 + unitW*columna;
    float y = unitH/2 + unitH*fila;

    for(int i=0 ; i<maxEnemies ; i++){ if(bees[i]==NULL) continue;
        if(bees[i]->asEntity().getX() == x && bees[i]->asEntity().getY() == y){
            encontrado=bees[i];
            break;
        }
    }

    return encontrado;
}

void GameManager::quitarHieloLinea(int x, int y, int len, bool horizontal){
    int aux=0;
    if(horizontal){
        for(int i=x ; i<=len; i++){
            aux=buscarHielo(i, y);
            if(hielo[aux]!=NULL){
                delete hielo[aux];
                hielo[aux]=NULL;
            }
        }
    }else{
        for(int i=y ; i<=len ;i++){
            aux=buscarHielo(x, i);
            if(hielo[aux]!=NULL){
                delete hielo[aux];
                hielo[aux]=NULL;
            }
        }
    }
}


void GameManager::colisiones(){
    
}

void GameManager::gameOver(){
   finish();
   start(currentLevel);
}

void GameManager::victoria(){
    finish();
    start( rand()%1000+3601 );
}