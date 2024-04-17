#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED
#include "type.h"


typedef enum{tour, tourRoi, archer, chevalier, dragon, gargouille, Empty} TuniteDuJeu;
typedef enum{sol, solEtAir, air } Tcible;


typedef struct Tunite {
    TuniteDuJeu nom;
    Tcible cibleAttaquable;	//indique la position des unités que l’on peut attaquer
    Tcible maposition;		//indique soit « air » soit « sol », utile pour savoir
                            //qui peut nous attaquer
    int pointsDeVie;
    int vitesseAttaque;	//en nb de ticks, plus c’est petit plus c’est rapide
    int degats;
    int portee ;			//en mètre, distance sur laquelle on peut atteindre une
                            //cible
    struct Tunite* Target;

    int vitessedeplacement;	//en m/s
    int posX, posY;			//position sur le plateau de jeu

    int coutEnElixir;
} Tunite;


typedef struct T_Cell{
    struct T_Cell *next;
    struct T_Cell *prev;
    Tunite* pdata;              // Be careful to do a malloc before using this
} T_Cell;

typedef T_Cell *T_List;



typedef T_List TListePlayer;

typedef Tunite* ** TplateauJeu;  ////tableau a deux dimensions de largeur 11 et hauteur 19 contenant des pointeurs (Tunite*)




#endif // TYPE_H_INCLUDED
