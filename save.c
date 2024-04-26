#include <stdio.h>
#include <stdlib.h>

#include "save.h"
#include "clashloyal.h"
#include "type.h"

void saveSeq(TListePlayer player1, TListePlayer player2){
    FILE *file = fopen("partieseq.txt", "w");
    TListePlayer current = player1;
    while (!(isEmptyList(current))) { /* hmmmmmm */
        fprintf(file, "%d %d %d %d %d %d %d %f %d %d %d\n",
            getUnitName(getData(current)), getUnitTarget(getData(current)), getTargetCategory(getData(current)),
            getHPLeft(getData(current)), getAttackDelay(getData(current)), getDamage(getData(current)),
            getRange(getData(current)), getMoveSpeed(getData(current)),
            getPosX(getData(current)), getPosY(getData(current)),
            getElixirCost(getData(current)));
        current = getNextCell(current);
    };
    current = player2;
    while (!(isEmptyList(current))) {
        fprintf(file, "%d %d %d %d %d %d %d %f %d %d %d\n",
            getUnitName(getData(current)), getUnitTarget(getData(current)), getTargetCategory(getData(current)),
            getHPLeft(getData(current)), getAttackDelay(getData(current)), getDamage(getData(current)),
            getRange(getData(current)), getMoveSpeed(getData(current)),
            getPosX(getData(current)), getPosY(getData(current)),
            getElixirCost(getData(current)));
        current = getNextCell(current);
    };
    fclose(file);
}
void saveBin(TListePlayer player1, TListePlayer player2){
    FILE *file = fopen("partiebin.txt", "wb");
    TListePlayer current = player1;
    while (!isEmptyList(current)) {
        fwrite(getData(current), sizeof(Tunite), 1, file);
        current = getNextCell(current);
    };
    Tunite * finListe1 = NULL;
    fwrite(finListe1, sizeof(Tunite), 1, file);
    current = player2;
    while (!isEmptyList(current)) {
        fwrite(getData(current), sizeof(Tunite), 1, file);
        current = getNextCell(current);
    };
    fclose(file);
}
void loadSeq(TListePlayer *player1, TListePlayer *player2){  // &(D.data) ou (&D)->data
    FILE *file = fopen("partieseq.txt", "r");
    char buffer[1024];
    int finListe1 = 0;
    Tunite data;
    while (fscanf(file, "%d %d %d %d %d %d %f %d %d %d\n",
              &data.nom, &data.cibleAttaquable, &data.maposition,
              &data.pointsDeVie, &data.vitesseAttaque, &data.degats,
              &data.portee, &data.vitessedeplacement,
              &data.posX, &data.posY,
              &data.coutEnElixir) != EOF) {
    player1=addFirst(player1, &data);
    };
    fclose(file);
}

void loadBin(TListePlayer *player1, TListePlayer *player2){
    FILE *file = fopen("partiebin.txt", "rb");
    initList(player1);
    initList(player2);
    TListePlayer *current = player1;
    Tunite temp;
    while (fread(&temp, sizeof(Tunite), 1, file)) {
        addLast(*current,&temp);
        current=getNextCell(current);
    }
    current = player2;
    while (fread(&temp, sizeof(Tunite), 1, file)) {
        addLast(*current,&temp);
        current=getNextCell(current);
    }
    fclose(file);
}
