#include "remplissage.h"

void remplissage (Sudoku * S){
  switch ((*S).nom){
  case ('s'):
    remplissageSudoku(S);
    break;
  case ('k'):
    remplissageSudokuKiller(S);
    break;
  case ('j'):
    remplissageSudokuJigsaw(S);
    break;
  case ('c'):
    remplissageSudokuComparison(S);
    break;
  default :
    printf("C'est pas un Sudoku comme on veut.\n");
    break;
  }
}

void remplissageSudoku (Sudoku * S){
  reglesBases(S);
  uniciteBloc(S);
}

void remplissageSudokuKiller (Sudoku * S){
  reglesBases(S);
  uniciteBloc(S);
}

void remplissageSudokuJigsaw (Sudoku * S){
  reglesBases(S);
}

void remplissageSudokuComparison (Sudoku * S){
  reglesBases(S);
  uniciteBloc(S);
}


void reglesBases(Sudoku * S){
  //Unicité lignes
  for (int i = 0 ; i < (*S).Nrows ; i++){
    for (int j = 0 ; j < (*S).Ncolumns ; j++){
      (*S).RU.U[(*S).RU.nbU][j].x = i;
      (*S).RU.U[(*S).RU.nbU][j].y = j;
    }
    (*S).RU.nbU++;
  }
  //Unicité colonnes
  for (int i = 0 ; i < (*S).Ncolumns ; i++){
    for (int j = 0 ; j < (*S).Nrows ; j++){
      (*S).RU.U[(*S).RU.nbU][j].x = j;
      (*S).RU.U[(*S).RU.nbU][j].y = i;
    }
    (*S).RU.nbU++;
  }
}


void uniciteBloc(Sudoku * S){
  int n = racine((*S).Nrows * (*S).Ncolumns), cpt;
  for (int carreL = 0 ; carreL < racine(n) ; carreL++){
    for (int carreC = 0 ; carreC < racine(n) ; carreC++){
      cpt = 0;
      for (int i = 0 ; i < racine(n) ; i++){
	for (int j = 0 ; j < racine(n) ; j++){
	  (*S).RU.U[(*S).RU.nbU][cpt].x = carreL*racine(n) + i;
	  (*S).RU.U[(*S).RU.nbU][cpt].y = carreC*racine(n) + j;
	  cpt++;
	}
      }
      (*S).RU.nbU++;
    }
  }
}
