#include "board.hpp"
#include "view.hpp"
#include "mask.hpp"
#include "types.hpp"
#include "historique.hpp"
#include "game.hpp"


#include <fstream>
#include <string> 
#include <iostream>
#include <random>
using namespace std;

random_device dev;
mt19937 rng(dev());
void one_run(){}

bool one_run_human(char plateau[T][T], bool couleur, historique **Tetehisto){
  int x,xArr;
  char y, yArr;
  char maskPIECE_SELECT[T][T];
  char maskDEPLA_POSSI[T][T];
  

  
  highlight_movable_pieces(plateau, maskPIECE_SELECT, couleur);
  do{
    cout<<"Case de la pièce que vous souhaitez bouger : "; //rajout de la fonction roi
    cin >>y >> x;
    x = 8 - x;
    y = (int)y - 'a';
    if(maskPIECE_SELECT[x][y] != PIECE_JOUABLE){
      cout<<"Cette pièce ne peut pas être jouée"<<endl;}
  } while( !DansPlateau(x, y) or (get_couleur(plateau[x][y]) != couleur) or  plateau[x][y] ==VIDE or maskPIECE_SELECT[x][y] != PIECE_JOUABLE);
  
    highlight_possible_moves(plateau, maskDEPLA_POSSI, x, y);
    do{
      cout<<endl<<"Case sur laquelle vous souhaitez mettre votre pièce : ";
      cin >>yArr>> xArr;
      xArr = 8 - xArr;
      yArr = (int)yArr - 'a';
    }while( !DansPlateau(x, y) or maskDEPLA_POSSI[xArr][yArr] != DEPLACEMENT_POSSIBLE);
    
    if(plateau[xArr][yArr] == VIDE){
      move_char(plateau, x, y,xArr, yArr);
      MAJ_historique(Tetehisto, x, y, xArr, yArr, plateau[x][y]);} 
    else{
      //ajouté au score
      set_square(plateau,xArr, yArr, VIDE);//détruire pièce
      move_char(plateau, x, y,xArr, yArr);
      MAJ_historique(Tetehisto, x, y, xArr, yArr, plateau[x][y]);}
      return false;}














int jeu_choices(){
  /*Coix dans le menu du jeu*/
  int choix;
  do{
    cout << "Votre choix : ";
    cin>>choix;}while(choix <1 or choix >4);
    return choix;}
      
  
  



struct PieceMoveOrdi{int coord[2];
                      PieceMoveOrdi *next;};





int parcourir_tableau(char plateau[T][T], char mask[T][T], PieceMoveOrdi **pile, char maskDemande){
  /*Transforme les élement demandé en liste chainé*/
  int cpt = 0;  
  PieceMoveOrdi *ptr = new PieceMoveOrdi;
  *pile = ptr;
  //print_board(plateau, mask);
    for (int i = 0; i < T; i++) {
      for (int j = 0; j < T; j++) {
        if (mask[i][j]  == maskDemande){
          ptr->next = new PieceMoveOrdi ;
          ptr = ptr->next ;
          ptr->coord[0] = i;
          ptr->coord[1] = j;
          cpt ++;
          }}}

  return cpt;}




void afficher_pile(PieceMoveOrdi *pile) {
  PieceMoveOrdi *piece = pile;
  while (piece != NULL) {
    cout << "Coordonnées: (" << piece->coord[0] << ", " << piece->coord[1] << ")" <<endl;
    piece = piece->next;}}




int Choicealea(int max){
  /*Choisit un nombre aléatoire en 1 et max*/
  uniform_int_distribution<> dist(1,max);
  return  dist(rng);}



