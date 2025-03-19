#include "board.hpp"
#include "view.hpp"
#include "mask.hpp"




#include <fstream>
#include <string> 
#include <iostream>
using namespace std;




void empty_mask(){/* inutile dans notre code*/}


void clear_mask(char mask[T][T]){
  /* réinitialise un masque aux valeurs 0(CLASSIQUE)*/
  for(int i= 0; i< T; i++){
    for(int j= 0; j< T; j++){
      mask[i][j] = CLASSIQUE;}}}



char get_mask(char mask[T][T], int ligne, int col){
  /*Recupere le contenu d'une case du mask*/
  return mask[ligne][col];}



void set_mask(char mask[T][T],int lig, int col, char elt){
  /*modifie le contenu d'une case*/
  mask[lig][col] = elt;}

bool DansPlateau(int x, int y){
  /* Vérifie si des coordonnées x et y sont présente dans le plateau*/
  if( (x < T) and (y <T)){
    if((x >=0) and (y >=0)){return true;}}
  return false;}




void highlight_possible_moves_king(char plateau[T][T],char mask[T][T], int x, int y){
  /* crée le masque correspondant au déplacement possible d'un roi*/
  //char mask_tempo[T][T];
  int newX, newY;
  int coord[8][2] = {{-1,-1},{-1,0},{-1,1}, //coordonnées possible 
                     {0,-1},{0,1},
                     {1,-1},{1,0},{1,1}};
  for(int i=0; i<8; i++){
    newX = x+coord[i][0];
    newY = y+coord[i][1];
    if( DansPlateau(newX, newY)){//test si coord toujours dans le plateau)
        if(plateau[newX][newY] == VIDE){
          mask[newX][newY] = DEPLACEMENT_POSSIBLE;} //si pas de piece
        else {if(get_couleur(plateau[x][y]) != get_couleur(plateau[newX][newY])){// si pièce camps adverse
          mask[newX][newY] = DEPLACEMENT_POSSIBLE;} 
  }}}}


void highlight_possible_moves_rook(char plateau[T][T],char mask[T][T], int x, int y){
  /* crée le masque correspondant au déplacement possible d'une tour*/
  int move = -1;//sens de déplacement négatif
  int newX = x + move;
  int newY = y + move;
  
  for(int i=0; i<2; i++){
    while( (DansPlateau(newX, y)) and (plateau[newX][y] == VIDE)){ //VERTICALE
      mask[newX][y] = DEPLACEMENT_POSSIBLE;
      newX += move;}
    if( (DansPlateau(newX, y)) and (get_couleur(plateau[x][y]) != get_couleur(plateau[newX][y]) )){mask[newX][y] = DEPLACEMENT_POSSIBLE;}

    while( (DansPlateau(x, newY)) and (plateau[x][newY] == VIDE)){ //HORIZONTALE
      mask[x][newY] = DEPLACEMENT_POSSIBLE;
      newY += move;}
    if( (DansPlateau(x, newY)) and (get_couleur(plateau[x][y]) != get_couleur(plateau[x][newY]) )){mask[x][newY] = DEPLACEMENT_POSSIBLE;}
    move = 1;//sens de déplacement positif
    newX = x + move;
    newY = y + move;}}









void highlight_possible_moves_bishop(char plateau[T][T],char mask[T][T], int x, int y){
  /* crée le masque correspondant au déplacement possible d'un fou*/
  
  int moveX = -1;//sens de déplacement négatif
  int moveY = -1;
  int newX = x + moveX;
  int newY = y + moveY;
  
  for(int i=0; i<2; i++){
    while( (DansPlateau(newX, newY)) and (plateau[newX][newY] == VIDE)){ //HAUT i = 0 : GAUCHE ; i=1 DROITE
      mask[newX][newY] = DEPLACEMENT_POSSIBLE;
      newX += moveX;
      newY += moveY;}
    if( (DansPlateau(newX, newY)) and (get_couleur(plateau[x][y]) != get_couleur(plateau[newX][newY]) )){mask[newX][newY] = DEPLACEMENT_POSSIBLE;}//si dernière case = pièce adverse

    newX = x + moveX*-1; // configure l'inverse
    newY = y + moveY*-1;// configure l'inverse
    while( (DansPlateau(newX, newY)) and (plateau[newX][newY] == VIDE)){ //BAS i = 0 : DROITE ; i=1 GAUCHE
      mask[newX][newY] = DEPLACEMENT_POSSIBLE;
      newX += moveX*-1;
      newY += moveY*-1;}
    if( (DansPlateau(newX, newY)) and (get_couleur(plateau[x][y]) != get_couleur(plateau[newX][newY]) )){mask[newX][newY] = DEPLACEMENT_POSSIBLE;}//si dernière case = pièce adverse
    moveX = -1;//sens de déplacement négatif
    moveY = 1;
    newX = x + moveX;
    newY = y + moveY;}}







