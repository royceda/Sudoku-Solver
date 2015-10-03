#include <stdio.h>
#include <stdlib.h>
#include "verification.h"

void vider_tableau (int *T, int len) {
  for (int i = 0; i < len; i = i + 1)
    T[i] = 0;
}

// Vérifier si les nombres initialisés sont toujours présents.
int verifier_nombre (Sudoku S1, Sudoku S2){
  int test;
  for (int i = 0 ; i < S1.Nrows ; i = i + 1){
    for (int j = 0 ; j < S1.Ncolumns ; j = j + 1){
      if ((S1.G[i][j]) > 0){
	test = (S1.G[i][j]) != (S2.G[i][j]);
	if (test != 0){
	  return  0;
	}
      }
    }
  }
  return 1;
}

// vérifier si une colonne contient les nombres de 1 à N.
// retourne 1 si Vraie, 0 si Faux.

int verifier_ligne (Sudoku S, int ligne){
  int compteur = 1;
  int tmp[N + 1];
  vider_tableau(tmp,N+1);
  for (int i = 0 ; i < S.Ncolumns ; i = i + 1){
    tmp[S.G[ligne][i]] = tmp[S.G[ligne][i]] + 1;
  }
  while ((tmp[compteur] == 1) && (compteur < N+1))
    compteur = compteur + 1;
  if (compteur != S.Nsymbol + 1)
    return 0;
  return 1;
}

// vérifier si une colonne contient les nombres de 1 à N.
// retourne 1 si Vraie, 0 si Faux.

int verifier_colonne (Sudoku S, int colonne){
  int compteur = 1;
  int tmp[N + 1];
  vider_tableau(tmp, N + 1);
  for (int i = 0 ; i < S.Nrows ; i = i + 1){
    tmp[S.G[i][colonne]] = tmp[S.G[i][colonne]] + 1;
  }
  while ((tmp[compteur] == 1) && (compteur < N+1))
    compteur = compteur + 1;
  if (compteur != S.Nsymbol + 1)
    return 0;
  return 1;
}


// vérifier si un bloc carré contient les nombres de 1 à N.
// retourne 1 si Vraie, 0 si Faux.

int verifier_bloc_carre (Sudoku S, int a, int b){
  int tmp[N+1];
  int compteur = 1 ;
  vider_tableau(tmp, N+1);
  for (int i = 0 ; i < racine(S.Nrows) ; i = i + 1){
    for (int j = 0 ; j < racine(S.Ncolumns) ; j = j + 1)
      {
	tmp[S.G[racine(S.Nrows) * a + i][racine(S.Ncolumns) * b + j]]++;
      }
	       
  }
  while ((tmp[compteur] == 1) && (compteur < N+1))
    {
      compteur = compteur + 1;
    }
  if (compteur != S.Nsymbol + 1)
    {
      return 0;
    }
  return 1;
}

// vérifier si un bloc contient les nombres de 1 à N.
// retourne 1 si Vraie, 0 si Faux.

int verifier_bloc (Sudoku S, int numbloc){                                                                     
  int tmp[N+1];
  int compteur = 1;
  vider_tableau(tmp, N+1);
  for (int i = 0 ; i < S.Nsymbol ; i = i + 1){
    tmp[S.G[S.RU.U[numbloc][i].x][S.RU.U[numbloc][i].y]]++ ;
  }
  while ((tmp[compteur] == 1) && (compteur < N+1))
    compteur = compteur + 1;
  if (compteur != S.Nsymbol + 1)
    return 0;
  return 1;
}

// vérifier si la somme des valeurs d'une zone correspond bien.
// retourne 1 si Vrai, 0 si Faux.

int verifier_somme (Sudoku S, int numsum){
    int somme = 0, i = 0;
    while ((S.RS.S[numsum][i].x != -1) && (i < SMAX)){
        somme = somme + (S.G[S.RS.S[numsum][i].x][S.RS.S[numsum][i].y]);
        i = i + 1;
    }
    if (somme != S.RS.Ssum[numsum])
        return 0;
    return 1;
}

//vérifier si la comparaison entre 2 cases est juste.
// retourne 1 si Vrai, 0 si Faux.

int verifier_comparaison(Sudoku S, int numcomp){
    int a = S.G[S.RO.O[numcomp].A.x][S.RO.O[numcomp].A.y];
    int b = S.G[S.RO.O[numcomp].B.x][S.RO.O[numcomp].B.y];
    switch (S.RO.O[numcomp].sign){
    case '<' :
      return (a < b);
      break;
    case '>' :
      return (a > b);
      break;      
    case '=' :
      return (a == b);
      break;
    case 'i' :
      return (a <= b);
      break;
    case 's' :
      return (a >= b);
      break;
    default:
      printf("Ceci n'est pas une comparaison");
    }
    return 0;
}


