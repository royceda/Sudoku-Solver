#ifndef __VERIFICATION_H
#define __VERIFICATION_H

#include "sudoku.h"
#include "lecture.h"


// Vider un tableau
void vider_tableau (int *T, int len) ;

// Vérifier si les nombres initialisés sont toujours présents.
int verifier_nombre (Sudoku S1, Sudoku S2);

// vérifier si une colonne contient les nombres de 1 à N.
// retourne 1 si Vraie, 0 si Faux.
int verifier_ligne (Sudoku S, int ligne);

// vérifier si une colonne contient les nombres de 1 à N.
// retourne 1 si Vraie, 0 si Faux.
int verifier_colonne (Sudoku S, int colonne);

// vérifier si un bloc carré contient les nombres de 1 à N.
// retourne 1 si Vraie, 0 si Faux.
int verifier_bloc_carre (Sudoku S, int a, int b);

// vérifier si un bloc contient les nombres de 1 à N.
// retourne 1 si Vraie, 0 si Faux.
int verifier_bloc (Sudoku S, int numbloc);

// vérifier si la somme des valeurs d'une zone correspond bien.
// retourne 1 si Vraie, 0 si Faux.
int verifier_somme (Sudoku S, int numsum);

//vérifier si la comparaison entre 2 cases est juste.
// retourne 1 si Vraie, 0 si Faux.
int verifier_comparaison(Sudoku S, int numcomp);

// Fonction vérification Sudoku : renvoie 0 si incorrect et 1 si correct.
int verification_sudoku (Sudoku S1, Sudoku S2);

// Fonction vérification Jigsaw : renvoie 0 si incorrect et 1 si correct.
int verification_jigsaw (Sudoku S1, Sudoku S2);

// Fonction vérification Killer-Sudoku : renvoie 0 si incorrect et 1 si correct.
int verification_killer (Sudoku S1, Sudoku S2);

// Fonction vérification  Comparision-Sudoku : renvoie 0 si incorrect et 1 si correct.
int verification_comparaision (Sudoku S1, Sudoku S2);

// Fonction vérification : renvoie 0 si incorrect et 1 si correct.
int verification (Sudoku S1, Sudoku S2) ;

#endif