void highlight_possible_moves_queen(char plateau[T][T],char mask[T][T], int x, int y){
  /* crée le masque correspondant au déplacement possible d'une reine*/
  highlight_possible_moves_rook(plateau, mask, x, y); //horizontale et verticale
  highlight_possible_moves_bishop(plateau, mask, x, y);} //Diagonale



void highlight_possible_moves_knight(char plateau[T][T],char mask[T][T], int x, int y){
  /*crée le masque correspondant au déplacement possible du cavalier*/
  int newX, newY;
  int coord[8][2] = { {-2,-1},{-2,1},//coordonnées possible 
                      {-1,-2},{-1,2},
                      {1,-2},{1,2},
                      {2,-1},{2,1}};
  for(int i=0; i<8; i++){
    newX = x+coord[i][0];
    newY = y+coord[i][1];
    if( DansPlateau(newX, newY)){//test si coord toujours dans le plateau)
        if(plateau[newX][newY] == VIDE){
          mask[newX][newY] = DEPLACEMENT_POSSIBLE;} //si pas de piece
        else {if(get_couleur(plateau[x][y]) != get_couleur(plateau[newX][newY])){// si pièce camps adverse
          mask[newX][newY] = DEPLACEMENT_POSSIBLE;} 
  }}}}

bool ligneDepPawn(bool couleur, int x, int y){
  /*Regarde si un pion est bien sur sa ligne de départ*/
  if(couleur){
    if(x == 1){return true;}}
  else{if(x == 6){return true;}}
  return false;}


void highlight_possible_moves_pawn(char plateau[T][T],char mask[T][T], int x, int y){
  /*crée le masque correspondant au déplacement possible d'un pion*/
  bool couleur = get_couleur(plateau[x][y]);
  int sens;
  if(couleur){sens = -1;}
  else {sens = 1;}
  
  if (DansPlateau(x-sens, y)){
    if(plateau[x-sens][y] == VIDE){
      mask[x-sens][y] = DEPLACEMENT_POSSIBLE;
      if(ligneDepPawn(couleur, x, y)){ //Si sur la ligne de départ
        if( plateau[x-(sens*2)][y] == VIDE ){ //si la case est dans le plateau ou quel correspond à l'adversaire //or (couleur != get_couleur(plateau[x-(sens*2)][y]))
          mask[x-(sens*2)][y] = DEPLACEMENT_POSSIBLE;}}}}
  int col = 1;
    for(int i=0; i<2; i++){ //fait les attaque en diagonale à 1 de dustance
      if(DansPlateau(x-sens, y-col) and plateau[x-sens][y-col] != VIDE){
        if(get_couleur(plateau[x][y]) != get_couleur(plateau[x-sens][y-col])){
          mask[x-sens][y-col] = DEPLACEMENT_POSSIBLE;}}
      col = -1;}}







void  highlight_movable_pieces(char plateau[T][T],char mask[T][T], bool couleur){
  /*toutes les pièces qui peuvent se déplacer au prochain coup*/
  char maskT[T][T];
  clear_mask(maskT);
  for(int i=0; i<T; i++){
    for(int j=0; j<T; j++){
      clear_mask(maskT);
      if(plateau[i][j] != VIDE and get_couleur(plateau[i][j]) == couleur){
        highlight_possible_moves(plateau, maskT, i, j); //cacul déplacement possible des pièce du joueur en i j
        int x=0, y =0;
         //print_board(plateau, maskT);
        while(maskT[x][y] != DEPLACEMENT_POSSIBLE and x < T){ //tant qu'on na pas trouvé un déplacement possible (pour prouvé que la pièce peut bougé)
          y ++; //ajout colonne
          if (y == T){
            x ++; y = 0;}} // ajout ligne
          if(DansPlateau(x, y) and maskT[x][y] == DEPLACEMENT_POSSIBLE){mask[i][j] = PIECE_JOUABLE;} //ajouté la piece au mask
      }}}}





