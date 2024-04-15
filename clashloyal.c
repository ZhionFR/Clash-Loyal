#include "clashloyal.h"
#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include <time.h>
#pragma GCC diagnostic ignored "-Wimplicit-int"
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"

/**************** Tab alloc/display ****************/

TplateauJeu AlloueTab2D(int largeur, int hauteur){
    TplateauJeu jeu;
    jeu = (Tunite***)malloc(sizeof(Tunite**)*largeur);
    for (int i=0;i<largeur;i++){
        jeu[i] = (Tunite**)malloc(sizeof(Tunite*)*hauteur);
    }
    return jeu;  //tab2D contenant des pointeurs
}

void initPlateauAvecNULL(TplateauJeu jeu,int largeur, int hauteur){
    for (int i=0;i<largeur;i++){
        for (int j=0;j<hauteur;j++){
            jeu[i][j] = NULL;
        }
    }
    // la rivière :
    jeu[0][9]=creeEmpty(0,9);
    jeu[1][9]=creeEmpty(1,9);
    jeu[2][9]=creeEmpty(2,9);
    jeu[3][9]=creeEmpty(3,9);
    jeu[4][9]=creeEmpty(4,9);
    jeu[6][9]=creeEmpty(6,9);
    jeu[7][9]=creeEmpty(7,9);
    jeu[8][9]=creeEmpty(8,9);
    jeu[9][9]=creeEmpty(9,9);
    jeu[10][9]=creeEmpty(10,9);
}

void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur){
    //pour un affichage sur la console, en relation avec enum TuniteDuJeu
    const char* InitialeUnite[6]={"T", "R", "A", "C", "D", "G"};

    printf("\n");
    for (int j=0;j<hauteur;j++){
        for (int i=0;i<largeur;i++){
            // A ne pas donner aux etudiants
            if (jeu[i][j] != NULL){
                    printf("%s",InitialeUnite[jeu[i][j]->nom]);
            }
            else printf(" ");  //cad pas d'unité sur cette case
        }
        printf("\n");
    }
}


/****************** Get functions ******************/

TuniteDuJeu getUnitName(Tunite* unit){
    return unit->nom;
}
Tcible getUnitTarget(Tunite* unit){
    return unit->cibleAttaquable;
}
Tcible getTargetCategory(Tunite* unit){
    return unit->maposition;
}
int getHPLeft(Tunite* unit){
    return unit->pointsDeVie;
}
float getAttackDelay(Tunite* unit){
    return unit->vitesseAttaque;
}
int getDamage(Tunite* unit){
    return unit->degats;
}
int getRange(Tunite* unit){
    return unit->portee;
}
int getMoveSpeed(Tunite* unit){
    return unit->vitessedeplacement;
}
int getPosX(Tunite* unit){
    return unit->posX;
}
int getPosY(Tunite* unit){
    return unit->posY;
}
int getElixirCost(Tunite* unit){
    return unit->coutEnElixir;
}
int getTarget(Tunite* unit, Tunite* cible){ // cible est la variable qu'on voudrati renvoyer si on etait sur d'avoir une cible,
                                            // mais on doit renvoyer un int pour savoir si on en a une donc on passe cible en argument
                                            // et on la modifiera lors du get tout en renvoyant 0 si elle existe et 1 sinon
    if (unit->Target==NULL){
        cible = NULL;
        return 1;
    }else{
        cible = unit->Target;
        return 0;
    }
}



/****************** Set functions ******************/

