#ifndef __ECRITURECNF_H
#define __ECRITURECNF_H

#include <stdio.h>
#include <stdlib.h>

#include "sudoku.h"
#include "remplissage.h"
#include "verification.h"

void sudoku2CNF (Sudoku S, char *nomFichier);


void remplissageClassique (Sudoku S, FILE *f);


void traductionReglesU (Sudoku S, FILE *f);


void traductionReglesO (Sudoku S, FILE *f);


void traductionReglesS (Sudoku S, FILE *f);


void traductionReglesSimplesS (Sudoku S, FILE *f);


void listeSomme(Sudoku S, int cpt, int len, int sum, int cpt2, int *Tmp, FILE *f);


int egalSomme (int *T, int len, int sum);


void traduireTableau (Sudoku S, int cpt, int cpt2, int *Tmp, FILE *f);
   

int longueurLigneS (Sudoku S, int ligne);


#endif
