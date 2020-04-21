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
    ////////////// COSAS BASICAS //////////////
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
    nullbees=0;
    currentLevel=0;
    lineaDiamantes=false;
    for(int i=0 ; i<12 ; i++){
        niveles[i] = rand()%1000+3601;
    }

    bordesRosasTimer.setMax(1.0f);

    vista.setCenter(sf::Vector2f(windowW/2, windowH/2 - unitH*2));
    vista.setSize(sf::Vector2f(windowW + windowW/2, windowH + windowH/2));


    //////// BORDES ////////////
    float bordeSize = 25.0f;

    bordeDerecha.setSize(Vector2f(bordeSize, windowH + 2*bordeSize));
    bordeDerecha.setPosition(windowW-1 , -bordeSize);
    bordeDerecha.setFillColor(Color(255,0,128));
    
    bordeArriba.setSize(Vector2f(windowW, bordeSize));
    bordeArriba.setPosition(0,-bordeSize);
    bordeArriba.setFillColor(Color(255,0,128));

    bordeIzquierda.setSize(Vector2f(bordeSize, windowH + 2*bordeSize));
    bordeIzquierda.setPosition(-bordeSize,-bordeSize);
    bordeIzquierda.setFillColor(Color(255,0,128));

    bordeAbajo.setSize(Vector2f(windowW, bordeSize));
    bordeAbajo.setPosition(0,windowH);
    bordeAbajo.setFillColor(Color(255,0,128));

    //////////////// ENTITY ///////////////
    for(int i=0 ; i<maxHielo ; i++){
        hielo[i]=NULL;
    }
    for(int i=0 ; i<maxEnemies ; i++){
        bees[i]=NULL;
    }
    Hielo::initAnimaciones();

    /////////////// TEXTURAS /////////////
    if( ! Pengo::giveTexture("resources/sheet_Pengo.png")) std::cout << "Error cargando textura de Pengo" << std::endl;
    if( ! Hielo::giveTexture("resources/sheet_Hielo.png")) std::cout << "Error cargando textura de Hielo" << std::endl;
    if(!Snobee::giveTexture("resources/sheet_Snobee.png")) std::cout << "Error cargando textura de Snobee" << std::endl;
    if( !Huevo::giveTexture("resources/sheet_Snobee.png")) std::cout << "Error cargando textura de Snobee" << std::endl;


    ///////////// HUD ///////////////
    fuente.loadFromFile("resources/Roboto-Black.ttf");
    puntos=0;
    HUD_Puntuacion.setPosition(180,-150);
    HUD_Puntuacion.setString( String(std::to_string(puntos)) );
    HUD_Puntuacion.setColor( Color(255,255,255) );
    HUD_Puntuacion.setFont( fuente );

    HUD_Puntuacion_E.setPosition(0,-150);
    HUD_Puntuacion_E.setString( String( "Puntuacion: " ) );
    HUD_Puntuacion_E.setColor( Color(255,255,255) );
    HUD_Puntuacion_E.setFont( fuente );

    HUD_Vidas_E.setPosition(0,-100);
    HUD_Vidas_E.setString( String( "Vidas: " ) );
    HUD_Vidas_E.setColor( Color(255,255,255) );
    HUD_Vidas_E.setFont( fuente );

    HUD_Vida1.setTexture(*Pengo::getTextura());
    HUD_Vida1.setTextureRect(IntRect(0*unitW,0*unitH,unitW, unitH));
    HUD_Vida1.setPosition(100,-100);
    //HUD_Vida1.setScale(-1,1);
    HUD_Vida2.setTexture(*Pengo::getTextura());
    HUD_Vida2.setTextureRect(IntRect(0*unitW,0*unitH,unitW, unitH));
    HUD_Vida2.setPosition(150,-100);
    //HUD_Vida2.setScale(-1,1);
    HUD_Vida3.setTexture(*Pengo::getTextura());
    HUD_Vida3.setTextureRect(IntRect(0*unitW,0*unitH,unitW, unitH));
    HUD_Vida3.setPosition(200,-100);
    //HUD_Vida3.setScale(-1,1);

    HUD_currentLevel_E.setPosition(300,-100);
    HUD_currentLevel_E.setString( String( "Nivel: " ) );
    HUD_currentLevel_E.setColor( Color(255,255,255) );
    HUD_currentLevel_E.setFont( fuente );

    HUD_currentLevel.setPosition(400,-100);
    HUD_currentLevel.setString( std::to_string(currentLevel) );
    HUD_currentLevel.setColor(Color(255,255,255) );
    HUD_currentLevel.setFont(fuente);

    HUD_Seed_E.setPosition(300,-150);
    HUD_Seed_E.setString( "Semilla: " );
    HUD_Seed_E.setColor(Color(255,255,255) );
    HUD_Seed_E.setFont(fuente);

    HUD_Seed.setPosition(435,-150);
    HUD_Seed.setString( std::to_string(currentSeed) );
    HUD_Seed.setColor(Color(255,255,255) );
    HUD_Seed.setFont(fuente);

    HUD_Godmode.setPosition(0,-200);
    HUD_Godmode.setString( "God mode OFF" );
    HUD_Godmode.setColor(Color(128,128,128) );
    HUD_Godmode.setFont(fuente);
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

    bees[0]= crearSnobee(1,1);

    hielo[4] ->tieneHuevo();
    hielo[14]->tieneHuevo();
    hielo[24]->tieneHuevo();

    return true;
}

