#include "board.hpp"
#include "mask.hpp"
#include "view.hpp"



#include <fstream>
#include <string> 
#include <iostream>
using namespace std;

string pieceB[6] = {{"\u2654"},{"\u2655"},{"\u2656"},{"\u2657"},{"\u2658"},{"\u2659"}}; //piece d'échec blanche
string pieceN[6] ={{"\u265A"},{"\u265B"},{"\u265C"},{"\u265D"},{"\u265E"},{"\u265F"}};  //piece d'échec noir

char pieces[6] = {'k','q','r','b','n','p'};



void set_background(int i, int j){
  /* Définit la couleur de fond*/
  if((i + j) % 2 == 0){
        cout << "\033[40m";} //"\033[44m"40
    else{cout << "\033[47m";}}//"\033[42m"47   46

void set_foreground(char piece){
  /* Définit la couleur d'ine pièce*/
  int c=0;  //compteur qui permet de récuperer le code unicode
  if(piece == VIDE){
        cout << " "<<" ";}
  else{

    if(get_couleur(piece)){
      while(piece !=pieces[c]){c++;}
      cout << "\033[30m" << pieceN[c] << " ";} 
    else{
      while(piece !=(char)((int)pieces[c] - 32)){c++;}
      cout << "\033[37m" << pieceB[c] << " ";} 
      }  
    
    }


void print_square_color(char piece, int i, int j){
  /* Affiche la couleur de fond et de la pièce*/
  set_background(i, j);
  set_foreground(piece);}


void reset_colors() {
  /* Remet les couleurs par défaut*/
    cout << "\033[0m";}


void print_board(char plateau[T][T]){
  /*Affichage du plateau en couleur */
  cout <<endl<< "  ";
  for (int i = 0; i < T; i++){cout<<((char)((int)i+'a'))<<" ";}
  
  for (int i = 0; i < T; i++){
    cout <<endl<< T-i << " ";

    for (int j = 0; j < T; j++){
      print_square_color(plateau[i][j], i ,j);
      reset_colors();}
    cout<<T-i;}
  cout <<endl<< "  ";
  for (int i = 0; i < T; i++){cout<<((char)((int)i+'a'))<<" ";}
  cout << endl;}

/*################################################################################*/
//Partie affichage Mask:


void set_background(int i, int j, char mask){
  /* Définit la couleur de fond par rapport au mask*/
  if(mask==CLASSIQUE){
    set_background(i, j);}
  else if(mask==ATTAQUABLE){cout << "\033[41m";}//ROUGE
  else if(mask==NON_ATTAQUABLE){cout << "\033[42m";}//VERT
  else if(mask==PEUX_PRENDRE){cout << "\033[43m";}//\033[43m
  else if(mask==DEPLACEMENT_POSSIBLE){cout << "\033[44m";}//BLEU
  else if(mask==PIECE_SELECT){cout << "\033[45m";}//VIOLER
  else if(mask==PIECE_JOUABLE){cout << "\033[46m";}//VERTCLAIRE
  else if(mask==GRIS){cout << "\033[47m";}//"0;90m"
}

void print_square_color(char piece,char mask, int i, int j){
  /* Affiche la couleur de fond par rapport au mask et de la pièce*/
  set_background(i, j, mask);
  set_foreground(piece);}

void print_board(char plateau[T][T], char mask[T][T]){
  /*Affichage du plateau en couleur avec le mask */
  cout<<endl<<"\033[48;5;88m"<<"  ";
  for (int i = 0; i < T; i++){cout<<((char)((int)i+'a'))<<" ";}
  cout<<"  ";
  reset_colors();
  
  for (int i = 0; i < T; i++){
    cout <<endl<<"\033[48;5;88m"<< T-i << " ";
    reset_colors();
    for (int j = 0; j < T; j++){
      print_square_color(plateau[i][j], mask[i][j], i ,j);
      reset_colors();}
    
    cout<<"\033[48;5;88m"<<" "<<T-i;
    reset_colors();}

  cout<<endl<<"\033[48;5;88m"<<"  ";
  for (int i = 0; i < T; i++){cout<<((char)((int)i+'a'))<<" ";}
  cout<<"  ";
  reset_colors();
  cout << endl;}



void mask_choices_menu(){
  string ligne = " -----------------------------------------------";
  cout<<ligne<<endl;
  cout<<"|  1- Pièces pouvant ce déplacer.               |"<<endl
      <<"|  2- Pièces attaquables.                       |"<<endl
      <<"|  3- Déplacements possible d'une pièce.        |"<<endl
      <<"|  4- Une pièces que l'adversaire peut attaquer.|"<<endl
      <<"|  5- Quitter l'aide.                           |"<<endl
      <<"|  6- Menu du jeu.                              |"<<endl
      <<ligne<<endl;}




void jeu_choices_menu(){
  string ligne = " -----------------------------------------------";
  cout<<ligne<<endl;
  cout<<"|  1- Continuer la partie.                      |"<<endl
      <<"|  2- Revenir en arrière.                       |"<<endl
      <<"|  3- Arrêté la partie.                         |"<<endl
      <<ligne<<endl;}