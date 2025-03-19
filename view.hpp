#ifndef VIEW_HPP
#define VIEW_HPP


#include <iostream>

//void print_square(char piece);

void set_background(int i, int j);
void set_foreground(char piece);
void print_square_color(char piece, int i, int j);
void print_board(char plateau[T][T]);


//MASK
void set_background(int i, int j, char mask);
void print_square_color(char piece,char mask, int i, int j);
void print_board(char plateau[T][T], char mask[T][T]);
void jeu_choices_menu();
void mask_choices_menu();
#endif