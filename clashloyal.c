#include "SDL.h"
#include "clashloyal.h"
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
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

/****************** Set functions ******************/

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

/****************** Creating Units ******************/

Tunite *createUnit(TuniteDuJeu name, Tcible target, Tcible targetCategory, int MaxHP, float atkDelay, int damage, int range, float movementSpeed, int posX, int posY, int elixirCost){
    Tunite *nouv = (Tunite*)malloc(sizeof(Tunite));
    nouv->nom = name;
    nouv->cibleAttaquable = target;
    nouv->maposition = targetCategory;
    nouv->pointsDeVie = MaxHP;
    nouv->vitesseAttaque = atkDelay;
    nouv->degats = damage;
    nouv->portee = range;
    nouv->vitessedeplacement = movementSpeed;
    nouv->posX = posX;
    nouv->posY = posY;
    nouv->coutEnElixir = elixirCost;
    return nouv;
}

Tunite *creeTour(posx, posy){
    return createUnit(tour, solEtAir, sol, 500, 1.0, 100, 3, 0, posx, posy, 0);
}
Tunite *creeTourRoi(posx, posy){
    return createUnit(tourRoi, solEtAir, sol, 800, 1.2, 120, 4, 0, posx, posy, 0);
}
Tunite *creeChevalier(posx, posy){
    return createUnit(chevalier, sol, sol, 400, 1.5, 250, 1, 2.0, posx, posy, 4);
}
Tunite *creeArcher(posx, posy){
    return createUnit(archer, solEtAir, sol, 80, 0.7, 120, 3, 1.0, posx, posy, 2);
}
Tunite *creeDragon(posx, posy){
    return createUnit(name, solEtAir, air, 200, 1.1, 70, 2, 2.0, posx, posy, 3);
}
Tunite *creeGargouille(posx, posy){
    return createUnit(name, solEtAir, air, 80, 0.6, 90, 1, 3.0, posx, posy, 1);
}



void PositionnePlayerOnPlateau(TListePlayer player, TplateauJeu jeu, Tunite* UnitList, int whichPlayer){

}






