## TBD :

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
   - [ ] Tunite *creeArcher(int posx, int posy);
   - [ ] Tunite *creeGargouille(int posx, int posy);
   - [ ] Tunite *creeDragon(int posx, int posy);
   - [ ] Tunite *creeChevalier(int posx, int posy);
 - [ ] Void AjouterUnite(TListePlayer *player, Tunite *nouvelleUnite);

### Menu-ing
 - [ ] Save
 - [ ] Load
