#ifndef __LECTURE_H
#define __LECTURE_H

#include "sudoku.h"
#include "remplissage.h"

// #define myscanf((nbtk),(file),(format),...) if(fscanf((file),(format),__VAR_ARGS__)!=(nbtk) { perror("fscanf"); exit(EXIT_FAILURE); }

//Procédure remplissant une grille de sudoku si il y a une seule règle S par ligne (si la règle S sert à placer un nombre dans une case)
void remplirGrille (Sudoku * S);

//Fonction pour lire le contenu d'un fichier et retourne un Sudoku
void lecture (Sudoku * S, char * Nom);

//Lit un fichier retourné par Glucose et remplit la grille avec
void lectureSAT (Sudoku * S, char * nomFichier);


#endif
