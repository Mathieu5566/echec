#ifndef TYPES_HPP
#define TYPES_HPP


#include <iostream>



//struct game{
  struct piecePrise{char piece;
                    int nbPrise;};

  struct historique{char piece_deplace;
                    int coord_dep[2];
                    int coord_arr[2];
                   historique *next;};








//};


#endif


