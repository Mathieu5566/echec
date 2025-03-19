#include "board.hpp"
#include "view.hpp"
#include "mask.hpp"
#include "types.hpp"
#include "historique.hpp"


#include <fstream>
#include <string> 
#include <iostream>
using namespace std;

/*
void MAJ_historique(historique **historique,int xDep, int yDep, int xArr, int yArr, char piece){
  historique *elt = new historique;
  elt->coord_dep[0] = xDep;
  elt->coord_dep[1] = yDep;
  elt->coord_arr[0] = xArr;
  elt->coord_arr[1] = yArr;
  if (P == 1){
    elt->next = (*historique);
    *L = elt;}

  maillon *prec = *L;
  while (prec->next !=NULL){prec = prec->next;}
  elt->next = prec->next;
  prec->next = elt;
  return true;}
*/



void MAJ_historique(historique **Tetehisto,int xDep, int yDep, int xArr, int yArr, char piece){
    historique *nouveau = new historique;
    nouveau->piece_deplace = piece;
    nouveau->coord_dep[0] = xDep;
    nouveau->coord_dep[1] = yDep;
    nouveau->coord_arr[0] = xArr;
    nouveau->coord_arr[1] = yArr;
    nouveau->next = NULL;
    if (*Tetehisto == NULL) {
        *Tetehisto = nouveau;
        return;}
    
  historique *temp = *Tetehisto;
    while (temp->next != NULL) {
        temp = temp->next;}
    temp->next = nouveau;}



int play_historique(historique *Tetehisto, char mask[T][T]) {
    int cpt = 0;
    historique *temp = Tetehisto;
    char plateauHisto[T][T];
    empty(plateauHisto);
    start(plateauHisto);
    while (temp != NULL){
      //if(temp->next != NULL){
      cpt ++;
      cout<<endl<<"Historique : "<<cpt;
      move_char(plateauHisto, temp->coord_dep[0], temp->coord_dep[1], temp->coord_arr[0], temp->coord_arr[1]);
      
      print_board(plateauHisto, mask);
      temp = temp->next;
      //}
    }

      return cpt;}


void supprimer_apres_position(historique **tete, int position) {
    historique *courant = *tete;
    for (int i = 1; i < position; i++) {
        courant = courant->next;}
    courant->next = NULL;}



int backtrack_historique(historique **Tetehisto, char mask[T][T], char plateau[T][T]){
  int nb = play_historique(*Tetehisto, mask);
  int choix =0, cpt = 0;
  
  char plateauHisto[T][T];
  empty(plateauHisto);
  start(plateauHisto);
  
  if(nb == 0){cout<<"Vous ne pouvez pas revenir en arrière"<<endl;
             return false;}
  cout<< "À quelle version du plateau souhaité vous retournez ? (de 1 à "<<nb<<" ) : ";
  do {cin >>choix;}while (choix < 0 or choix > nb);
  
    historique *temp = *Tetehisto;

    while (cpt != choix){ 

      move_char(plateauHisto, temp->coord_dep[0], temp->coord_dep[1], temp->coord_arr[0], temp->coord_arr[1]);
      temp = temp->next;
      cpt ++;}
      cout<<endl<<"\tLa version numéro "<<choix<< " a été restaurée"<<endl;

  supprimer_apres_position(Tetehisto, choix);
  for(int i=0; i<T; i++){
      for(int j=0; j<T; j++){
        plateau[i][j] = plateauHisto[i][j];}}
  return choix;}