void setUnitName(Tunite* unit, TuniteDuJeu name){
    unit->nom = name;
}
void setUnitTarget(Tunite* unit, Tcible target){
    unit->cibleAttaquable = target;
}
void setTargetCategory(Tunite* unit, Tcible position){
    unit->maposition = position;
}
void setHPLeft(Tunite* unit, int hp){
    unit->pointsDeVie = hp;
}
void setAttackDelay(Tunite* unit, int atkdelay){
    unit->vitesseAttaque = atkdelay;
}
void setDamage(Tunite* unit, int dmg){
    unit->degats = dmg;
}
void setRange(Tunite* unit, int range){
    unit->portee = range;
}
void setMoveSpeed(Tunite* unit, int movespeed){
    unit->vitessedeplacement = movespeed;
}
void setPosX(Tunite* unit, int posx){
    unit->posX = posx;
}
void setPosY(Tunite* unit, int posy){
    unit->posY = posy;
}
void setElixirCost(Tunite* unit, int elixircost){
    unit->coutEnElixir = elixircost;
}
void setTarget(Tunite* unit, Tunite* cible){
    unit->Target =  cible;
}



/****************** Creating Units ******************/

int isEmptySlot(TplateauJeu jeu, int posx, int posy){
    if (jeu[posx][posy]==NULL){
        return 0;
    }else{
        return 1;
    }
}

int findNewUnitPlace(TplateauJeu jeu, int whichplayer, int* posx, int* posy){
    int x;
    int y = 3;
    if (whichplayer==2) y = 15;
    for (x=3; x<8; x++){
        if (isEmptySlot(jeu, x, y)){
            *posx = x;
            *posy = y;
            return 0;
        }else{
            return 1;
        }
    }
}

void buyUnit(TplateauJeu jeu, TListePlayer playerList, int elixir, int whichplayer){ // explication : cf. /Docu/dragonDesProbas.png
    srand(time(NULL));
    int probaArcher = 1;
    int probaChevalier = 1;
    int probaDragon = 1;
    int probaGargouille = 1;
    int probatotal = probaArcher + probaChevalier + probaDragon + probaGargouille;
    int randint = rand()%probatotal;
    int* posx;
    int* posy;
    if (findNewUnitPlace(jeu, whichplayer, posx, posy)){
        if(randint<probaArcher){
            if (elixir>2){
                creeArcher(*posx, *posy);
            }
        }else{
        randint = randint - probaArcher;
        if(randint<probaChevalier){
            if (elixir>4){
                creeChevalier(*posx, *posy);
            }
        }else{
        randint = randint - probaChevalier;
        if(randint<probaDragon){
            if (elixir>3){
                creeDragon(*posx, *posy);
            }
        }else{
        randint = randint - probaDragon;
        if(randint<probaGargouille){
            if (elixir>1){
                creeGargouille(*posx, *posy);
            }
        }
        }
        }
        }
    }
}

void createTowers(TplateauJeu jeu, TListePlayer* playerList1, TListePlayer* playerList2){
    Tunite* Roi1 = creeTourRoi(5, 1);
    Tunite* Roi2 = creeTourRoi(5, 17);
    Tunite* Tour1 = creeTour(5, 3);
    Tunite* Tour2 = creeTour(5, 15);
    // add towers to game
    addUnitToGame(jeu, *playerList1, Roi1);
    addUnitToGame(jeu, *playerList1, Tour1);
    addUnitToGame(jeu, *playerList2, Roi2);
    addUnitToGame(jeu, *playerList2, Tour2);
}


Tunite *createUnit(TuniteDuJeu name, Tcible target, Tcible targetCategory, int MaxHP, int atkDelay, int damage, int range, int movementSpeed, int posX, int posY, int elixirCost){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    setUnitName(nouv, name);
    setUnitTarget(nouv, target);
    setTargetCategory(nouv, targetCategory);
    setHPLeft(nouv, MaxHP);
    setAttackDelay(nouv, atkDelay);
    setDamage(nouv, damage);
    setRange(nouv, range);
    setMoveSpeed(nouv, movementSpeed);
    setPosX(nouv, posX);
    setPosY(nouv, posY);
    setElixirCost(nouv, elixirCost);
    return nouv;
}

