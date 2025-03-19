#ifndef GAME_HPP
#define GAME_HPP


#include <iostream>


bool one_run_human(char plateau[T][T], bool couleur,historique **Tetehisto);
void one_run_computer(char plateau[T][T], bool couleur, historique **Tetehisto);


int jeu_choices();
#endif