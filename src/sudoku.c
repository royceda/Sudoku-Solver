#include <stdlib.h>
#include <stdio.h>
#include "sudoku.h"
#include "verification.h" //Pour vider_tableau

//Racine entière d'un nombre entier
int racine(int nombre)
{
  int r1, r2;
  r1 = (nombre + 1) / 2;
  while(1)
  {
    r2 = (r1 + nombre / r1) / 2;
    if (r2 >= r1)
      return r1;
    r1 = r2;
  }
}



//Remplit de 0 un tableau à deux dimensions
void tableauVide (int tailleV, int tailleH, int T[tailleV][tailleH])
{
  int i,j;
  for(i = 0; i < tailleV; i++)
    {
      for(j = 0; j < tailleH; j++)
        {
          T[i][j] = 0;
        }
    }
}

//Initialise un tableau de coordonées avec des cases à (-1,-1)
void TabCoordVide (int tailleV, int tailleH, Coordonnee T[tailleV][tailleH])
{
  for( int i = 0; i < tailleV; i++)
    {
      for (int j = 0; j < tailleH; j++)
        {
          T[i][j].x = -1;
          T[i][j].y = -1;
        }
    }
}

//Initialise un tableau de règles O
void tabregleOvide (int taille, regleO T[taille])
{
  for(int i = 0; i < taille; i++)
    {
      T[i].A.x = -1;
      T[i].A.y = -1;
      T[i].B.x = -1;
      T[i].B.y = -1;
      T[i].sign = '=';
    }
}
         
//Initialise un Sudoku
void sudokuVide (Sudoku * S)
{
  S->Nsymbol = 0;
  S->Nrows = 0;
  S->Ncolumns = 0;
  S->nom = 'x';
  
  tableauVide(S->Nrows, S->Nrows, S->G);

  vider_tableau(S->col, SMAX);

  TabCoordVide(SMAX, SMAX, S->RS.S);
  S->RS.nbS = 0;
  vider_tableau(S->RS.Ssum, SMAX);

  S->RU.Usymbol = 0;
  S->RU.nbU = 0;
  TabCoordVide(UMAX, N, S->RU.U);

  S->RO.nbO = 0;
  tabregleOvide( OMAX, S->RO.O );
}

//Afficher un tableau à 2 dimensions
void afficheTab(int tailleV, int tailleH, int tab[ tailleV ][ tailleH ])
{
  for(int i = 0; i < tailleV; i++)
    {
      for(int j = 0; j < tailleH; j++)
        {
          printf("%d ", tab[i][j]);
        }
      printf("\n");
    }
}

//Affiche une ligne du type : +--------+--------+--------+
void afficheLigne(int taille)
{
  int i, taille2;
  taille2 = racine(taille);
  printf("+-");
  for(i = 1; i < taille; i++)
    {
      if(i % taille2 == 0)
        {
          printf("+-");
        }
      else
        {
          printf("---");
        }
    }
  printf("+\n");
}

//Affiche un tableau de coordonnées à deux dimensions
void afficheTabCoord (int tailleV, int tailleH, Coordonnee T[ tailleV ][ tailleH ])
{
  int i,j;
  i = 0;
  j = 0;
  while(i < tailleV && T[i][j].x != -1)
    {
      printf("%2d ",i);
      while(j < tailleH && T[i][j].x != -1)
        {
          printf("(%2d,%2d) ", T[i][j].x, T[i][j].y);
          j = j + 1;
        }
       printf("\n");
       i = i + 1;
       j = 0;
    }
}



//Affiche regle S
void afficheRegleS (Sudoku S)
{
  int i,j;
  i = 0;
  j = 0;
  while(i < SMAX && S.RS.S[i][j].x != -1)
    {
      printf("Somme : %2d, Cases :  ", S.RS.Ssum[i]);
      while((j < SMAX) && (S.RS.S[i][j].x != -1))
        {
          printf("(%2d,%2d) ", S.RS.S[i][j].x, S.RS.S[i][j].y);
          j = j + 1;
        }
       printf("\n");
       i = i + 1;
       j = 0;
    }
}

