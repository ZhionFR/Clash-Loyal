## TBD :

### Error Codes
 - [ ] Doc with all error codes (exit(ErrorCode)) with error code an int (except 1, 2, 127, 132, 133, 134, 136, 137, 138, 139, 152, 153, 158, 159)

### Comments : 
 - [ ] List
   - [ ] .c
   - [ ] .h
 - [ ] ClashLoyal
   - [ ] .c
   - [ ] .h
 - [ ] Main
   - [ ] .c

### Attack phase
 - [ ] Bool tourRoiDetruite(TListePlayer player);
 - [ ] TListePlayer quiEstAPortee(TListePlayer player, Tunite *uneUniteDeLautreJoueur);
   - [ ] (Not Required) sort by AtkSpeed
 - [ ] TListePlayer combat(TListePlayer player, Tunite *uneUniteDeLautreJoueur);
 - [ ] Void supprimerUnite(TListePlayer *player, Tunite *UniteDetruite);

### Move phase
 - [ ] void PositionnePlayerOnPlateau(TListePlayer player, TplateauJeu jeu);

### Create Phase
 - [ ] Tunite AcheteUnite(int *elixirEnStockduJoueur);
   - [X] Tunite *creeArcher(int posx, int posy);
   - [X] Tunite *creeGargouille(int posx, int posy);
   - [X] Tunite *creeDragon(int posx, int posy);
   - [X] Tunite *creeChevalier(int posx, int posy);
 - [ ] Void AjouterUnite(TListePlayer *player, Tunite *nouvelleUnite);

### Menu-ing
 - [ ] Save
 - [ ] Load
