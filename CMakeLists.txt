cmake_minimum_required(VERSION 3.10)
project(echec)


set(SRC main.cpp board.cpp view.cpp mask.cpp game.cpp historique.cpp)
set(HEADER board.hpp view.hpp mask.hpp game.hpp types.hpp historique.hpp)
add_executable(echec ${SRC} ${HEADER})