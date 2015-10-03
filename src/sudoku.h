#ifndef __SUDOKU_H
#define __SUDOKU_H

#define N 16 //Taille maximale de Sudoku (pour les tableaux)
#define OMAX 2*N*(N-1)
#define SMAX N*N
#define UMAX N*N

typedef struct Coordonnee{
    int x,y; // ligne et colonne d'un point de coordonnée (x,y).
} Coordonnee;

typedef struct ReglesU{
    Coordonnee U[UMAX][N];
    int Usymbol ; // nombre de symbols dans une zone = taille d'une zone.
    int nbU ; // nombre de zones avec pour règle U.
} ReglesU;

typedef struct regleO{
    Coordonnee A;
    char sign;
    Coordonnee B;
} regleO;

typedef struct ReglesO{
    regleO O[OMAX];
    int nbO ; // nombre de règles O.
} ReglesO;

typedef struct ReglesS{
    Coordonnee S[SMAX][SMAX];
    int Ssum[SMAX] ; // tableau composé des sommes des règles S.
    int nbS ; // nombre de règles S.
} ReglesS;

//Type de jeu Sudoku
typedef struct Sudoku
{
  int Nsymbol; //Nombre de symboles
  int Nrows; //Nombre de lignes
  int Ncolumns;//Nombre de colonnes
  char nom; //s: sudoku, k : killer, c : comparison, j : jigsaw
  int G[N][N]; //La grille en elle-même
  ReglesU RU;
  ReglesO RO;
  ReglesS RS;
  int col[N*N];
} Sudoku;

//Racine entière d'un nombre entier
int racine(int nombre);

//Remplit de 0 un tableau à deux dimensions
void tableauVide (int tailleV, int tailleH, int T[ tailleV ][ tailleH ]);

//Initialise un tableau de coordonées avec des cases à (-1,-1)
void TabCoordVide (int tailleV, int tailleH, Coordonnee T[ tailleV ][ tailleH ]);


//Initialise un tableau de règles O
void tabregleOvide (int taille, regleO T[taille]);


//Initialise un Sudoku
void sudokuVide (Sudoku * S);

//Afficher un tableau à 2 dimensions
void afficheTab(int tailleV, int tailleH, int tab[ tailleV ][ tailleH ]);

//Affiche un tableau de coordonnées à deux dimensions
void afficheTabCoord (int tailleV, int tailleH, Coordonnee T[ tailleV ][ tailleH ]);

//Affiche regle S
void afficheRegleS (Sudoku S);

//Affiche une regleO
void afficheRegleO (regleO o);

//Affiche toutes les règles O pour les ReglesO
void afficheTabRegleO (Sudoku S);

//Affiche une ligne du type : +--------+--------+--------+
void afficheLigne(int taille);

//Affiche la grille de jeu
void afficheJeu(Sudoku S);

//Affiche la totalité du jeu de sudoku : ses règles et sa grille
void affiche(Sudoku S);

//crée un fichier txt à compiler avec pdflatex
void affichage (Sudoku S, char *nomFichier);

//idem en couleur
void affichagec (Sudoku S, char *nomFichier);


#endif