bool GameManager::start(int seed){
    int pengoX=7, pengoY=6;
    pengo = crearPengo(pengoX, pengoY);
    if(vidas==0) vidas=3;
    currentSeed=seed;
    Hielo::totalHuevos=0;
    Hielo::totalDiamantes=0;
    lineaDiamantes=false;

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

        variance=4;

        while(Hielo::totalDiamantes<maxDiamantes){
            for(int i=0; i<maxHielo ; i++){ if(hielo[i]==NULL) continue;
                if(Hielo::totalDiamantes>=maxDiamantes) break;;
                if(seed%(90+variance)<2 && !hielo[i]->getHuevo()){
                    
                    hielo[i]->tieneDiamante();
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
    if(!vidas){
        gameOver();
    }
    bool todosmuertos=true;
    for(int i=0 ; i<maxEnemies ; i++){
        if(bees[i]!=NULL){
            todosmuertos=false; break;
        }
    }
    if(todosmuertos) victoria();
    
    
    //Crear nuevos huevos
    if(bees[afortunada] == NULL){
        for(int i=0 ; i<maxHielo ; i++){ if(hielo[i]==NULL) continue;
            if(hielo[i]->getHuevo() && hielo[i]->getHost()==NULL){
                bees[afortunada] = new Snobee( hielo[i]->asEntity()->getX(), hielo[i]->asEntity()->getY() );
                bees[afortunada]->birth(hielo[i]);
                break;
            }
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
        if(bees[afortunada]!= NULL && !bees[afortunada]->isBirthing()){
            coliHieloSnobee(*hielo[i], *bees[afortunada]);
        }
    }

    int coliP_SB = coliPengoSnobee();
    if(coliP_SB != -1){
        if(bees[coliP_SB]->isStunned()){
            bees[coliP_SB]->destroy();
        } else{
            if(!godmode){
                pengo->iniciarMuerte();
            }
        }
    }

    //Updates de las cosas
    if(pengo!=NULL){
        pengo->update();
    }
        

    for(int i=0 ; i<maxHielo ; i++){ if(hielo[i]==NULL) continue;
        hielo[i]->update();
        if(hielo[i]->getKillme()){
            delete hielo[i];
            hielo[i]=NULL;
        }
    }

    if(bordesRosasTimer.advance() <= 0){
        bordeDerecha.setFillColor(Color(255,0,128));
        bordeArriba.setFillColor(Color(255,0,128));
        bordeIzquierda.setFillColor(Color(255,0,128));
        bordeAbajo.setFillColor(Color(255,0,128));
    }

    for(int i=0 ; i<maxEnemies ; i++){ if(bees[i]==NULL) continue;
        bees[i]->update();
        if(bees[i]->getKillme()){
            delete bees[i];
            bees[i]=NULL;
        }
    }

    if(comprobarLineaDiamantes()){
        activarLineaDiamantes();
    }

    HUD_Puntuacion.setString( std::to_string(puntos) );
    HUD_currentLevel.setString( std::to_string(currentLevel+1) );
    HUD_Seed.setString( std::to_string(currentSeed) );
}

bool GameManager::canMove(int direction){
    bool puede = true;

    if(coliPengoHielo(direction)!=NULL || coliBorde(pengo->asEntity(), direction)){
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

    

    window.draw(bordeDerecha);
    window.draw(bordeArriba);
    window.draw(bordeIzquierda);
    window.draw(bordeAbajo);


    window.draw(HUD_Puntuacion);
    window.draw(HUD_Puntuacion_E);
    window.draw(HUD_Vidas_E);
    window.draw(HUD_currentLevel_E);
    window.draw(HUD_currentLevel);
    if(vidas>=1) window.draw(HUD_Vida1);
    if(vidas>=2) window.draw(HUD_Vida2);
    if(vidas>=3) window.draw(HUD_Vida3);
    window.draw(HUD_Seed_E);
    window.draw(HUD_Seed);
    window.draw(HUD_Godmode);
}

bool GameManager::push(){
    int facing = pengo->getFacing();
    Hielo* colisionante = coliPengoHielo(facing);

    if(colisionante==NULL){
        return stun(facing);
    }

    pengo->setPushing(true);
    pengo->asEntity()->getAnimacion()->setBehavior(3);

    if(!pengo->isDying()){
        switch(facing){
            case 1: case 3:
                pengo->asEntity()->getAnimacion()->setSecuencia(pengo->animEmpujarDerecha);
            break;

            case 2:
                pengo->asEntity()->getAnimacion()->setSecuencia(pengo->animEmpujarArriba);
            break;

            case 4:
                pengo->asEntity()->getAnimacion()->setSecuencia(pengo->animEmpujarAbajo);
            break;

            default:break;
        }
    }
    
        if( (coliHieloHielo(colisionante, facing) || coliBorde(colisionante->asEntity(), facing)) && !colisionante->isDying() && !colisionante->getDiamante() ){
            colisionante->iniciarMuerte();
            return true;
        }else{
            if(!colisionante->isDying()){
                colisionante->move(facing);
                return true;
            }
        }
    
    
    

    return false;
}

Hielo* GameManager::coliPengoHielo(int direction){
    Hielo* colisionante = NULL;

    sf::FloatRect pengoLeft = pengo->asEntity()->hitboxLeft;
    sf::FloatRect pengoRight = pengo->asEntity()->hitboxRight;
    sf::FloatRect pengoDown = pengo->asEntity()->hitboxDown;
    sf::FloatRect pengoUp = pengo->asEntity()->hitboxUp;

    switch(direction){
        case 1: //Pengo intenta moverse hacia la derecha
        for(int i=0 ; i<maxHielo ; i++){
            if(hielo[i]!=NULL && pengoRight.intersects(hielo[i]->asEntity()->hitboxLeft)){
                colisionante = hielo[i];
                break;
            }
        }
            
        break;
            
        case 2://Pengo intenta moverse hacia arriba
            for(int i=0 ; i<maxHielo ; i++){
                if(hielo[i]!=NULL && pengoUp.intersects(hielo[i]->asEntity()->hitboxDown)){
                   colisionante = hielo[i];
                   break;
                }
            }
        break;

        case 3: //Pengo intenta moverse hacia la izquierda
            for(int i=0 ; i<maxHielo ; i++){
                if(hielo[i]!=NULL && pengoLeft.intersects(hielo[i]->asEntity()->hitboxRight)){
                    colisionante = hielo[i];
                    break;
                }
            }
        break;

        case 4: //Pengo intenta moverse hacia abajo
            for(int i=0 ; i<maxHielo ; i++){
                if(hielo[i]!=NULL && pengoDown.intersects(hielo[i]->asEntity()->hitboxUp)){
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

    sf::FloatRect pengoLeft = hieloBase->asEntity()->hitboxLeft;
    sf::FloatRect pengoRight = hieloBase->asEntity()->hitboxRight;
    sf::FloatRect pengoDown = hieloBase->asEntity()->hitboxDown;
    sf::FloatRect pengoUp = hieloBase->asEntity()->hitboxUp;

    switch(direction){
        case 1: //Pengo intenta moverse hacia la derecha
        for(int i=0 ; i<maxHielo ; i++){
            if(hielo[i]!=NULL && pengoRight.intersects(hielo[i]->asEntity()->hitboxLeft)){
                hayColision=true;
                break;
            }
        }
            
        break;
            
        case 2://Pengo intenta moverse hacia arriba
            for(int i=0 ; i<maxHielo ; i++){
                if(hielo[i]!=NULL && pengoUp.intersects(hielo[i]->asEntity()->hitboxDown)){
                   hayColision=true;
                   break;
                }
            }
        break;

        case 3: //Pengo intenta moverse hacia la izquierda
            for(int i=0 ; i<maxHielo ; i++){
                if(hielo[i]!=NULL && pengoLeft.intersects(hielo[i]->asEntity()->hitboxRight)){
                    hayColision=true;
                    break;
                }
            }
        break;

        case 4: //Pengo intenta moverse hacia abajo
            for(int i=0 ; i<maxHielo ; i++){
                if(hielo[i]!=NULL && pengoDown.intersects(hielo[i]->asEntity()->hitboxUp)){
                    hayColision=true;
                    break;
                }
            }
        break;

        default:break;
    }

    return hayColision;
}

int GameManager::coliPengoSnobee(){
    for(int i=0 ; i<maxEnemies; i++){ if(bees[i]==NULL) continue;
        if(pengo->asEntity()->hitboxLeft.intersects(bees[i]->getHitbox())
        || pengo->asEntity()->hitboxDown.intersects(bees[i]->getHitbox())
        || pengo->asEntity()->hitboxRight.intersects(bees[i]->getHitbox())
        || pengo->asEntity()->hitboxUp.intersects(bees[i]->getHitbox())
        ){
            return i;
        }
    }

    return -1;
}

int GameManager::coliHieloSnobee(Hielo& hielo0, Snobee& snobee0){
    int hMoving = hielo0.asEntity()->getMovingState();
    FloatRect beebox=snobee0.getHitbox();
    FloatRect hielobox=hielo0.getHitbox();
    Hielo* asesino = &hielo0;
    if(beebox.intersects(hielobox) && !snobee0.isDying()){
        if(hMoving){
            snobee0.iniciarMuerte(asesino);
            return 1;
        } else{
            snobee0.asEntity()->changeSpeed(20.0f);
            if(!hielo0.isDying() && !hielo0.getDiamante()){
                hielo0.iniciarMuerte();
                switch(snobee0.getFacing()){
                    case 1:
                        snobee0.asEntity()->getAnimacion()->setSecuencia(snobee0.animRomperDerecha);
                    break;
                    case 2:
                        snobee0.asEntity()->getAnimacion()->setSecuencia(snobee0.animRomperArriba);
                    break;
                    case 3:
                        snobee0.asEntity()->getAnimacion()->setSecuencia(snobee0.animRomperDerecha);
                    break;
                    case 4:
                        snobee0.asEntity()->getAnimacion()->setSecuencia(snobee0.animRomperAbajo);
                    break;
                    default:break;
                }
                return 2;
            }
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
        if(hielo[i]->asEntity()->getX() == x && hielo[i]->asEntity()->getY() == y){
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
        if(bees[i]->asEntity()->getX() == x && bees[i]->asEntity()->getY() == y){
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



void GameManager::gameOver(){
   finish();
   start(currentSeed);
}

void GameManager::victoria(){
    finish();
    currentLevel++;
    if(currentLevel>11){
        currentLevel=0;
        vidas=3;
        puntos=0;
    } 
    start( niveles[currentLevel] );
}

void GameManager::respawnPengo(){
    delete pengo;
    pengo = crearPengo(7, 6);
}

bool GameManager::coliPengoBorde(int direction){
    switch(direction){
        case 1:
            if(pengo->asEntity()->hitboxRight.intersects( bordeDerecha.getGlobalBounds() )){
                return true;
            }
        break;
        case 2:
            if(pengo->asEntity()->hitboxUp.intersects( bordeArriba.getGlobalBounds() )){
                return true;
            }
        break;
        case 3:
            if(pengo->asEntity()->hitboxLeft.intersects( bordeIzquierda.getGlobalBounds() )){
                return true;
            }
        break;
        case 4:
            if(pengo->asEntity()->hitboxDown.intersects( bordeAbajo.getGlobalBounds() )){
                return true;
            }
        break;
        

        default:break;
    }
    return false;
}
bool GameManager::coliBorde(Entity* entity, int direction){
    switch(direction){
        case 1:
            if(entity->hitboxRight.intersects( bordeDerecha.getGlobalBounds() )){
                return true;
            }
        break;
        case 2:
            if(entity->hitboxUp.intersects( bordeArriba.getGlobalBounds() )){
                return true;
            }
        break;
        case 3:
            if(entity->hitboxLeft.intersects( bordeIzquierda.getGlobalBounds() )){
                return true;
            }
        break;
        case 4:
            if(entity->hitboxDown.intersects( bordeAbajo.getGlobalBounds() )){
                return true;
            }
        break;
        

        default:break;
    }

    return false;
}


bool GameManager::stun(int direction){
    RectangleShape* tocado=NULL;
    if(coliBorde(pengo->asEntity(),direction)){
        switch(direction){
            case 1:
                tocado=&bordeDerecha;
                for(int i=0 ; i<maxEnemies ; i++){ if(bees[i]==NULL) continue;
                    if(coliBorde(bees[i]->asEntity(), 1)){ 
                        bees[i]->becomeStunned();
                    }
                }
                pengo->asEntity()->getAnimacion()->setSecuencia(pengo->animEmpujarDerecha);
            break;
            case 2:
                tocado=&bordeArriba;
                for(int i=0 ; i<maxEnemies ; i++){ if(bees[i]==NULL) continue;
                    if(coliBorde(bees[i]->asEntity(), 2)){ 
                        bees[i]->becomeStunned();
                    }
                }
                pengo->asEntity()->getAnimacion()->setSecuencia(pengo->animEmpujarArriba);
            break;
            case 3:
                tocado=&bordeIzquierda;
                for(int i=0 ; i<maxEnemies ; i++){ if(bees[i]==NULL) continue;
                    if(coliBorde(bees[i]->asEntity(), 3)){ 
                        bees[i]->becomeStunned();
                    }
                }
                pengo->asEntity()->getAnimacion()->setSecuencia(pengo->animEmpujarDerecha);
            break;
            case 4:
                tocado=&bordeAbajo;
                for(int i=0 ; i<maxEnemies ; i++){ if(bees[i]==NULL) continue;
                    if(coliBorde(bees[i]->asEntity(), 4)){ 
                        bees[i]->becomeStunned();
                    }
                }
                pengo->asEntity()->getAnimacion()->setSecuencia(pengo->animEmpujarAbajo);
            break;

            default:break;
        }

        pengo->setPushing(true);
        pengo->asEntity()->getAnimacion()->setBehavior(3);
        

        if(tocado!=NULL){
            tocado->setFillColor(Color(255,255,0));
            bordesRosasTimer.reset();
        }

    }
     

    return false;
}

bool GameManager::HayDiamante(Snobee* snobee0, int direction){
    switch(direction){
        case 1:
            for(int i=0 ; i<maxHielo ; i++){ if(hielo[i]==NULL) continue;
                if(hielo[i]->getDiamante() && hielo[i]->asEntity()->hitboxLeft.intersects( snobee0->asEntity()->hitboxRight )){
                    return true;
                }
            }
        break;
        case 2:
            for(int i=0 ; i<maxHielo ; i++){ if(hielo[i]==NULL) continue;
                if(hielo[i]->getDiamante() && hielo[i]->asEntity()->hitboxDown.intersects( snobee0->asEntity()->hitboxUp )){
                    return true;
                }
            }
        break;
        case 3:
            for(int i=0 ; i<maxHielo ; i++){ if(hielo[i]==NULL) continue;
                if(hielo[i]->getDiamante() && hielo[i]->asEntity()->hitboxRight.intersects( snobee0->asEntity()->hitboxLeft )){
                    return true;
                }
            }
        break;
        case 4:
            for(int i=0 ; i<maxHielo ; i++){ if(hielo[i]==NULL) continue;
                if(hielo[i]->getDiamante() && hielo[i]->asEntity()->hitboxUp.intersects( snobee0->asEntity()->hitboxDown )){
                    return true;
                }
            }
        break;
        default:break;
    }
    return false;
}

bool GameManager::comprobarLineaDiamantes(){
    Hielo* diamantes[maxDiamantes];
    for(int i=0 ; i<maxDiamantes ; i++) diamantes[i]=NULL;
    int a=0;

    for(int i=0; i<maxHielo ; i++){ if(hielo[i]==NULL) continue; 
        if(hielo[i]->getDiamante()){
            diamantes[a]=hielo[i];
            a++;
        }
    }
    if(diamantes[0]==NULL || diamantes[1]==NULL || diamantes[2]==NULL) return false;
    ////// HORIZONTAL
    // CENTRO 0
    if(diamantes[0]->asEntity()->hitboxLeft.intersects( diamantes[1]->asEntity()->hitboxRight)
    && diamantes[0]->asEntity()->hitboxRight.intersects( diamantes[2]->asEntity()->hitboxLeft )){
        return true;
    }
    if(diamantes[0]->asEntity()->hitboxLeft.intersects( diamantes[2]->asEntity()->hitboxRight)
    && diamantes[0]->asEntity()->hitboxRight.intersects( diamantes[1]->asEntity()->hitboxLeft )){
        return true;
    }

    //CENTRO 1
    if(diamantes[1]->asEntity()->hitboxLeft.intersects( diamantes[0]->asEntity()->hitboxRight)
    && diamantes[1]->asEntity()->hitboxRight.intersects( diamantes[2]->asEntity()->hitboxLeft )){
        return true;
    }
    if(diamantes[1]->asEntity()->hitboxLeft.intersects( diamantes[2]->asEntity()->hitboxRight)
    && diamantes[1]->asEntity()->hitboxRight.intersects( diamantes[0]->asEntity()->hitboxLeft )){
        return true;
    }

    //CENTRO 2
    if(diamantes[2]->asEntity()->hitboxLeft.intersects( diamantes[0]->asEntity()->hitboxRight)
    && diamantes[2]->asEntity()->hitboxRight.intersects( diamantes[1]->asEntity()->hitboxLeft )){
        return true;
    }
    if(diamantes[2]->asEntity()->hitboxLeft.intersects( diamantes[1]->asEntity()->hitboxRight)
    && diamantes[2]->asEntity()->hitboxRight.intersects( diamantes[0]->asEntity()->hitboxLeft )){
        return true;
    }

    /////////VERTICAL
    // CENTRO 0
    if(diamantes[0]->asEntity()->hitboxUp.intersects( diamantes[1]->asEntity()->hitboxDown)
    && diamantes[0]->asEntity()->hitboxDown.intersects( diamantes[2]->asEntity()->hitboxUp )){
        return true;
    }
    if(diamantes[0]->asEntity()->hitboxUp.intersects( diamantes[2]->asEntity()->hitboxRight)
    && diamantes[0]->asEntity()->hitboxDown.intersects( diamantes[1]->asEntity()->hitboxUp )){
        return true;
    }

    //CENTRO 1
    if(diamantes[1]->asEntity()->hitboxUp.intersects( diamantes[0]->asEntity()->hitboxDown)
    && diamantes[1]->asEntity()->hitboxDown.intersects( diamantes[2]->asEntity()->hitboxUp )){
        return true;
    }
    if(diamantes[1]->asEntity()->hitboxUp.intersects( diamantes[2]->asEntity()->hitboxDown)
    && diamantes[1]->asEntity()->hitboxDown.intersects( diamantes[0]->asEntity()->hitboxUp )){
        return true;
    }

    //CENTRO 2
    if(diamantes[2]->asEntity()->hitboxUp.intersects( diamantes[0]->asEntity()->hitboxDown)
    && diamantes[2]->asEntity()->hitboxDown.intersects( diamantes[1]->asEntity()->hitboxUp )){
        return true;
    }
    if(diamantes[2]->asEntity()->hitboxUp.intersects( diamantes[1]->asEntity()->hitboxDown)
    && diamantes[2]->asEntity()->hitboxDown.intersects( diamantes[0]->asEntity()->hitboxUp )){
        return true;
    }

    return false;
}

void GameManager::activarLineaDiamantes(){
    if(!lineaDiamantes){
        lineaDiamantes=true;
        for(int i=0; i<maxEnemies ; i++){ if(bees[i]==NULL) continue;
            bees[i]->becomeStunned();
        }
        incrementarPuntos(3500);
    }
    

    Hielo* diamantes[maxDiamantes];
    int a=0;
    for(int i=0; i<maxHielo ; i++){ if(hielo[i]==NULL) continue; 
        if(hielo[i]->getDiamante()){
            diamantes[a]=hielo[i];
            diamantes[a]->asEntity()->setSprite(3,0);
            a++;
        }
    }

}

void GameManager::toggleGodMode(){
    if(!godmode){
        godmode=true;
        HUD_Godmode.setColor( Color(255,255,0));
        HUD_Godmode.setString( "God mode ON" );
    } else{
        godmode=false;
        HUD_Godmode.setColor( Color(128,128,128));
        HUD_Godmode.setString( "God mode OFF" );
    }
}

bool GameManager::coliSnobeeSnobee(Snobee* snobee0, int direction){
    if(snobee0==NULL) return false;
    switch(direction){
        case 1:
            for(int i=0 ; i<maxEnemies; i++){ if(bees[i]==NULL) continue;
                if(bees[i]->asEntity()->hitboxRight.intersects( snobee0->asEntity()->hitboxLeft )){
                    return true;
                }
            }
        break;

        case 2:
            for(int i=0 ; i<maxEnemies; i++){ if(bees[i]==NULL) continue;
                if(bees[i]->asEntity()->hitboxUp.intersects( snobee0->asEntity()->hitboxDown )){
                    return true;
                }
            }
        break;

        case 3:
            for(int i=0 ; i<maxEnemies; i++){ if(bees[i]==NULL) continue;
                if(bees[i]->asEntity()->hitboxLeft.intersects( snobee0->asEntity()->hitboxRight )){
                    return true;
                }
            }
        break;

        case 4:
            for(int i=0 ; i<maxEnemies; i++){ if(bees[i]==NULL) continue;
                if(bees[i]->asEntity()->hitboxDown.intersects( snobee0->asEntity()->hitboxUp )){
                    return true;
                }
            }
        break;

        default:break;
    }
    return false;
}