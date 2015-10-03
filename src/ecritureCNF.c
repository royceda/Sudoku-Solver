#include "ecritureCNF.h"

void sudoku2CNF (Sudoku S, char *nomFichier){
  FILE *f;
  
  char carac = 0;
  int nbLignes = 0;
  
  f = fopen(nomFichier, "w");
  remplissageClassique(S, f);
  switch (S.nom){
  case('s'):
    traductionReglesU(S, f);
    traductionReglesSimplesS(S, f);
    break;
  case('k'):
    traductionReglesU(S, f);
    traductionReglesS(S, f);
    break;
  case('j'):
    traductionReglesU(S, f);
    traductionReglesSimplesS(S, f);
    break;
  case('c'):
    traductionReglesU(S, f);
    traductionReglesO(S, f);
    break;
  default :
    printf("Ce n'est pas un Sudoku conforme.\n");
  }  
  fclose( f );

  //Calcul du nombre de lignes
  f = fopen(nomFichier, "r"); //Mode lecture seule
  rewind( f ); //Place le curseur au début du fichier
  while( carac != EOF )
    {
      carac = fgetc ( f );
      if (carac == '\n')
	{
	  nbLignes = nbLignes + 1;
	}
    }
   fclose(f);


   //Méthode adaptée d'une fonction d'openclassrooms (forum)
   //Permet d'écrire une ligne en début de fichier sans toucher au reste
   FILE * tmp = tmpfile(); //Ouvre un fichier temporaire (sera supprimé à sa fermeture)
   f = fopen(nomFichier, "r+"); //Lecture et écriture

   while( (carac = fgetc( f )) != EOF )
     {
       fputc(carac, tmp); //On recopie f dans tmp
     }

   rewind( f ); //On se remet au début des deux
   rewind( tmp );

   fprintf(f, "p cnf %d %d\n", S.Nsymbol*S.Nsymbol*S.Nsymbol, nbLignes); //On écrit la ligne p cnf ... ...
   
   while( (carac = fgetc( tmp )) != EOF )
     {
       fputc(carac, f); //On récrit tout ce qu'il y avait sauvegardé dans tmp
     }

   fclose(tmp); //on ferme tmp (est supprimé)
   fclose(f);   

}

void remplissageClassique (Sudoku S, FILE *f){
  // Valeur unique dans chaque cellule.
  
  for (int i = 0; i < S.Nrows; i++){
    for (int j = 0; j < S.Ncolumns; j++){
      for (int k = 1; k <= S.Nsymbol; k++)
	fprintf(f, "%d ", VARIABLE(i, j, k, S.Nsymbol));
      fprintf(f, "0\n");
    }
  }
  
  // Une seule valeur par cellule
  
  for (int i = 0; i < S.Nrows; i++){
    for (int j = 0; j < S.Ncolumns; j++){
      for (int k1 = 1; k1 <= S.Nsymbol; k1++){
	for (int k2 = 1; k2 < k1; k2++)
	  fprintf(f, "-%d -%d 0\n", VARIABLE(i, j, k1, S.Nsymbol), VARIABLE(i, j, k2, S.Nsymbol));
      }
    }
  }
}


void traductionReglesU (Sudoku S, FILE *f){
  int cpt2, i;
  //  if (S.Nsymbol <= 9){
    for (int cpt = 0 ; cpt < S.RU.nbU ; cpt ++){
      i = 0;
      while ((i < N) && (S.RU.U[cpt][i].x != -1)){
	for (int k = 1 ; k <= S.Nsymbol ; k++){
	  cpt2 = i + 1;
	  while ((cpt2 < N) && (S.RU.U[cpt][cpt2].x != -1)){
	    fprintf(f, "-%d -%d 0\n",VARIABLE(S.RU.U[cpt][i].x, S.RU.U[cpt][i].y, k, S.Nsymbol), VARIABLE(S.RU.U[cpt][cpt2].x, S.RU.U[cpt][cpt2].y, k, S.Nsymbol));
	    cpt2++;
	  }
	}
	i++;
      }
    }
    //}
  // gérer les sudoku classiques 16*16
  /*else{
    for (int cpt = 0 ; cpt < S.RU.nbU ; cpt ++){
      for (int k = 1 ; k <= S.Nsymbol ; k++){
	cpt2 = 0;
	while ((cpt2 < N) && (S.RU.U[cpt][cpt2].x != -1)){
	  fprintf(f, "%d ", VARIABLE(S.RU.U[cpt][cpt2].x, S.RU.U[cpt][cpt2].y, k, S.Nsymbol));
	  cpt2++;
	}
	fprintf(f, "0\n");
      }
    }
    }*/
}

