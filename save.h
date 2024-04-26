#ifndef SAUVEGARDE_H_INCLUDED
#define SAUVEGARDE_H_INCLUDED
#include "type.h"

void saveSeq(TListePlayer player1, TListePlayer player2);
void saveBin(TListePlayer player1, TListePlayer player2);
void loadSeq(TListePlayer *player1, TListePlayer *player2);
void loadBin(TListePlayer *player1, TListePlayer *player2);

#endif // SAUVEGARDE_H_INCLUDED
