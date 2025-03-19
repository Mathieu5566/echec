#include "board.hpp"
#include "view.hpp"
#include "mask.hpp"

#include "types.hpp"
#include "game.hpp"

#include "historique.hpp"



#include <iostream>
#include <string> 
#include <fstream>
using namespace std;

// cd build/
// cmake ..
// make
// ./echec fen_write.txt fen_readd.txt


int main(int argc, char *argv[]){


  if (argc==0){return (EXIT_FAILURE);}
  string fichierFEN_read, fichierFEN_write;
  if (argc == 2){
    fichierFEN_read = ((string const)argv[1]);
    fichierFEN_write = fichierFEN_read;}
  else{
    fichierFEN_read = ((string const)argv[1]);
    fichierFEN_write = ((string const)argv[2]);}

  historique *Tetehisto = NULL;
  char plateau[T][T];
  char testFEN[T][T];
  char mask[T][T];
  bool NOIR = 1, BLANC = 0;
  bool JoueurActuel = BLANC;
  bool FirstJoueur;
  int choixJ, choixP, choixJreprise,choixS, choixD, ChoixMenuG, ChoixHisto, nbTour=0;

  empty(plateau);
  clear_mask(mask);


  
  
  
  cout<<endl<<"Dans quel configuration voulez vous jouer :"<<endl;
  cout<<"\t 1- Nouvel partie"<<endl
      <<"\t 2- Reprendre partie depuis sauvgarde"<<endl
      <<"\t Votre choix : ";
  cin >> choixP;
  cout<<"\n";

  
  cout<<"Dans quel configuration voulez vous jouer :"<<endl;
  cout<<"\t 1- HUMAIN vs HUMAIN"<<endl
      <<"\t 2- HUMAIN vs ORDINATEUR"<<endl
      <<"\t Votre choix : ";
  cin >> choixJ;
  cout<<"\n";

  if(choixP == 2){
    string choixDoc = fichierFEN_read;
    if(argc > 2){ //si plusieur fichier
      cout<<"Sur quel fichier ce trouve votre sauvgarde ? :"<<endl;
      cout<<"\t 1- "<<fichierFEN_read<<endl<<"\t 2- "<<fichierFEN_write<<endl<<"\t Votre choix : "; cin>> choixD;cout<<"\n";
      if(choixD == 2){choixDoc = fichierFEN_write;}}
    if(!test_read_FEN(choixDoc, plateau)){
      cout<<"Aucun plateau n'a pu être récupéré"<<endl;
      cout<<"\t1- Il n'existe pas"<<endl<<"\t2- Il est incomplet"<<endl;
      empty(plateau);start(plateau);}
    else{
      cout<<"Quel joueur doit reprendre votre partie :"<<endl;
      cout<<"\t1- Joueur 1 (blanc)"<<endl<<"\t2- Joueur 2 (noir)"<<endl<<"\t Votre choix : ";cin>> choixJreprise;
      if(choixJreprise == 2){JoueurActuel = NOIR;}}}

  else{start(plateau);}
  
  
  FirstJoueur = JoueurActuel;
  cout<<"Toutes les saisies de pièces se feront par couples (Lettre, Chriffre)."<<endl<<"\tPar exemple : 'b7' / 'f2' ..."<<endl;
  
  
  
  
  
  if(choixJ == 1){ //HUMAIN vs HUMAIN
      
    while(nbTour < 50){ //condition à ajouter d'arret
      cout<<endl<<"À vous de jouer ";
      if(JoueurActuel){cout <<"Joueur 2 (noir):"<<endl;}
      else{cout <<"Joueur 1 (blanc):"<<endl;}
      print_board(plateau, mask);
      mask_choices_menu();
        
      if(maskes_choices(plateau, mask, JoueurActuel)){ //ouverture du menu du jeu
        jeu_choices_menu();
         ChoixMenuG = jeu_choices();
          
        
        if(ChoixMenuG == 2){//fin de partie demandé
          clear_mask(mask);
          ChoixHisto = backtrack_historique(&Tetehisto, mask, plateau);
          if(ChoixHisto !=0){
            if(ChoixHisto % 2 == 0){
              JoueurActuel = FirstJoueur;}
            else{JoueurActuel = !FirstJoueur;}
            
            cout<<endl<<"À vous de jouer ";
            if(JoueurActuel){cout <<"Joueur 2 (noir):"<<endl;}
            else{cout <<"Joueur 1 (blanc):"<<endl;}}}
    
        
        if(ChoixMenuG == 3){//fin de partie demandé
          cout<<"Voulez-vous sauvegarder votre partie pour la reprendre plus tard ? :"<<endl;
          cout<<"\t 1- Oui"<<endl<<"\t 2- Non"<<endl<<"\t Votre choix : ";cin>> choixS;
          if(choixS == 1){
            write_FEN(plateau, fichierFEN_write);
            cout<<endl<<"\tVotre partie est enregistré sur : "<<fichierFEN_write
                <<endl<<"\tN'oubliez pas, le prochain joueur qui doit jouer est le joueur : Joueur ";
            if(JoueurActuel){cout<<"2 (noir)"<<endl;}
            else{cout<<"1 (blanc)"<<endl;}}
          return 0;}}
    
      clear_mask(mask);
      print_board(plateau, mask);
      one_run_human(plateau, JoueurActuel,&Tetehisto );
      JoueurActuel = !JoueurActuel;
      nbTour ++;} }



  
  if(choixJ == 2){ //HUMAIN vs ORDI

    
    while(nbTour < 50){ //condition à ajouter d'arret

        if(JoueurActuel == 1){
          cout<<"L'ordinateur à joué :"<<endl;
          one_run_computer(plateau, NOIR, &Tetehisto);}
    
   
      
      if(JoueurActuel == 0){
        cout<<endl<<"À vous de jouer Joueur 1 (blanc):";
     
            
        print_board(plateau, mask);
        mask_choices_menu();
      if(maskes_choices(plateau, mask, JoueurActuel)){ //ouverture du menu du jeu
        jeu_choices_menu();
         ChoixMenuG = jeu_choices();
          
        
        if(ChoixMenuG == 2){//fin de partie demandé
          ChoixHisto = backtrack_historique(&Tetehisto, mask, plateau);
          if(ChoixHisto !=0){
            if(ChoixHisto % 2 == 0){
              JoueurActuel = FirstJoueur;}
            else{JoueurActuel = !FirstJoueur;}
            
      
            if(JoueurActuel){
              cout<<"L'ordinateur à joué :"<<endl;
              one_run_computer(plateau, NOIR, &Tetehisto);}
            else{cout <<"À vous de jouer Joueur 1 (blanc):"<<endl;}}}
    
        
        if(ChoixMenuG == 3){//fin de partie demandé
          cout<<"Voulez-vous sauvegarder votre partie pour la reprendre plus tard ? :"<<endl;
          cout<<"\t 1- Oui"<<endl<<"\t 2- Non"<<endl<<"\t Votre choix : ";cin>> choixS;
          if(choixS == 1){
            write_FEN(plateau, fichierFEN_write);
            cout<<endl<<"\tVotre partie est enregistré sur : "<<fichierFEN_write
                <<endl<<"\tN'oubliez pas, le prochain joueur qui doit jouer est le joueur : Joueur ";
            if(JoueurActuel){cout<<"2 (noir)"<<endl;}
            else{cout<<"1 (blanc)"<<endl;}}
          return 0;}}

      //if(JoueurActuel == 0){
      clear_mask(mask);
      
      print_board(plateau, mask);
      one_run_human(plateau, JoueurActuel,&Tetehisto );//}

      }
      


      JoueurActuel = !JoueurActuel;}






    
  }







  
















  /*
  //INITIALISATION PLATEAU
  empty(plateau);
  start(plateau);
  //cout<<"Affichage de début de partie :"<<endl;
  //print_board(plateau);
  clear_mask(mask);
  
  

  print_board(plateau, mask);
  one_run_computer(plateau, 1);
  
  
  one_run_human(plateau,1);
  print_board(plateau, mask);
  
  //TEST mouvement

  cout<<"Affichage mouvement :"<<endl;
  
  //Modifie emplacement piece :
  move_char(plateau, 0, 1, 2, 2);
  move_char(plateau, 1, 6, 3, 6);
  
  move_char(plateau, 6, 1, 4, 1);
  move_char(plateau, 7, 2, 5, 0);
  
  print_board(plateau);
  cout<<endl;

  
  //TEST read fen
  cout<<"Test read fen : "<<endl;
  if(test_read_FEN(fichierFEN_read, testFEN)){
    print_board(testFEN);}
  else{cout<<"\tAucun FEN validé n'a pu être récupéré"<<endl;}
  cout<<endl;

  //TEST write fen
  cout<<"Test write fen : "<<endl;
  write_FEN(plateau, fichierFEN_write);
  cout<<"Plateau enregistré  sous format FEN dans "<<fichierFEN_write<<" : "<<read_FEN(fichierFEN_write)<<endl<<endl;
  
  //TEST MASK :
  cout<<"Test mask :"<<endl;
  clear_mask(mask);
  for(int j=0; j<T;j++){
    mask[j][1]=ATTAQUABLE;
    mask[j][2]=NON_ATTAQUABLE;
    mask[j][3]=PEUX_PRENDRE;
    mask[j][4]=DEPLACEMENT_POSSIBLE;
    mask[j][5]=PIECE_SELECT;
    mask[j][6]=PIECE_JOUABLE;
    mask[j][7]=GRIS;}
  print_board(plateau, mask);
  cout<<endl;


  
  //TEST MASK King:  
  cout<<"Test mask King :"<<endl;
  clear_mask(mask);
  move_char(plateau, 0, 4, 4, 5);
  highlight_possible_moves(plateau,mask, 4, 5);
  
  move_char(plateau, 7, 4, 3, 1);
  highlight_possible_moves(plateau,mask, 3, 1);
  
  
  print_board(plateau, mask);
  move_char(plateau, 4, 5, 0, 4);
  move_char(plateau, 3, 1, 7, 4);
  cout<<endl;

  
  //TEST MASK Rook:  
  cout<<"Test mask Rook :"<<endl;
  clear_mask(mask);
  
  move_char(plateau, 0, 0, 4, 4);
  highlight_possible_moves(plateau,mask, 4,4);
  print_board(plateau, mask);

  
  //TEST MASK Bishop:  
  cout<<"Test mask Bishop :"<<endl;
  start(plateau);
  clear_mask(mask);
  
  move_char(plateau, 0, 2, 4, 4);
  highlight_possible_moves(plateau,mask, 4,4);
  print_board(plateau, mask);
  move_char(plateau, 4, 4, 0, 2);

  //TEST MASK QUEEN:  
  cout<<"Test mask Queen :"<<endl;
  empty(plateau);
  start(plateau);
  clear_mask(mask);
  
  move_char(plateau, 0, 3, 4, 4);
  highlight_possible_moves(plateau,mask, 4,4);
  print_board(plateau, mask);

  //TEST MASK Knight:  
  cout<<"Test mask Knight :"<<endl;
  empty(plateau);
  start(plateau);
  clear_mask(mask);
  
  move_char(plateau, 0, 1, 5, 4);
  highlight_possible_moves(plateau,mask, 5,4);
  print_board(plateau, mask);


  //TEST MASK Pawn:  
  cout<<"Test mask Pawn :"<<endl;
  empty(plateau);
  start(plateau);
  clear_mask(mask);
  
  move_char(plateau, 6, 2, 2, 4);
  
  highlight_possible_moves(plateau,mask, 2,4);
  highlight_possible_moves(plateau,mask, 6,3);
  //highlight_possible_moves(plateau,mask, 1,1);
  move_char(plateau, 1, 6, 4, 1);
   highlight_possible_moves(plateau,mask, 4,1);
  print_board(plateau, mask);

   //TEST MASK highlight_movable_pieces:  
  cout<<"Test highlight_movable_pieces :"<<endl;
  empty(plateau);
  start(plateau);
  clear_mask(mask);
  
  move_char(plateau, 6, 3, 4, 4);
  
  highlight_movable_pieces(plateau,mask, 1);
  print_board(plateau, mask);
  

  //TEST highlight_attacked_pieces:  
  cout<<"Test highlight_attacked_pieces :"<<endl;
  empty(plateau);
  start(plateau);
  clear_mask(mask);
  move_char(plateau, 6, 1, 2, 1);
 move_char(plateau, 6, 3, 4, 4); 
  move_char(plateau, 7, 7, 3, 5);
 highlight_attacked_pieces(plateau,mask, 0);
  print_board(plateau, mask);



  //TEST  highlight_take_pieces:  
  cout<<"Test highlight_take_pieces :"<<endl;

  clear_mask(mask);
   
  highlight_take_pieces(plateau,mask, 2, 1);

  print_board(plateau, mask);
*/


//mask_choices_menu();
return 0;}