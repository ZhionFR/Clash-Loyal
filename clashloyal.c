#include "clashloyal.h"
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "math.h"
#include "type.h"
#include <time.h>

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
    const char* InitialeUnite[7]={"T", "R", "A", "C", "D", "G", "E"};

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

void affichePlayerListConsole(TListePlayer playerList){
    //pour un affichage sur la console, en relation avec enum TuniteDuJeu
    const char* InitialeUnite[7]={"T", "R", "A", "C", "D", "G", "E"};

    printf("\n[ ");
    TListePlayer curr = playerList;
    while(!(isEmptyList(curr))){
        printf("%s ",InitialeUnite[getData(curr)->nom]);
        curr = getNextCell(curr);
    }
    printf("]\n");
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
Tunite* getTarget(Tunite* unit){
    if (unit->Target==NULL){
        return NULL;
    }else{
        return unit->Target;
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
        return 1;
    }else{
        return 0;
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
            return 1;
        }
    }
    printf("No possible spawn location found\n");
    return 0;
}


TListePlayer buyUnit(TplateauJeu jeu, TListePlayer* playerList, int* elixir, int whichplayer){ // explication : cf. /Docu/dragonDesProbas.png
    Tunite* newUnit;
    int probaArcher = 1;
    int probaChevalier = 1;
    int probaDragon = 1;
    int probaGargouille = 1;
    int probatotal = probaArcher + probaChevalier + probaDragon + probaGargouille;
    int randint = rand()%probatotal;
    int posx = 0;
    int posy = 0;
    if (findNewUnitPlace(jeu, whichplayer, &posx, &posy)){
        if(randint<probaArcher){
            if (*elixir>2){
                *elixir = *elixir - 2;
                newUnit = creeArcher(posx, posy);
                return addUnitToGame(jeu, playerList, newUnit);
            }else{
                return *playerList;
            }
        }else{
        randint = randint - probaArcher;
        if(randint<probaChevalier){
            if (*elixir>4){
                *elixir = *elixir - 4;
                newUnit = creeChevalier(posx, posy);
                return addUnitToGame(jeu, playerList, newUnit);
            }else{
                return *playerList;
            }
        }else{
        randint = randint - probaChevalier;
        if(randint<probaDragon){
            if (*elixir>3){
                *elixir = *elixir - 3;
                newUnit = creeDragon(posx, posy);
                return addUnitToGame(jeu, playerList, newUnit);
            }else{
                return *playerList;
            }
        }else{
        randint = randint - probaDragon;
        if(randint<probaGargouille){
            if (*elixir>1){
                *elixir = *elixir - 1;
                newUnit = creeGargouille(posx, posy);
                return addUnitToGame(jeu, playerList, newUnit);
            }else{
                return *playerList;
            }
        }else{
            return *playerList;
        }
        }
        }
        }
    }else{
        return *playerList;
    }
}

TListePlayer addKingTower(TplateauJeu jeu, TListePlayer* playerList, int whichplayer){
    Tunite* kingTower;
    int posKing = 1;
    if(whichplayer==2){
        posKing = 17;
    }
    kingTower = creeTourRoi(5, posKing);
    return addUnitToGame(jeu, playerList, kingTower);
}