void traductionReglesO (Sudoku S, FILE *f){
  for (int cpt = 0 ; cpt < S.RO.nbO ; cpt++){
    switch (S.RO.O[cpt].sign){
    case '<' :
      for (int i = 1 ; i <= S.Nsymbol ; i++){
	for (int j = 1 ; j <= i ; j++)
	  fprintf(f, "-%d -%d 0\n", VARIABLE(S.RO.O[cpt].A.x, S.RO.O[cpt].A.y, i, S.Nsymbol), VARIABLE(S.RO.O[cpt].B.x, S.RO.O[cpt].B.y, j, S.Nsymbol));
      }
      break;
    case '>' :
      for (int i = 1 ; i <= S.Nsymbol ; i++){
	for (int j = i ; j <= S.Nsymbol ; j++)
	  fprintf(f, "-%d -%d 0\n", VARIABLE(S.RO.O[cpt].A.x, S.RO.O[cpt].A.y, i, S.Nsymbol), VARIABLE(S.RO.O[cpt].B.x, S.RO.O[cpt].B.y, j, S.Nsymbol));
      }
      break;      
    case '=' :
      for (int i = 1 ; i <= S.Nsymbol ; i++){
	  fprintf(f, "-%d %d 0\n", VARIABLE(S.RO.O[cpt].A.x, S.RO.O[cpt].A.y, i, S.Nsymbol), VARIABLE(S.RO.O[cpt].B.x, S.RO.O[cpt].B.y, i, S.Nsymbol));
      }
      break;
    case 'i' :
      for (int i = 1 ; i <= S.Nsymbol ; i++){
	for (int j = 1 ; j < i ; j++)
	  fprintf(f, "-%d -%d 0\n", VARIABLE(S.RO.O[cpt].A.x, S.RO.O[cpt].A.y, i, S.Nsymbol), VARIABLE(S.RO.O[cpt].B.x, S.RO.O[cpt].B.y, j, S.Nsymbol));
      }
      break;
    case 's' :
      for (int i = 1 ; i <= S.Nsymbol ; i++){
	for (int j = i+1 ; j <= S.Nsymbol ; j++)
	  fprintf(f, "-%d -%d 0\n", VARIABLE(S.RO.O[cpt].A.x, S.RO.O[cpt].A.y, i, S.Nsymbol), VARIABLE(S.RO.O[cpt].B.x, S.RO.O[cpt].B.y, j, S.Nsymbol));
      }
      break;
    default:
      printf("Ceci n'est pas une comparaison.\n");
    }
  }
}

void traductionReglesS (Sudoku S, FILE *f){
  int cpt2, len;
  int Tmp[SMAX];
  for (int cpt = 0 ; cpt < S.RS.nbS ; cpt++){
    vider_tableau(Tmp, SMAX);
    cpt2 = 0;
    len = longueurLigneS(S, cpt);
    listeSomme(S, cpt, len, S.RS.Ssum[cpt], cpt2, Tmp, f);
  }
}

void traductionReglesSimplesS (Sudoku S, FILE *f){
  for (int cpt = 0 ; cpt < S.RS.nbS ; cpt++)
    fprintf(f, "%d 0\n", VARIABLE(S.RS.S[cpt][0].x, S.RS.S[cpt][0].y, S.RS.Ssum[cpt], S.Nsymbol));
}


void listeSomme(Sudoku S, int cpt, int len, int sum, int cpt2, int *Tmp, FILE *f){
  for (int i = 1 ; i <= S.Nsymbol ; i++){
    Tmp[cpt2] = i;
    if (len == 1){
      if (!(egalSomme(Tmp, cpt2 + 1 , S.RS.Ssum[cpt])))
	traduireTableau (S, cpt, cpt2, Tmp, f);
    }
    else 
      listeSomme(S, cpt, len-1, sum-i, cpt2+1, Tmp, f);
  }
}

int egalSomme (int *T, int len, int sum){
  int sum2 = 0;
  for (int i = 0 ; i < len ; i++)
    sum2 = sum2 + T[i];
  return (sum2 == sum);
}


void traduireTableau (Sudoku S, int cpt, int cpt2, int *Tmp, FILE *f){
  for (int i = 0 ; i <= cpt2 ; i++)
    fprintf(f, "-%d ", VARIABLE(S.RS.S[cpt][i].x, S.RS.S[cpt][i].y, Tmp[i], S.Nsymbol));
  fprintf(f, "0\n");
}
   

int longueurLigneS (Sudoku S, int ligne){
  int cpt = 0;
  while (S.RS.S[ligne][cpt].x != -1)
    cpt++;
  return cpt;
}