//Affiche une regleO
void afficheRegleO (regleO o)
{
  if( o.sign == 'i' )
    {
      printf("(%2d,%2d) <= (%2d,%2d) ", o.A.x, o.A.y, o.B.x, o.B.y);
    }
  else if (o.sign == 's')
    {
      printf("(%2d,%2d) >= (%2d,%2d) ", o.A.x, o.A.y, o.B.x, o.B.y);
    }
  else
    {
      printf("(%2d,%2d) %c (%2d,%2d) ", o.A.x, o.A.y, o.sign, o.B.x, o.B.y);
    }
}

//Affiche toutes les règles O pour les ReglesO
void afficheTabRegleO (Sudoku S)
{
  for(int i = 0 ; i < S.RO.nbO; i++)
    {
      afficheRegleO(S.RO.O[i]);
      printf("\n");
    }
}

//Affiche la grille de jeu
void afficheGrille(Sudoku S)
{
  int i,j,n;
  n = racine( S.Nrows );
  for(i = 0; i < S.Nrows; i++)
    {
      if(i % n == 0)
        {
          afficheLigne( S.Nrows );
        }
      for(j = 0;j < S.Nrows; j++)
        {
          if(j % n == 0)
            {
              printf("| ");
            }
          if( S.G[i][j] != 0 )
            {
              printf("%d ", S.G[i][j]);
            }
          else
            {
              printf(". ");
            }
        }
      printf("|\n");
    }
  afficheLigne( S.Nrows );
  printf("\n");
}

//Affiche la totalité du jeu de sudoku : ses règles et sa grille
void affiche(Sudoku S)
{
  printf("Type de jeu : ");
  switch( S.nom )
    {
    case 's' :
      printf("Sudoku.\n");
      break;
    case 'k' :
      printf("Killer Sudoku.\n");
      break;
    case 'c' :
      printf("Comparison Sudoku.\n");
      break;
    case 'j' :
      printf("Jigsaw Sudoku.\n");
      break;
    default :
      printf("Bah j'en sais rien (%c).\n", S.nom);
    }

  if(S.nom == 's' || S.nom == 'c' || S.nom == 'k' || S.nom == 'j' )
    {
      /*printf("Règle U : \n");
      printf("Nombre de zones : %2d. Nombre de symboles dans une zone : %2d.\n", S.RU.nbU, S.RU.Usymbol);
      afficheTabCoord( UMAX, N, S.RU.U);

      printf("\nRègle O : \n");
      printf("Nombre de regles O : %2d.\n", S.RO.nbO);
      afficheTabRegleO(S);

      printf("\nRègle S : \n");
      printf("Nombre de règles S : %2d.\n", S.RS.nbS);
      afficheRegleS(S);*/
     
     
      printf("\nGrille : \n");
      afficheGrille( S );
    }
}


//crée un fichier txt à compiler avec pdflatex
void affichage (Sudoku S, char *nomFichier)
{
  FILE *f;
  int i,j,k,n;
  n = racine( S.Nrows );
  f = fopen(nomFichier, "w");
  fprintf(f,"\\documentclass[a4paper,16pt]{article}\n\\usepackage[utf8]{inputenc}\n\\usepackage[french]{babel}\n\\usepackage{amsmath, amssymb}\n\\usepackage{colortbl}\n\\usepackage{geometry}\n\\geometry{vmargin=2.5cm}\n\\begin{document}\n\\setlength\\doublerulesep{1pt}\n\\doublerulesepcolor{black}\n\\begin{center}\n\\begin{tabular}{ ");
  for ( k = 0; k < S.Ncolumns; k++)
    {
      if ((k % n) == 0)
	{
	  fprintf(f,"||c");
	}
      else fprintf(f,"|c");
    }
  fprintf(f,"||");
  fprintf(f,"}\n");
  for(i = 0; i < S.Nrows; i++)
    {
      if ( (i % n ) == 0)
	{
	  fprintf(f,"\\hline\\hline");
	}
      else fprintf(f,"\\hline");
      for(j = 0 ;j < (S.Nrows - 1); j++)
        {
	  if( S.G[i][j] != 0 )
            {
              fprintf(f,"%d & ", S.G[i][j]);
            }
          else
            {
              fprintf(f,". &");
            }
        }
      fprintf(f,"%d\\\\", S.G[i][j]);
    }
  fprintf(f,"\\hline\\hline");
  fprintf(f,"\\end{tabular}\n\\end{center}");  
  fprintf(f,"\\end{document}");
  fclose(f);
}