TListePlayer addBaseTower(TplateauJeu jeu, TListePlayer* playerList, int whichplayer){
    Tunite* tower;
    int posTower = 3;
    if(whichplayer==2){
        posTower = 15;
    }
    tower = creeTour(5, posTower);
    return addUnitToGame(jeu, playerList, tower);
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

TListePlayer addUnitToGame(TplateauJeu jeu, TListePlayer* playerList, Tunite* unit){
    int posX = getPosX(unit);
    int posY = getPosY(unit);
    jeu[posX][posY] = unit;
    return addLast(*playerList, unit);
}


/****************** Updating Game ******************/

void updatePlayer(TplateauJeu jeu, TListePlayer playerList, int whichPlayer, TListePlayer enemyPlayerList, int time){
    TListePlayer current = playerList;
    Tunite* unit;
    if (isEmptyList(current)){
        exit(1);
    }
    while(!(isEmptyList(current))){
        unit = getData(current);
        updateUnit(jeu, unit, whichPlayer, enemyPlayerList, time);
        current = getNextCell(current);
    }
}


void updateUnit(TplateauJeu jeu, Tunite* unit, int whichPlayer, TListePlayer enemyPlayerList, int time){
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
    int hp;
    int atkDelay = getAttackDelay(unit);
    Tunite* target = NULL;
    target = getIfTarget(unit, target);
    if (target!=NULL){
            if(!(time%atkDelay)){ // time%atkDelay = 0 tous les atkDelay ticks
            hp = ((getHPLeft(target)) - (getDamage(unit)));
            if (hp<=0){
                enemyPlayerList = killUnit(target, enemyPlayerList, jeu);
                target = NULL;
            }else {
                setHPLeft(target, hp);
            }
        }
    }else{
        target = getNewTarget(unit, enemyPlayerList, target);
        if (target!=NULL){
            if(time%atkDelay){ // time%atkDelay vaut 0 tous les atkDelay ticks
                hp = getHPLeft(target);
                hp = ((getHPLeft(target)) - (getDamage(unit)));
                if (hp<=0){
                    enemyPlayerList = killUnit(target, enemyPlayerList, jeu);
                    target = NULL;
                }else {
                    setHPLeft(target, hp);
                }
            }
        }else{
            if(!(time%3)){ // on bouge tt les 3 ticks, à changer si on change la vitesse des ticks obviously ;)
                moveUnit(jeu, unit, whichPlayer);
            }
        }
    }
}

/*************** GetNewTarget ***************/
int dist(int Xa, int Ya, int Xb, int Yb){
    int d = (Xa-Xb)*(Xa-Xb)+(Ya-Yb)*(Ya-Yb);
    return sqrt(d);
}

Tunite* getIfTarget(Tunite* unit, Tunite* target){
    if (target == NULL) {
        return NULL;
    }
    int posX = getPosX(unit);
    int posY = getPosY(unit);
    int tposX = getPosX(target);
    int tposY = getPosY(target);
    int d = dist(posX, posY, tposX, tposY);
    if (d < getRange(unit) && getHPLeft(target) > 0) {
        return target;
    } else {
        return NULL;
    }
}


Tunite* getNewTarget(Tunite* unit, TListePlayer enemyPlayer, Tunite* target){
    int i = 0, n = getNbCell(enemyPlayer);
    TListePlayer current = enemyPlayer;
    int posX, posY, CposX, CposY, maxRange, d;
    posX = getPosX(unit);
    posY = getPosY(unit);
    maxRange = getRange(unit);
    int loop = 1;
    while(loop){
        if (isEmptyList(current)){
            return NULL;
        }
        CposX = getPosX(getData(current));
        CposY = getPosY(getData(current));
        d = dist(posX, posY, CposX, CposY);
        if (d<=maxRange){
            return getData(current);
        }else{
            if(i>=n){
                return NULL;
            }else{
                current = getNextCell(current);
                i++;
            }
        }
    }
    return NULL;
}

/***************** KillUnit *****************/

int findUnitIndex(TListePlayer playerList, int posX, int posY){
    TListePlayer current = playerList;
    int i = 0;
    while (current != NULL) {
        Tunite* unit = getData(current);
        if (posX == getPosX(unit) && posY == getPosY(unit)) {
            return i;
        }
        current = getNextCell(current);
        i++;
    }
    return -1;
}

TListePlayer killUnit(Tunite* unit, TListePlayer playerList, TplateauJeu jeu){
    int posX = getPosX(unit);
    int posY = getPosY(unit);
    int ind;
    ind = findUnitIndex(playerList, posX, posY);
    if (ind==-1){
        return playerList;
    }
    playerList = delAtN(playerList, ind);
    jeu[posX][posY] = NULL;
    return playerList;
}

/***************** MoveUnit *****************/

void moveUnitTo(TplateauJeu jeu, Tunite* unit, int posX, int posY){ // type void -> int to add verif if split flying/not
    int prevPosX = getPosX(unit);
    int prevPosY = getPosY(unit);
    jeu[prevPosX][prevPosY] = NULL;
    jeu[posX][posY] = unit;
    setPosX(unit, posX);
    setPosY(unit, posY);
}

void moveUnit(TplateauJeu jeu, Tunite* unit, int whichplayer){ // TBD : les unites volantes doivent passer au dessus de la riviere
    int i, n = getMoveSpeed(unit);
    if (n==0){
        return;
    }
    int randint = rand()%2;
    int randint2 = rand()%2;
    int posX = getPosX(unit);
    int posY = getPosY(unit);
    int yDir = +1;
    int xDir = +1;                  // Default = vers le haut
    if (whichplayer==2){
        yDir = -1;                  // Si joueur 2 : vers le bas
    }
    for (i=0;i<n;i++){
        if (posX>5){                // Si a gauche, direction de X = droite
            xDir = -1;
        }else{
            if (posX==5){
                if (randint2){      // Si au milieu, direction de X = random
                    xDir = -1;
                }else{
                    xDir = +1;
                }
            }else{
                if (posX<5){        // Si a droite, direction de X = gauche
                   xDir = +1;
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

/****************** THE END ******************/

int isKingDead(T_List l){
    if (isEmptyList(l)){
        return 0;
    }
    Tunite* firstUnit = getData(l);
    if (getUnitName(firstUnit) == tourRoi){
        return 1;
    }else{
        return 0;
    }
}






