bool choose_mouvement_computer(PieceMoveOrdi **pieceMove, int nb, char plateau[T][T] , historique **Tetehisto){
  /* Si il peut attrapé une pièce il l'attrape, sinon choisit aléatoirement*/
  PieceMoveOrdi *prec = *pieceMove;
  char maskT[T][T];
  clear_mask(maskT);
  PieceMoveOrdi *pileDepPossi = NULL;
 
  int c = 2, nbalea, nbalea2;
  int x, y;
  for(int i=0; i<T; i++){ //regarde si pièce attaquable
    for(int j=0; j<T; j++){
      clear_mask(maskT);
      if(plateau[i][j] != VIDE and get_couleur(plateau[i][j]) == 1){ //les pièce de notre camps
        highlight_possible_moves(plateau, maskT, i, j); //cacul déplacement possible des pièce du joueur en i j

        for(int x=0; x<T; x++){
          for(int y=0; y<T; y++){
            if(plateau[x][y] != VIDE){
              if(maskT[x][y] == DEPLACEMENT_POSSIBLE and get_couleur(plateau[x][y]) != 0 ){
                set_square(plateau,i, j, VIDE);
                move_char(plateau, x, y,i, j);
                MAJ_historique(Tetehisto, x, y,i, j, plateau[x][y]);
                return true;}}}}}}}
  
  //////////////////////////////////////
  clear_mask(maskT); //choisi pièce à aléatoirement
  if(nb >1){


    nbalea =  Choicealea(nb);

    for (int i = 0; i < nbalea; i++) {
        prec = prec->next;}

    x = prec->coord[0];
    y = prec->coord[1];
        
    highlight_possible_moves(plateau, maskT, x, y);//calcul déplacement possible
    int nbarrive = parcourir_tableau(plateau, maskT, &pileDepPossi, DEPLACEMENT_POSSIBLE);
     PieceMoveOrdi *prec2 = &*pileDepPossi;
    nbalea2 =  Choicealea(nbarrive);
    for (int i = 0; i < nbalea2; i++) {
        prec2 = prec2->next;}
    int xArr = prec2->coord[0];
    int yArr = prec2->coord[1];
    move_char(plateau, x, y,xArr, yArr);
    MAJ_historique(Tetehisto, x, y, xArr, yArr, plateau[x][y]);
    return true;
  }
  
  return false;}






void one_run_computer(char plateau[T][T], bool couleur, historique **Tetehisto){
  /*Donne aux fonctions les pièces qui peuvent bouger*/
  PieceMoveOrdi *pile = NULL;

  char maskPIECE_SELECT[T][T];
  clear_mask(maskPIECE_SELECT);
  highlight_movable_pieces(plateau, maskPIECE_SELECT, couleur);
  int nb = parcourir_tableau(plateau, maskPIECE_SELECT, &pile, PIECE_JOUABLE);
choose_mouvement_computer(&pile, nb, plateau , Tetehisto);
}


bool king_in_check(char plateau[T][T], bool couleur){
  int depPos =8;
  char mask[T][T];
  clear_mask(mask);
  int x, y;
  for(int i = 0; y < 8; y++){
    for(int j = 0; x < 8; x++){
      if(couleur){
        if(plateau[y][x] == 'N'){
          x = i;
          y = j;}}
      else{
        if(plateau[y][x] == 'n'){
          i = x;
          j = y;}}}}
  highlight_attacked_pieces(plateau,mask, !couleur);
  if(plateau[x][y] == ATTAQUABLE){
    cout<<"Votre roi semble en difficulté"<<endl;}
    int newX, newY;
    int coord[8][2] = {{-1,-1},{-1,0},{-1,1}, //coordonnées possible 
                     {0,-1},{0,1},
                     {1,-1},{1,0},{1,1}};
  
  for(int v=0; v<8; v++){
    newX = x+coord[v][0];
    newY = y+coord[v][1];
    for(int i=0; i<T; i++){ //regarde si pièce attaquable
      for(int j=0; j<T; j++){
      clear_mask(mask);
      if(plateau[i][j] != VIDE and get_couleur(plateau[i][j]) == !couleur){
        highlight_possible_moves(plateau, mask, i, j);
        if(mask[newX][newY]== DEPLACEMENT_POSSIBLE){
          depPos --;}}}}}

  if(depPos > 1){
    cout<<"Votre roi doit être déplacé :"<<endl;
    return false;}

  cout<<"Votre roi ne peut être déplacé";
  if(couleur){cout<<"Joueur 2 (noir) : Vous êtes en échec et mat. Vous avez perdu"<<endl;}
  return true;}

