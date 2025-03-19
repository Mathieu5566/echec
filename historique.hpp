#ifndef HISTORIQUE_HPP
#define HISTORIQUE_HPP


#include <iostream>

void MAJ_historique(historique **Tetehisto,int xDep, int yDep, int xArr, int yArr, char piece);
int play_historique(historique *Tetehisto, char mask[T][T]);

int backtrack_historique(historique **Tetehisto, char mask[T][T], char plateau[T][T]);
#endif