void  highlight_attacked_pieces(char plateau[T][T],char mask[T][T], bool couleur){
  /*toutes les pièces qui peuvent être prises au prochain coup*/
  char maskT[T][T];
  clear_mask(maskT);
  
  for(int i=0; i<T; i++){
    for(int j=0; j<T; j++){
      clear_mask(maskT);
      if(plateau[i][j] != VIDE and get_couleur(plateau[i][j]) == couleur){ //les pièce de notre camps
        highlight_possible_moves(plateau, maskT, i, j); //cacul déplacement possible des pièce du joueur en i j
       // print_board(plateau, maskT);
        for(int x=0; x<T; x++){
          for(int y=0; y<T; y++){
            if(plateau[x][y] != VIDE){
              if(maskT[x][y] == DEPLACEMENT_POSSIBLE and get_couleur(plateau[x][y]) != couleur ){mask[x][y] = ATTAQUABLE;}//si ont peut ce déplacer sur une pièce adverse, ont peut l'attaquer
              else if(mask[x][y] != ATTAQUABLE and get_couleur(plateau[x][y]) != couleur ){mask[x][y] = NON_ATTAQUABLE;}//sinon non attaquable
            }}}
    }}}}




void  highlight_take_pieces(char plateau[T][T],char mask[T][T], int x, int y){
  /*toutes les pièces dangereuses à une pièce, c’est-à-dire celles qui peuvent prendre une pièce spécifiée du joueur*/
  char maskT[T][T];
  clear_mask(maskT);
  bool couleur = get_couleur(plateau[x][y]);
  mask[x][y]  = PIECE_SELECT;
  for(int i=0; i<T; i++){
    for(int j=0; j<T; j++){
      clear_mask(maskT);
      if(plateau[i][j] != VIDE and get_couleur(plateau[i][j]) != couleur){//si la pièce appartient à l'adversaire
        highlight_possible_moves(plateau, maskT, i, j); //calclul les déplacement possibile d'une pièce
       // print_board(plateau, maskT);
        if(maskT[x][y] == DEPLACEMENT_POSSIBLE){ //test sur les coordonnée demandé par le joueur
          mask[i][j] = PEUX_PRENDRE;} //la piece testé
            
            }}}}



bool maskes_choices(char plateau[T][T], char mask[T][T], bool couleur){
  /* Permet de choisir un mask, renvoie true si le joueur demande à consulter le menu principale*/
  int choix;
  int x;
  char y;
  cout << "Votre choix : ";
  do{
    cin>>choix;
    if(choix == 6){return true;}
    clear_mask(mask);
    if(choix == 1){
      highlight_movable_pieces(plateau,mask, couleur);
      print_board(plateau, mask);}
    if(choix == 2){
      highlight_attacked_pieces(plateau,mask, couleur);
      print_board(plateau, mask);}
    if(choix == 3){
      do{
        cout<<"Coordonnées de la pièce choisie : ";
        cin >>y>> x;
        x = 8 - x;
        y = (int)y - 'a';}
        while(plateau[x][y] == VIDE or get_couleur(plateau[x][y]) != couleur);
        
      highlight_possible_moves(plateau, mask, x, y);
      print_board(plateau, mask);}
      
      if(choix == 4){
        do{
          cout<<"Coordonnées de la pièce choisie : ";
          cin >>y>> x;
          x = 8 - x;
          y = (int)y - 'a';}
          while(plateau[x][y] == VIDE or get_couleur(plateau[x][y]) != couleur);
          highlight_take_pieces(plateau, mask, x, y);
          print_board(plateau, mask);}


    if(choix != 5){cout<<endl<<"Un autre Mask/Menu ? : ";}
  }while(choix != 5);
  return false;}












void highlight_possible_moves(char plateau[T][T],char mask[T][T], int x, int y){
  /* transfere vers les fonction mask associé au pièce*/
  char piece = plateau[x][y];
  mask[x][y]  = PIECE_SELECT;
  switch(piece){
  
    case 'k': highlight_possible_moves_king(plateau, mask, x, y);
    break;
    case 'K': highlight_possible_moves_king(plateau, mask, x, y);
    break;
    case 'r': highlight_possible_moves_rook(plateau, mask, x, y);
    break;
    case 'R': highlight_possible_moves_rook(plateau, mask, x, y);
    break;
    case 'b': highlight_possible_moves_bishop(plateau, mask, x, y);
    break;
    case 'B': highlight_possible_moves_bishop(plateau, mask, x, y);
    break;
    case 'q': highlight_possible_moves_queen(plateau, mask, x, y);
    break;
    case 'Q': highlight_possible_moves_queen(plateau, mask, x, y);
    break;    
    case 'n': highlight_possible_moves_knight(plateau, mask, x, y);
    break;
    case 'N': highlight_possible_moves_knight(plateau, mask, x, y);
    break;
    case 'p': highlight_possible_moves_pawn(plateau, mask, x, y);
    break;
    case 'P': highlight_possible_moves_pawn(plateau, mask, x, y);
    break;
  }}