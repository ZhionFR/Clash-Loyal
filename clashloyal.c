#include "SDL.h"
#include "clashloyal.h"
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <r
#include <time.h>

//typedef Tunite* ** TplateauJeu;

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

Tunite AcheteUnite(int *elixirEnStockduJoueur){

}

Tunite *creeTour(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tour;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 500;
    nouv->vitesseAttaque = 1.0;
    nouv->degats = 100;
    nouv->portee = 3;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->coutEnElixir = 0;
    return nouv;
}

Tunite *creeTourRoi(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = tourRoi;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 800;
    nouv->vitesseAttaque = 1.2;
    nouv->degats = 120;
    nouv->portee = 4;
    nouv->vitessedeplacement = 0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->coutEnElixir = 0;
    return nouv;
}
<<<<<<< Updated upstream
=======

Tunite *creeChevalier(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = chevalier;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 400;
    nouv->vitesseAttaque = 1.5;
    nouv->degats = 250;
    nouv->portee = 1;
    nouv->vitessedeplacement = 2;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->coutEnElixir = 2;
    return nouv;
}

Tunite *creeArcher(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = archer;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = sol;
    nouv->pointsDeVie = 80;
    nouv->vitesseAttaque = 0.7;
    nouv->degats = 120;
    nouv->portee = 3;
    nouv->vitessedeplacement = 1.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->coutEnElixir = 2;
    return nouv;
}

Tunite *creeDragon(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = dragon;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = air;
    nouv->pointsDeVie = 200;
    nouv->vitesseAttaque = 1.1;
    nouv->degats = 70;
    nouv->portee = 2;
    nouv->vitessedeplacement = 2.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->coutEnElixir = 3;
    return nouv;
}

Tunite *creeGargouille(int posx, int posy){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = gargouille;
    nouv->cibleAttaquable = solEtAir;
    nouv->maposition = air;
    nouv->pointsDeVie = 80;
    nouv->vitesseAttaque = 0.6;
    nouv->degats = 90;
    nouv->portee = 1;
    nouv->vitessedeplacement = 3.0;
    nouv->posX = posx;
    nouv->posY = posy;
    nouv->coutEnElixir = 1;
    return nouv;
}

>>>>>>> Stashed changes
/*
    TuniteDuJeu nom;
    Tcible cibleAttaquable;	//indique la position des unités que l’on peut attaquer
    Tcible maposition;		//indique soit « air » soit « sol », utile pour savoir
                            //qui peut nous attaquer
    int pointsDeVie;
    float vitesseAttaque;	//en seconde, plus c’est petit plus c’est rapide
    int degats;
    int portee ;			//en mètre, distance sur laquelle on peut atteindre une
                            //cible

    float vitessedeplacement;	//en m/s
    int posX, posY;			//position sur le plateau de jeu

    int coutEnElixir;
*/
/****************** Encapsulation de mes couilles ******************/

TuniteDuJeu getUnitName(Tunite unit){
    return unit->nom;
}
Tcible getUnitTarget(Tunite unit){
    return unit->cibleAttaquable;
}
Tcible getTargetCategory(Tunite unit){
    return unit->maposition;
}
int getHPLeft(Tunite unit){
    return unit->pointsDeVie;
}
float getAttackDelay(Tunite unit){
    return unit->vitesseAttaque;
}
int getDamage(Tunite unit){
    return unit->degats;
}
int getRange(Tunite unit){
    return unit->portee;
}
int getMoveSpeed(Tunite unit){
    return unit->vitessedeplacement;
}
int getPosX(Tunite unit){
    return unit->posX;
}
int getPosY(Tunite unit){
    return unit->posY;
}
int getElixirCost(Tunite unit){
    return unit->coutEnElixir;
}


void setUnitName(Tunite unit, TuniteDuJeu name){
    unit->nom = name;
}
void setUnitTarget(Tunite unit, Tcible target){
    unit->cibleAttaquable = target;
}
void setTargetCategory(Tunite unit, Tcible position){
    unit->maposition = position;
}
void setHPLeft(Tunite unit, int hp){
    unit->pointsDeVie = hp;
}
void setAttackDelay(Tunite unit, int atkdelay){
    unit->vitesseAttaque = atkdelay;
}
void setDamage(Tunite unit, int dmg){
    unit->degats = dmg;
}
void setRange(Tunite unit, int range){
    unit->portee, range;
}
void setMoveSpeed(Tunite unit, int movespeed){
    unit->vitessedeplacement = movespeed;
}
void setPosX(Tunite unit, int posx){
    unit->posX = posx;
}
void setPosY(Tunite unit, int posy){
    unit->posY = posy;
}
void setElixirCost(Tunite unit, int elixircost){
    unit->coutEnElixir = elixircost;
}


/*******************************************************************/

void PositionnePlayerOnPlateau(TListePlayer player, TplateauJeu jeu, Tunite* UnitList, int whichPlayer){
    int i, j, n, movesLeft, rand;
    Tunite unit;
    nbUnit = lenList(player);
    srand(time(NULL));
    rand = rand()%2;
    for(i=0;i<n;i++){
        unit = UnitList[player[i].pdata];
        movesLeft = unit.vitessedeplacement;
        for(j=0;j<movesLeft;j++){
            if(unit.posY != 3 && whichPlayer == 1){
                if(jeu[unit.posX][unit.posY+1] == NULL){

                }
            }
            if(unit.posY == 15 && whichPlayer == 2){

            }
            if(unit.posX == 5){

            }
            if(unit.posX>=5){

            } else if(unit.posX<=5){

            }
        }
    }
}