//crée un fichier txt à compiler avec pdflatex
void affichagec (Sudoku S, char *nomFichier)
{
  FILE *f;
  int i,j,k,n,nb;
  n = racine( S.Nrows );
  f = fopen(nomFichier, "w");
  fprintf(f,"\\documentclass[a4paper,16pt]{article}\n\\usepackage[utf8]{inputenc}\n\\usepackage[french]{babel}\n\\usepackage{amsmath, amssymb}\n\\usepackage{colortbl}\n\\usepackage{geometry}\n\\usepackage[dvipsnames]{xcolor}\n\\geometry{vmargin=2.5cm}\n\\begin{document}\n\\setlength\\doublerulesep{1pt}\n\\doublerulesepcolor{black}\n\\begin{center}\n\\begin{tabular}{ ");
  for ( k = 0; k < S.Ncolumns; k++)
    {
      if ((k % n) == 0)
	{
	  fprintf(f,"||c");
	}
      else fprintf(f,"|c");
    }
  fprintf(f,"||");
  fprintf(f,"}\n");
  for(i = 0; i < S.Nrows; i++)
    {
      if ( (i % n ) == 0)
	{
	  fprintf(f,"\\hline\\hline");
	}
      else fprintf(f,"\\hline");
      for(j = 0 ;j < (S.Nrows - 1); j++)
        {
	  if( S.G[i][j] != 0 )
            {
	      nb = (i * S.Nsymbol) + j;
	      //printf("%d\n",S.col[nb]);
	      switch (S.col[nb])
		{
		case 0:
		  fprintf(f,"\\cellcolor{white}%d & ", S.G[i][j]);
		  break;
		case 1:
		  fprintf(f,"\\cellcolor{green}%d & ", S.G[i][j]);
		  break;
		case 2:
		  fprintf(f,"\\cellcolor{red}%d & ", S.G[i][j]);
		  break;
		case 3:
		  fprintf(f,"\\cellcolor{yellow}%d & ", S.G[i][j]);
		  break;
		case 4:
		  fprintf(f,"\\cellcolor{brown}%d & ", S.G[i][j]);
		  break;
		case 5:
		  fprintf(f,"\\cellcolor{purple}%d & ", S.G[i][j]);
		  break;
		case 6:
		  fprintf(f,"\\cellcolor{gray}%d & ", S.G[i][j]);
		  break;
		case 7:
		  fprintf(f,"\\cellcolor{cyan}%d & ", S.G[i][j]);
		  break;
		case 8:
		  fprintf(f,"\\cellcolor{Orchid}%d &", S.G[i][j]);
		  break;
		case 9:
		  fprintf(f,"\\cellcolor{Apricot}%d &", S.G[i][j]);
		  break;
		case 10:
		  fprintf(f,"\\cellcolor{Violet}%d &", S.G[i][j]);
		  break;
		case 11:
		  fprintf(f,"\\cellcolor{blue}%d &", S.G[i][j]);
		  break;
		case 12:
		  fprintf(f,"\\cellcolor{Dandelion}%d &", S.G[i][j]);
		  break;
		case 13:
		  fprintf(f,"\\cellcolor{SkyBlue}%d &", S.G[i][j]);
		  break;
		case 14:
		  fprintf(f,"\\cellcolor{LimeGreen}%d &", S.G[i][j]);
		  break;
		case 15:
		  fprintf(f,"\\cellcolor{Orange}%d &", S.G[i][j]);
		  break;
		default:
		  fprintf(f,"%d &", S.G[i][j]);
		  break;
		}
	    }
          else
            {
              nb = (i * S.Nsymbol) + j;
	      //printf("%d\n",S.col[nb]);
	      switch (S.col[nb])
		{
		case 0:
		  fprintf(f,"\\cellcolor{white}. & ");
		  break;
		case 1:
		  fprintf(f,"\\cellcolor{green}. &");
		  break;
		case 2:
		  fprintf(f,"\\cellcolor{red}. &");
		  break;
		case 3:
		  fprintf(f,"\\cellcolor{yellow}. &");
		  break;
		case 4:
		  fprintf(f,"\\cellcolor{brown}. &");
		  break;
		case 5:
		  fprintf(f,"\\cellcolor{purple}. &");
		  break;
		case 6:
		  fprintf(f,"\\cellcolor{gray}. &");
		  break;
		case 7:
		  fprintf(f,"\\cellcolor{cyan}. &");
		  break;
		case 8:
		  fprintf(f,"\\cellcolor{Orchid}. &");
		  break;
		case 9:
		  fprintf(f,"\\cellcolor{Apricot}. &");
		  break;
		case 10:
		  fprintf(f,"\\cellcolor{Violet}. &");
		  break;
		case 11:
		  fprintf(f,"\\cellcolor{blue}. &");
		  break;
		case 12:
		  fprintf(f,"\\cellcolor{Dandelion}. &");
		  break;
		case 13:
		  fprintf(f,"\\cellcolor{SkyBlue}. &");
		  break;
		case 14:
		  fprintf(f,"\\cellcolor{LimeGreen}. &");
		  break;
		case 15:
		  fprintf(f,"\\cellcolor{Orange}. &");
		  break;
		default:
		  fprintf(f,". &");
		  break;
		}
              
            }
        }
      nb = (i * S.Nsymbol) + j;
      //printf("%d\n",S.col[nb]);
      switch (S.col[nb])
	{
	case 0:
	  fprintf(f,"\\cellcolor{white}%d \\\\", S.G[i][j]);
	  break;
	case 1:
	  fprintf(f,"\\cellcolor{green}%d \\\\", S.G[i][j]);
	  break;
	case 2:
	  fprintf(f,"\\cellcolor{red}%d \\\\", S.G[i][j]);
	  break;
	case 3:
	  fprintf(f,"\\cellcolor{yellow}%d \\\\", S.G[i][j]);
	  break;
	case 4:
	  fprintf(f,"\\cellcolor{brown}%d \\\\", S.G[i][j]);
	  break;
	case 5:
	  fprintf(f,"\\cellcolor{purple}%d \\\\", S.G[i][j]);
	  break;
	case 6:
	  fprintf(f,"\\cellcolor{gray}%d \\\\", S.G[i][j]);
	  break;
	case 7:
	  fprintf(f,"\\cellcolor{cyan}%d \\\\", S.G[i][j]);
	  break;
	case 8:
	  fprintf(f,"\\cellcolor{Orchid}%d \\\\", S.G[i][j]);
	  break;
	case 9:
	  fprintf(f,"\\cellcolor{Apricot}%d \\\\", S.G[i][j]);
	  break;
	case 10:
	  fprintf(f,"\\cellcolor{Violet}%d \\\\", S.G[i][j]);
	  break;
	case 11:
	  fprintf(f,"\\cellcolor{blue}%d \\\\", S.G[i][j]);
	  break;
	case 12:
	  fprintf(f,"\\cellcolor{Dandelion}%d \\\\", S.G[i][j]);
	  break;
	case 13:
	  fprintf(f,"\\cellcolor{Skyblue}%d \\\\", S.G[i][j]);
	  break;
	case 14:
	  fprintf(f,"\\cellcolor{LimeGreen}%d \\\\", S.G[i][j]);
	  break;
	case 15:
	  fprintf(f,"\\cellcolor{Orange}%d \\\\", S.G[i][j]);
	  break;
	default:
	  fprintf(f,"%d \\\\", S.G[i][j]);
	  break;
	}
    }
  fprintf(f,"\\hline\\hline");
  fprintf(f,"\\end{tabular}\n\\end{center}");  
  fprintf(f,"\\end{document}");
  fclose(f);
}
