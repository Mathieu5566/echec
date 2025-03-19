#ifndef MASK_HPP
#define MASK_HPP


#include <iostream>

const char CLASSIQUE = '0';//Transparent
const char ATTAQUABLE = '1';//ROUGE
const char NON_ATTAQUABLE = '2';//VERT
const char PEUX_PRENDRE = '3';//MARON
const char DEPLACEMENT_POSSIBLE = '4'; //BLEU
const char PIECE_SELECT = '5';//VIOLET
const char PIECE_JOUABLE = '6';//VERTCLAIRE
const char GRIS = '7';//GRIS



void empty_mask();
void clear_mask(char mask[T][T]);
char get_mask(char mask[T][T], int ligne, int col);
void set_mask(char mask[T][T]);
void highlight_possible_moves_king(char plateau[T][T],char mask[T][T], int x, int y);

bool DansPlateau(int x, int y);
void highlight_possible_moves(char plateau[T][T],char mask[T][T], int x, int y);
void highlight_possible_moves_rook(char plateau[T][T],char mask[T][T], int x, int y);
void highlight_possible_moves_bishop(char plateau[T][T],char mask[T][T], int x, int y);
void highlight_possible_moves_knight(char plateau[T][T],char mask[T][T], int x, int y);

void highlight_possible_moves_pawn(char plateau[T][T],char mask[T][T], int x, int y);

void  highlight_movable_pieces(char plateau[T][T],char mask[T][T],bool couleur);
void  highlight_attacked_pieces(char plateau[T][T],char mask[T][T], bool couleur);

void  highlight_take_pieces(char plateau[T][T],char mask[T][T], int x, int y);
bool maskes_choices(char plateau[T][T], char mask[T][T], bool couleur);
#endif