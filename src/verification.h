#ifndef __VERIFICATION_H
#define __VERIFICATION_H

#include "sudoku.h"
#include "lecture.h"


// Vider un tableau
void vider_tableau (int *T, int len) ;

// V�rifier si les nombres initialis�s sont toujours pr�sents.
int verifier_nombre (Sudoku S1, Sudoku S2);

// v�rifier si une colonne contient les nombres de 1 � N.
// retourne 1 si Vraie, 0 si Faux.
int verifier_ligne (Sudoku S, int ligne);

// v�rifier si une colonne contient les nombres de 1 � N.
// retourne 1 si Vraie, 0 si Faux.
int verifier_colonne (Sudoku S, int colonne);

// v�rifier si un bloc carr� contient les nombres de 1 � N.
// retourne 1 si Vraie, 0 si Faux.
int verifier_bloc_carre (Sudoku S, int a, int b);

// v�rifier si un bloc contient les nombres de 1 � N.
// retourne 1 si Vraie, 0 si Faux.
int verifier_bloc (Sudoku S, int numbloc);

// v�rifier si la somme des valeurs d'une zone correspond bien.
// retourne 1 si Vraie, 0 si Faux.
int verifier_somme (Sudoku S, int numsum);

//v�rifier si la comparaison entre 2 cases est juste.
// retourne 1 si Vraie, 0 si Faux.
int verifier_comparaison(Sudoku S, int numcomp);

// Fonction v�rification Sudoku : renvoie 0 si incorrect et 1 si correct.
int verification_sudoku (Sudoku S1, Sudoku S2);

// Fonction v�rification Jigsaw : renvoie 0 si incorrect et 1 si correct.
int verification_jigsaw (Sudoku S1, Sudoku S2);

// Fonction v�rification Killer-Sudoku : renvoie 0 si incorrect et 1 si correct.
int verification_killer (Sudoku S1, Sudoku S2);

// Fonction v�rification  Comparision-Sudoku : renvoie 0 si incorrect et 1 si correct.
int verification_comparaision (Sudoku S1, Sudoku S2);

// Fonction v�rification : renvoie 0 si incorrect et 1 si correct.
int verification (Sudoku S1, Sudoku S2) ;

#endif