Tunite *creeTour(int posx, int posy){
    return createUnit(tour, solEtAir, sol, 500, 3, 100, 3, 0, posx, posy, 0);  // 1 s/atk -> 3 ticks
}
Tunite *creeTourRoi(int posx, int posy){
    return createUnit(tourRoi, solEtAir, sol, 800, 4, 120, 4, 0, posx, posy, 0);  // 1.2 s/atk -> 4 ticks
}
Tunite *creeChevalier(int posx, int posy){
    return createUnit(chevalier, sol, sol, 400, 5, 250, 1, 2, posx, posy, 4); // 1.5 s/atk -> 5 ticks
}
Tunite *creeArcher(int posx, int posy){
    return createUnit(archer, solEtAir, sol, 80, 2, 120, 3, 1, posx, posy, 2);  // 0.7 s/atk -> 2 ticks
}
Tunite *creeDragon(int posx, int posy){
    return createUnit(dragon, solEtAir, air, 200, 4, 70, 2, 2, posx, posy, 3); // 1.2 s/atk -> 4 ticks
}
Tunite *creeGargouille(int posx, int posy){
    return createUnit(gargouille, solEtAir, air, 80, 2, 90, 1, 3, posx, posy, 1);  // 0.6 s/atk -> 2 ticks
}
Tunite *creeEmpty(int posx, int posy){      // Creer des 'murs', on n'ajoute pas les Empty aux listes de joueurs donc elles ne sont pas updates
                                            // ne sont pas attaquees ou vues comme cibles, elles bloquent juste le deplacement.
    return createUnit(Empty, sol, sol, -1, -1, -1, -1, -1, posx, posy, -1);
}

void addUnitToGame(TplateauJeu jeu, TListePlayer playerList, Tunite* unit){
    int posX = getPosX(unit);
    int posY = getPosY(unit);
    jeu[posX][posY] = unit;
    playerList = addLast(playerList, unit);
}


/****************** Updating Game ******************/

void updatePlayer(TplateauJeu jeu, TListePlayer playerList, int whichPlayer, TListePlayer enemyPlayerList, int time){
    int i, n = getNbCell(playerList);
    TListePlayer current = playerList;
    Tunite* unit;
    for(i=0; i<n; i++){
        unit = getData(current);
        updateUnit(jeu, *unit, whichPlayer, enemyPlayerList, time);
    }
}


void updateUnit(TplateauJeu jeu, Tunite unit, int whichPlayer, TListePlayer enemyPlayerList, int time){
    // SI (Cible a portee && Cible vivante)
    //      SI (il est temps d'attaquer)
    //          Attaquer(Cible)
    // SINON SI (Nouvelle cible trouvee)
    //      Cible = Nouvelle cible
    //      SI (il est temps d'attaquer)
    //          Attaquer(Cible)
    // SINON
    //      SI (il est temps de bouger)
    //          Deplacer Unite
    Tunite* target = NULL;
    int hp;
    int atkDelay = getAttackDelay(&unit);
    int doesTargetExist = getTarget(&unit, target);
    if (doesTargetExist){
        if(time%atkDelay){ // time%atkDelay = 0 tous les atkDelay ticks
            hp = getHPLeft(target) - getDamage(&unit);
            if (hp<=0){
                enemyPlayerList = killUnit(*target, enemyPlayerList, jeu);
                target = NULL;
            }else {
                setHPLeft(target, hp);
            }
        }
    }else{
        getNewTarget(unit, enemyPlayerList, target);
        if (doesTargetExist){
            if(time%atkDelay){ // time%atkDelay vaut 0 tous les atkDelay ticks
                hp = getHPLeft(target) - getDamage(&unit);
                if (hp<=0){
                    enemyPlayerList = killUnit(*target, enemyPlayerList, jeu);
                    target = NULL;
                }else {
                    setHPLeft(target, hp);
                }
            }
        }else{
            if(time%3){ // on bouge tt les 3 ticks, à changer si on change la vitesse des ticks obviously ;)
                moveUnit(jeu, unit, whichPlayer);
            }
        }
    }
}