// Fonction vérification Sudoku : renvoie 0 si incorrect et 1 si correct.

int verification_sudoku (Sudoku S1, Sudoku S2) {
  if (S2.RS.Ssum[0] <= 0)
    return 0;
  if (!verifier_nombre(S1,S2)){   // vérifier si les nombres initialisés sont toujours présents.
    return 0;
    }
  for (int i = 0 ; i < S2.Nrows ; i = i + 1){
    if (!verifier_ligne(S2, i)){
      return 0;
    }
  }
  for (int i = 0 ; i < S2.Ncolumns ; i = i + 1){
    if (!verifier_colonne(S2, i)){
      return 0;
    }
  }
  for (int i = 0 ; i < racine(S2.Nrows) ;  i++) {
    for (int j = 0; j < racine(S2.Ncolumns) ; j++) {
      if (!(verifier_bloc_carre(S2, i, j))){
	return 0;
      }
    }
  }
  return 1;
}


// Fonction vérification Jigsaw : renvoie 0 si incorrect et 1 si correct.

int verification_jigsaw (Sudoku S1, Sudoku S2) {

  //gérer le sudoku vide (avec la règle S)
  if (S2.RS.Ssum[0] <= 0){
    printf("1");
    return 0;
  }

  if (!verifier_nombre(S1,S2)){     // vérifier si les nombres initialisés sont toujours présents.
    return 0;
  }
  for (int i = 0 ; i < S2.Nrows ; i = i + 1){
    if (!verifier_ligne(S2, i))
      return 0;
  }
  for (int i = 0 ; i < S2.Ncolumns ; i = i + 1){
    if (!verifier_colonne(S2, i))
      return 0;
  }
  for (int j = 0 ; j < S2.Nsymbol ; j = j + 1){
    if (!verifier_bloc(S2,j))
      return 0;
  }
  return 1;
}

// Fonction vérification Killer-Sudoku : renvoie 0 si incorrect et 1 si correct.

int verification_killer (Sudoku S1, Sudoku S2) {
  int numsum = 0;

  //gérer le sudoku vide (avec la règle S)
  if (S2.RS.Ssum[0] <= 0)
    return 0;

  for (int i = 0 ; i < S2.Nrows ; i = i + 1){
    if (!verifier_ligne(S2, i))
      return 0;
  }
  for (int i = 0 ; i < S2.Ncolumns ; i = i + 1){
    if (!verifier_colonne(S2, i))
      return 0;
  }
  for (int i = 0 ; i < racine(S2.Nrows) ;  i++) {
    for (int j = 0; j < racine(S2.Ncolumns) ; j = j + 1) {
      if (!verifier_bloc_carre(S2, i, j))
	return 0;
    }
  }
  while (S2.RS.Ssum[numsum]){
    if (!verifier_somme(S2, numsum))
        return 0;
    numsum = numsum + 1;
  }
  return 1;
}

// Fonction vérification  Comparision-Sudoku : renvoie 0 si incorrect et 1 si correct.

int verification_comparaision (Sudoku S1, Sudoku S2) {

  //gérer le sudoku vide (avec la règle O)
  if (S2.RO.O[0].A.x < 0)
    return 0;
  
  for (int i = 0 ; i < S2.Nrows ; i = i + 1){
    if (!verifier_ligne(S2, i))
      return 0;
  }
  for (int i = 0 ; i < S2.Ncolumns ; i = i + 1){
    if (!verifier_colonne(S2, i))
      return 0;
  }
  for (int i = 0 ; i < racine(S2.Nrows) ;  i++) {
    for (int j = 0; j < racine(S2.Ncolumns) ; j = j + 1) {
      if (!verifier_bloc_carre(S2, i, j))
	return 0;
    }
  }
  for (int i = 0 ; i < 2 * S2.Nrows * (S2.Ncolumns - 1) ; i = i + 1){
    if (!verifier_comparaison(S2, i))
      return 0;
  }
  return 1;
}

// Fonction vérification : renvoie 0 si incorrect et 1 si correct.

int verification (Sudoku S1, Sudoku S2) {
  switch (S1.nom){
  case ('s'):
    return verification_sudoku(S1,S2);
    break;
  case ('k'):
    return verification_killer(S1,S2);
    break;
  case ('j'):
    return verification_jigsaw(S1,S2);
    break;
  case ('c'):
    return verification_comparaision(S1,S2);
    break;
  default :
    printf("C'est pas un Sudoku comme on le veut.\n");
    return 0;
    break;
  }
}

