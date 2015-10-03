#ifndef __REMPLISSAGE_H
#define __REMPLISSAGE_H

#include <stdio.h>
#include <stdlib.h>

#include "sudoku.h"

#define VARIABLE(x,y,z,n) ((x*n*n)+(y*n)+z)

void remplissage (Sudoku * S);


void remplissageSudoku (Sudoku * S);

void remplissageSudokuKiller (Sudoku * S);


void remplissageSudokuJigsaw (Sudoku * S);


void remplissageSudokuComparison (Sudoku * S);


void reglesBases(Sudoku * S);


void uniciteBloc(Sudoku * S);

#endif