/*************** GetNewTarget ***************/
int dist(int Xa, int Ya, int Xb, int Yb){
    int d = (Xa-Xb)*(Xa-Xb)+(Ya-Xb)*(Ya-Xb);
    return sqrt(d);
}

void getNewTarget(Tunite unit, TListePlayer enemyPlayer, Tunite* target){
    int i = 0, n = getNbCell(enemyPlayer);
    TListePlayer current;
    int posX, posY, CposX, CposY, maxRange, d;
    posX = getPosX(&unit);
    posY = getPosY(&unit);
    maxRange = getRange(&unit);
    int loop = 0;
    while(loop){
        d = dist(posX, posY, CposX, CposY);
        if (dist<maxRange){
            target = getData(current);
            loop = 1;
        }else{
            if(i>n){
                target = NULL;
                loop = 1;
            }else{
                current = getNextCell(current);
                i++;
            }
        }
    }
}

/***************** KillUnit *****************/

int findUnitIndex(TListePlayer playerList, int posX, int posY){ // exeption non geree car on cherche normalement une unite qui est dans la liste
    TListePlayer current = playerList;
    int loop = 0;
    int i = 0;
    Tunite* unit;
    while (loop){
        unit = getData(current);
        if (posX==getPosX(unit)){
            if (posY==getPosY(unit)){
                return i;
            }
        }else{
            current = getNextCell(current);
            i++;
        }
    }
}

TListePlayer killUnit(Tunite unit, TListePlayer playerList, TplateauJeu jeu){
    int posX = getPosX(&unit);
    int posY = getPosY(&unit);
    int ind;
    ind = findUnitIndex(playerList, posX, posY);
    playerList = delAtN(playerList, ind);
    jeu[posX][posY] = NULL;
}

/***************** MoveUnit *****************/

void moveUnitTo(TplateauJeu jeu, Tunite unit, int posX, int posY){ // type void -> int to add verif if split flying/not
    int prevPosX = getPosX(&unit);
    int prevPosY = getPosY(&unit);
    jeu[prevPosX][prevPosY] = NULL;
    jeu[posX][posY] = &unit;
    setPosX(&unit, posX);
    setPosY(&unit, posY);
}

void moveUnit(TplateauJeu jeu, Tunite unit, int whichplayer){ // TBD : les unites volantes doivent passer au dessus de la riviere
    srand(time(NULL));
    int i, n = getMoveSpeed(&unit);
    int randint = rand()%2;
    int randint2 = rand()%2;
    int posX = getPosX(&unit);
    int posY = getPosY(&unit);
    int yDir = +1;
    int xDir = +1;                  // Default = vers le haut
    if (whichplayer==2){
        xDir = -1;                  // Si joueur 2 : vers le bas
    }
    for (i=0;i<n;i++){
        if (posY<5){                // Si a gauche, direction de Y = droite
            yDir = -1;
        }else{
            if (posY=5){
                if (randint2){      // Si au milieu, direction de Y = random
                    yDir = -1;
                }else{
                    yDir = +1;
                }
            }else{
                if (posY>5){        // Si a droite, direction de Y = gauche
                   yDir = +1;
                }
            }
        }
        if (randint){
            if (jeu[posX+xDir][posY]==NULL){
                moveUnitTo(jeu, unit, posX+xDir, posY);
            }else{
                if (jeu[posX][posY+yDir]==NULL){
                    moveUnitTo(jeu, unit, posX, posY+yDir);
                }
            }
        }else{
            if (jeu[posX][posY+yDir]==NULL){
                moveUnitTo(jeu, unit, posX, posY+yDir);
            }else{
                if (jeu[posX+xDir][posY]==NULL){
                    moveUnitTo(jeu, unit, posX+xDir, posY);
                }
            }
        }
    }
}






































