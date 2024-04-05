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

    //POUR LA DEMO D'AFFICHAGE UNIQUEMENT, A SUPPRIMER
    //(les tours ici ne sont pas liées aux listes des unités de vos joueurs)
    jeu[5][3]=creeTour(5,3);
    jeu[5][1]=creeTourRoi(5,1);
    jeu[5][15]=creeTour(5,15);
    jeu[5][17]=creeTourRoi(5,17);
    //FIN DEMO AFFICHAGE
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

Tunite *createUnit(TuniteDuJeu name, Tcible target, Tcible targetCategory, int MaxHP, float atkDelay, int damage, int range, float movementSpeed, int posX, int posY, int elixirCost){
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

Tunite *creeTour(posx, posy){
    return createUnit(tour, solEtAir, sol, 500, 1.0, 100, 3, 0, posx, posy, 0);  // 1 att/s -> 3 ticks
}
Tunite *creeTourRoi(posx, posy){
    return createUnit(tourRoi, solEtAir, sol, 800, 1.2, 120, 4, 0, posx, posy, 0);  // 1.2 att/s -> 4 ticks
}
Tunite *creeChevalier(posx, posy){
    return createUnit(chevalier, sol, sol, 400, 5, 250, 1, 2.0, posx, posy, 4); // 1.5 att/s -> 5 ticks
}
Tunite *creeArcher(posx, posy){
    return createUnit(archer, solEtAir, sol, 80, 0.7, 120, 3, 1.0, posx, posy, 2);  // 0.7 att/s -> 2 ticks
}
Tunite *creeDragon(posx, posy){
    return createUnit(dragon, solEtAir, air, 200, 1.1, 70, 2, 2.0, posx, posy, 3); // 1.2 att/s -> 4 ticks
}
Tunite *creeGargouille(posx, posy){
    return createUnit(gargouille, solEtAir, air, 80, 0.6, 90, 1, 3.0, posx, posy, 1);  // 0.6 att/s -> 2 ticks
}

/****************** Updating Game ******************/

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
                killUnit(*target);
                target = NULL;
            }else {
                setHPLeft(target, hp);
            }
        }
    }else{
        getNewTarget(unit, enemyPlayerList, target);
        if (doesTargetExist){
            if(time%atkDelay){ // time%atkDelay = 0 tous les atkDelay ticks
                hp = getHPLeft(target) - getDamage(&unit);
                if (hp<=0){
                    killUnit(*target);
                    target = NULL;
                }else {
                    setHPLeft(target, hp);
                }
            }
        }else{
            if(time%3){ // on bouge tt les 3 ticks, à changer si on change la vitesse des ticks obviously ;)
                moveUnit(jeu, unit);
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
    int i = 0, n = lenList(enemyPlayer);
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

void killUnit(Tunite unit){
    // remove unit from plateauJeu & TlistePlayer
}

void moveUnitTo(TplateauJeu jeu, Tunite unit, int posX, int posY){ // type void -> int to add verif if split flying/not
    int prevPosX = getPosX(&unit);
    int prevPosY = getPosY(&unit);
    jeu[prevPosX][prevPosY] = NULL;
    jeu[posX][posY] = &unit;
    setPosX(&unit, posX);
    setPosY(&unit, posY);
}

void moveUnit(TplateauJeu jeu, Tunite unit){
    srand(time(NULL));
    int i, n = getMoveSpeed(&unit);
    int randint = rand()%2;
    int posX = getPosX(&unit);
    int posY = getPosY(&unit);
    for (i=0;i<n;i++){
        if (randint){
            if (jeu[posX+1][posY]==NULL){
                moveUnitTo(jeu, unit, posX+1, posY);
            }else{
                if (jeu[posX][posY+1]==NULL){
                    moveUnitTo(jeu, unit, posX, posY+1);
                }
            }
        }else{
            if (jeu[posX][posY+1]==NULL){
                moveUnitTo(jeu, unit, posX, posY+1);
            }else{
                if (jeu[posX+1][posY]==NULL){
                    moveUnitTo(jeu, unit, posX+1, posY);
                }
            }
        }
    }
}

// Obsolete, a utiliser pour moveUnit
/*
void PositionnePlayerOnPlateau(TListePlayer player, TplateauJeu jeu, int whichPlayer){
    Tunite* unit;
    TListePlayer current = *player;
    int i, nbmovedone, posx, posy, randnum, doesItFly = 0;
    int len = lenList(player);
    srand(time(NULL));
    for (i=0;i<len;i++){
        unit = getData(*player);
        if (getTargetCategory(unit)==air){
            doesItFly = 1;
        }
        posx = getPosX(&unit);
        posy = getPosY(&unit);
        for (nbmovedone=0; nbmovedone<getMoveSpeed(&unit);nbmovedone++){
            randnum = rand()%2;
            if (whichPlayer==1){
                if(doesItFly){
                    if (posy!=8){
                        if (randnum == 0){
                                if (posx>5){
                                    moveUnit(jeu, *unit, posx-1, posy); //On deplace vers la gauche si l'unite est a droite
                                }else{
                                    if (posx>5) {
                                        moveUnit(jeu, *unit, posx-1, posy); //On deplace vers la droite si l'unite est a gauche
                                    }
                                }
                        } else {
                            moveUnit(jeu, *unit, posx, posy+1); // On deplace vers le haut
                        }
                    }else{
                            if (posx>5){
                                moveUnit(jeu, *unit, posx-1, posy); //On deplace vers la gauche si l'unite est a droite
                            }else{
                                if (posx>5) {
                                    moveUnit(jeu, *unit, posx-1, posy); //On deplace vers la droite si l'unite est a gauche
                                }
                            }
                    }
                }
            }
        }
    current = getNextCell(player);
    }
}

*/




































