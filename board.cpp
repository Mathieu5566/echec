#include "board.hpp"
#include "view.hpp"

#include <iostream>
#include <string> 
#include <fstream>

using namespace std;

void empty(char plateau[T][T]){
  /*Vide le plateau*/
  for(int i= 0; i< T; i++){
    for(int j= 0; j< T; j++){
      plateau[i][j] = VIDE;}}}




char get_square(char plateau[T][T], int ligne, int col){
  /*Recupere le contenu d'une case */
  return plateau[ligne][col];}//(int)(col-'a')


void set_square(char plateau[T][T],int lig, int col, char elt){
  /*modifie le contenu d'une case*/
  plateau[lig][col] = elt;}



void start(char plateau[T][T]){
  /*Initialise le plateau avec ses pièces*/
  char piece[8]={'r','n','b','q','k','b','n','r'};

  for(int i=0; i<8; i++ ){
    //NOIR
    set_square(plateau, 1, i, 'p');
    set_square(plateau, 0, i, piece[i] );//transforme en majuscule les pieces
    //BLANC
    set_square(plateau, 6, i, 'P');
    set_square(plateau, 7, i, (char)((int)piece[i] - 32));}}


bool move_char(char plateau[T][T],int depLig,int depCol,int arLig, int arCol){
  /*Deplace une pièce d'une case de départ à une case d'arrivé*/
  if (get_square(plateau, depLig, depCol) != VIDE){
    set_square(plateau, arLig, arCol, plateau[depLig][depCol]); //ajoute elt sur nouvelle pos
    set_square(plateau, depLig, depCol, VIDE); //supprime elt sur ancienne pos
    return true;}
  return false;}
  


 bool get_couleur(char elt){
  /*vérifie si une pièce est blanche ou non
  noir = true/1, blanc = false/0*/
  if(elt >= 'a' and elt <= 'z'){return true;}
  return false;}








//*****FEN*****


void write_FEN(char plateau[T][T],string fichierFEN){
 /* écrit le FEN d'un plateau dans fichierFEN*/
  ofstream f(fichierFEN, ios::app );
  int c =0;
   for(int i= 0; i< T; i++){
    c=0;
    for(int j= 0; j< T; j++){
      if(plateau[i][j] == VIDE){
        c++;
        if(j == T-1){
          (f)<<c;}}
      else{
        if(c != 0){
          (f)<<c;
          c=0;}
        (f)<<plateau[i][j];}}
     if(i != T-1){
      (f)<<"/";}}
  (f)<<endl;
  f.close();}



string read_FEN(string fichierFEN){
  /* Récupère la dernière ligne d'un fichier txt*/
  ifstream fichier(fichierFEN);
   if(fichier){
      string ligne, n;
      while(getline(fichier, ligne)){
        n= ligne;}
     return n;} 
    return 0;}



bool test_read_FEN(string fichierFEN, char fenTab[T][T]){
  /* Récupère la dernière ligne d'un fichier txt grace à read_FEN
     puis transforme la representation fen dans un plateau fenTab*/
  string fen = read_FEN(fichierFEN);
  int lig = 0, col = 0;
  int taille = fen.length();
  for(int i=0; i < taille; i++){
    if (fen[i] == '/'){
      lig ++;
      col =0;}
    else{
      if(fen[i] >= '1' and fen[i] <= '8'){ 
        for(int j = 0; j < int(fen[i]) - '0'; j++){
            fenTab[lig][col] = VIDE;
            col ++;}}
      else {
        fenTab[lig][col] = fen[i];
        col ++;}}
  }
  if(lig == 7 and col ==8){ return true;}//test si le fen donnée est valide
  return false;}




void clear_file(string fichierFEN){
  ofstream f(fichierFEN, ios::out);
  f.close();}

