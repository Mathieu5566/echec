#ifndef BOARD_HPP
#define BOARD_HPP


#include <iostream>
#include <string>
using namespace std;



const char VIDE = '-';
const int T = 8;
void empty(char plateau[T][T]);
void afficherPlateau(char plateau[T][T]);//va devoir partir
char get_square(char plateau[T][T], int ligne, char col);
void set_square(char plateau[T][T],int lig, int col, char elt);
void start(char plateau[T][T]);
bool move_char(char plateau[T][T],int depLig,int depCol,int arLig, int arCol);
bool get_couleur(char elt);


//FEN

void write_FEN(char plateau[T][T],string fichierFEN);
string read_FEN(string fichierFEN);
void clear_file(string fichierFEN);
bool test_read_FEN(string fichierFEN, char fenTab[T][T]);



#endif