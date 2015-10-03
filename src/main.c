#include <stdio.h>
#include <string.h>
#include "lecture.h"
#include "verification.h"
#include "sudoku.h"
#include "ecritureCNF.h"

void viderBuffer() //Fonctions viderBuffer prise sur openclassrooms.com
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}
 
//Fonction lire une chaine de caractère sécurisée (pas d'overflow) => openclassrooms
int lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;
 
    if (fgets(chaine, longueur, stdin) != NULL)
    {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        else
        {
            viderBuffer();
        }
        return 1;
    }
    else
    {
        viderBuffer();
        return 0;
    }
}


/**************************************
*            MAIN
**************************************/
int main(int argc, char *argv[])
{
  //Initialisation
  Sudoku S, Sinit;
  char nomFichier[50];
  sudokuVide(&S);
  //int lu;

  //Lecture du fichier de jeu
  if (argc < 2){
    printf("Entrez le nom du fichier à lire : ");
    lire(nomFichier, 50);
    lecture(&S, nomFichier);
  } else {
    lecture(&S, argv[1]);    
  }
  printf("\n");  

  //Copie du Sudoku lu
  Sinit = S;

  //Ecriture du fichier .cnf
  affiche(S);
  sudoku2CNF (S, "Sudoku.cnf");
  system("./glucose Sudoku.cnf Sudoku.out");

  //Lecture du fichier SAT fourni
  lectureSAT(&S, "Sudoku.out");
  //Affichage de fin
  affiche(Sinit);

  if (verification(Sinit, S)){
    affiche(S);
    printf("Le sudoku retourné est correct.\n");
    char* nom="grille";
    affichagec(S,nom);
    system("pdflatex grille 1> infoCompil;evince grille.pdf 2> errEvince");
    system("rm *.aux;rm *.log;rm infoCompil; rm errEvince");

  }
  else
    printf("Le sudoku retourné est incorrect.\n");
 
  return 0;
}
