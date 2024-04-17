#ifndef JEU2048_H_INCLUDED
#define JEU2048_H_INCLUDED

#define LARGEURJEU 11
#define HAUTEURJEU 19

#include "type.h"
#include <stdbool.h>


TplateauJeu AlloueTab2D(int largeur, int hauteur);
void initPlateauAvecNULL(TplateauJeu jeu,int largeur, int hauteur);
void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur);

/****************** Get functions ******************/

TuniteDuJeu getUnitName(Tunite* unit);
Tcible getUnitTarget(Tunite* unit);
Tcible getTargetCategory(Tunite* unit);
int getHPLeft(Tunite* unit);
float getAttackDelay(Tunite* unit);
int getDamage(Tunite* unit);
int getRange(Tunite* unit);
int getMoveSpeed(Tunite* unit);
int getPosX(Tunite* unit);
int getPosY(Tunite* unit);
int getElixirCost(Tunite* unit);
Tunite* getTarget(Tunite* unit);

/****************** Set functions ******************/

void setUnitName(Tunite* unit, TuniteDuJeu name);
void setUnitTarget(Tunite* unit, Tcible target);
void setTargetCategory(Tunite* unit, Tcible position);
void setHPLeft(Tunite* unit, int hp);
void setAttackDelay(Tunite* unit, int atkdelay);
void setDamage(Tunite* unit, int dmg);
void setRange(Tunite* unit, int range);
void setMoveSpeed(Tunite* unit, int movespeed);
void setPosX(Tunite* unit, int posx);
void setPosY(Tunite* unit, int posy);
void setElixirCost(Tunite* unit, int elixircost);
void setTarget(Tunite* unit, Tunite* cible);

/****************** Creating Units ******************/

int isEmptySlot(TplateauJeu jeu, int posx, int posy);
int findNewUnitPlace(TplateauJeu jeu, int whichplayer, int* posx, int* posy);
TListePlayer buyUnit(TplateauJeu jeu, TListePlayer* playerList, int* elixir, int whichplayer);

TListePlayer addKingTower(TplateauJeu jeu, TListePlayer* playerList, int whichplayer);
TListePlayer addBaseTower(TplateauJeu jeu, TListePlayer* playerList, int whichplayer);

Tunite *createUnit(TuniteDuJeu name, Tcible target, Tcible targetCategory, int MaxHP, int atkDelay, int damage, int range, int movementSpeed, int posX, int posY, int elixirCost);

Tunite *creeTour(int posx, int posy);
Tunite *creeTourRoi(int posx, int posy);
Tunite *creeChevalier(int posx, int posy);
Tunite *creeArcher(int posx, int posy);
Tunite *creeDragon(int posx, int posy);
Tunite *creeGargouille(int posx, int posy);
Tunite *creeEmpty(int posx, int posy);


TListePlayer addUnitToGame(TplateauJeu jeu, TListePlayer* playerList, Tunite* unit);

/****************** Updating Game ******************/

void updatePlayer(TplateauJeu jeu, TListePlayer playerList, int whichPlayer, TListePlayer enemyPlayerList, int time);
void updateUnit(TplateauJeu jeu, Tunite* unit, int whichPlayer, TListePlayer enemyPlayerList, int time);

/*************** GetNewTarget ***************/
int dist(int Xa, int Ya, int Xb, int Yb);
Tunite* getIfTarget(Tunite* unit, Tunite* target);
Tunite* getNewTarget(Tunite* unit, TListePlayer enemyPlayer, Tunite* target);

/***************** KillUnit *****************/

TListePlayer killUnit(Tunite* unit, TListePlayer playerList, TplateauJeu jeu);

/***************** MoveUnit *****************/

void moveUnit(TplateauJeu jeu, Tunite* unit, int whichplayer);

/****************** THE END ******************/

int isKingDead(T_List l);

#endif // JEU2048_H_INCLUDED
