#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "lecture.h"

//Procédure remplissant une grille de sudoku si il y a une seule règle S par ligne (si la règle S sert à placer un nombre dans une case)
void remplirGrille (Sudoku * S)
{
  int i = 0;
  int cpt = 0;

  while( i < (*S).RS.nbS ) //Pour toutes les règles S
    {
      while ( (cpt < 2) && ((*S).RS.S[i][cpt].x != -1) ) //Compte le nombre de de case sur la ligne S (jusqu'à 2, après inutile)
	{
	  if ( (*S).RS.S[i][cpt].x != -1 )
	    {
	      cpt = cpt + 1;
	    }
	}
      
      if (cpt == 1) //Si une seule case sur la ligne
	{

	  (*S).G[ (*S).RS.S[i][0].x ][ (*S).RS.S[i][0].y ] = (*S).RS.Ssum[i]; // On remplit la grille avec le nombre dans la case (x,y)
	}

      cpt = 0;
      i = i + 1;
    }
}


//Fonction pour lire le contenu d'un fichier et retourne un Sudoku
void lecture (Sudoku * S, char * Nom)
{
  //Initialisation
  sudokuVide(S);
  
  FILE* fichier = NULL;
  char carac, espace;
  int ui = 0, uj = 0, oi = 0, si = 0, sj = 0;
  int i, j , k ,l;
  int lu, numLign;
  char jeu[18];
  int numcolor=0;
  int limite = 15;


  printf("****Lecture****\n");
  //Lecture Fichier
  fichier = fopen(Nom, "r");

  if(fichier == NULL)
    {
      //Si erreur de lecture
      printf("Erreur de lecture. Ce fichier n'existe pas dans le répertoire du programme.\n");
      printf("****Lecture terminée****\n");
    }
  else
    {
      numLign = 1;//Initialise le compteur de lignes

      //Lit la première ligne
      lu = fscanf(fichier, "%d %d %d\n",&((*S).Nsymbol), &((*S).Nrows), &((*S).Ncolumns));

      if(lu != 3)
	{
	  //Si on a pas le bon nombre de tokens
	  printf("Erreur ligne %d.\n",numLign);
	}
      else
	{
	  numLign = numLign + 1;

	  //A partir de la deuxième ligne
	  while( !feof(fichier) ) //Sur toutes les autres lignes jusqu'à la fin du fichier
	    {
	      //Lit le premier caractère
	      carac = fgetc( fichier );

	      if(carac != EOF) //Si ce n'est pas le dernier caractère
		{
		  espace = fgetc( fichier ); //Lit l'espace qui suit

		  if ( espace != ' ' )
		    {
		      //Si ce n'est pas un espace : erreur
		      printf("Erreur ligne %d, pas d'espace suivant le premier caractère.", numLign);
		    }
		  else
		    {
		      switch ( carac ) //Vérifie si le caractère est g u s ou o.
			{
			case 'g' :

			  fgets(jeu, 18, fichier); //Récupère le type de jeu
			  (*S).nom = jeu[0];
			  numLign = numLign + 1;
			  break;

			case 'u' :
			  carac = fgetc(fichier); //Lit la première parenthèse

			  while(carac != '*') //Tant qu'on n'a pas atteint * de fin de ligne
			    {
			      lu = fscanf(fichier,"%d,%d)", &i, &j); //On récupère les couples de nombres (ligne,colonne) et on les met dans la règle U (tableau de coordonnées)
			      if(lu != 2 ) //Si pas le bon nombre de tokens
				{
				  printf("Erreur ligne %d, la ligne u numéro %d ne correspond pas aux normes.\n", numLign, (ui+1));				  
				}
			      else
				{
				  (*S).RU.U[ui][uj].x = i - 1;
				  (*S).RU.U[ui][uj].y = j - 1;
				  (*S).col[((i-1)*((*S).Nsymbol) + j -1)]= numcolor;//les cases d'une zone reçoivent une couleur.
				  uj = uj + 1;
				  (*S).RU.Usymbol = uj; //On a uj+1 symboles dans une zone, car uj commence à 0 (déjà incrémenté juste avant)
				  lu = fscanf(fichier, " %c", &carac); //On récupère les deux caractères suivant pour tester si fin de ligne

				  if( lu != 1 ) //Si pas le bon nombre de tokens
				    {
				      printf("Erreur, la ligne u numéro %d ne correspond pas aux normes.\n",(ui+1));
				    }
				  else if ( carac == '*' )
				    {
				      uj = 0; //Remet le curseur de tableau U au bon endroit  				      
				      ui = ui + 1; //Remet le curseur du tableau U au bon endroit
				      (*S).RU.nbU = ui; //Le nombre de lignes de S.RU.U = nombre de zones
				       if (limite == numcolor) 
					{
					  numcolor = 0 ;
					}
				       else {numcolor = numcolor + 1;} //on change de couleur
				    }
				}
			    }

			  carac = fgetc(fichier); //Si on a trouvé * on passe le '\n'
			  numLign = numLign + 1;
			  break;

			case 'o' :
			  lu = fscanf(fichier, "(%d,%d) %c (%d,%d) *\n", &i, &j, &(*S).RO.O[oi].sign, &k, &l); //Remplit la ligne de S.O avec ligne colonne symbole ligne colonne    
			  if( lu != 5) //Si pas le bon nombre de tokens
			    {
			      printf("Erreur ligne %d, la ligne o numéro %d ne correspond pas aux normes.\n",numLign, (oi+1));			      
			    }
			  else
			    {
			      (*S).RO.O[oi].A.x = i - 1;
			      (*S).RO.O[oi].A.y = j - 1;
			      (*S).RO.O[oi].B.x = k - 1;
			      (*S).RO.O[oi].B.y = l - 1;

			      oi = oi + 1; //Remet le curseur au bon endroit
			      (*S).RO.nbO = oi; // Nombre de règles O = nombre de cases du tableau
			    }

			  numLign = numLign + 1;
			  break;

			case 's' :
			  lu = fscanf(fichier, "%d (", &(*S).RS.Ssum[si]); //Lit du nombre de la somme jusqu'à la première parenthèse

			  if( lu != 1) //Si pas le bon nombre de tokens
			    {
			      printf("Erreur, la ligne s numéro %d ne correspond pas aux normes.\n",(si+1));
			    }
			  else
			    {
			      while(carac != '*') //Tant qu'on n'a pas atteint * de fin de ligne
				{
				  lu = fscanf(fichier,"%d,%d)", &i, &j); //On récupère les couples de nombres

				  if( lu != 2)//Si pas le bon nombre de tokens
				    {
				      printf("Erreur, la ligne s numéro %d ne correspond pas aux normes.\n",(si+1));
				    }
				  else
				    {
				      (*S).RS.S[si][sj].x = i - 1;
				      (*S).RS.S[si][sj].y = j - 1;

				      sj = sj + 1;//Place le curseur au bon endroit
				      
				      lu = fscanf(fichier," %c", &carac); //On récupère les deux caractères suivant pour tester si fin de ligne
				      if( lu != 1 ) //Si pas le bon nombre de tokens
					{
					  printf("Erreur, la ligne s numéro %d ne correspond pas aux normes.\n",(si+1));
					}
				      else if ( carac == '*' )
					{
					  sj = 0;//Remet le curseur de S au bon endroit
					  si = si + 1;
					  (*S).RS.nbS = si; //Le nombre de règles S = nombre de lignes du tableau					  
					}
				    }
				}
			    }

			  numLign = numLign + 1;
			  carac = fgetc(fichier); //Si on a trouvé * on passe le '\n'
			  break;

			default : //Ne fait rien par défaut
			  printf("Erreur ligne %d, j'devrais pas me retrouver là.\n", numLign);
			  numLign = numLign + 1;
			  break;
			}
		    }
		}
	    }
	}
      printf("****Lecture terminée****\n");
      //Fermeture de fichier
      fclose(fichier);
      remplirGrille(S); //Remplit la grille pour l'affichage
      remplissage (S);
    }  
}

//Lit un fichier retourné par Glucose et remplit la grille avec
void lectureSAT (Sudoku * S, char * nomFichier)
{
  int lu = 0;
  char carac;
  int nombre;
  int i,j,k;
  int cpt = 0; //Compte à quel nombre du fichier SAT on en est

  FILE* fichier = NULL;

  
  printf("****Lecture****\n");
  //Lecture Fichier SAT
  fichier = fopen(nomFichier, "r"); //Ouverture en écriture
  
  if(fichier == NULL)
    {
      //Si erreur de lecture
      printf("Erreur de lecture. Ce fichier n'existe pas dans le répertoire du programme.\n");
      printf("****Lecture terminée****\n");
    }
  else
    {  
      carac = fgetc ( fichier );
      if ( carac == 'U' )
	{
	  printf("Problème insatisfaisable. Pas de solution.\n");
	}
      else
	{

	  lu = fscanf(fichier, "AT\n%d", &nombre); //Pour le premier nombre
	  cpt = cpt + 1;
	  if( lu != 1 )
	    {
	      //Si on a pas le bon nombre de tokens
	      printf("Erreur première ligne.\n");
	    }
	  else
	    {
	    
	      if( nombre > 0 ) //Si le nombre est positif
		{

		  k = (nombre - 1) % (*S).Nsymbol; //On récupère ses coordonnées et le nombre en question
		  j = ((nombre - 1) / (*S).Nsymbol) % (*S).Nsymbol;
		  i = (((nombre - 1) / (*S).Nsymbol) / (*S).Nsymbol);

		 
		  if( (i <= (*S).Ncolumns - 1) && (i>=0) && (j>=0) && (j <= (*S).Nrows - 1) )
		    {

		      (*S).G[i][j] = k + 1;//Si le nombre convient aux indices de la grille on remplit
		      
		    }
		  else
		    {
		      printf("Erreur d'indice, impossible de remplir la grille avec le nombre %d.\n",cpt);
		    }
		}
	    }

	  while( nombre != 0 ) //Pour tous les autres : exactement le même procédé
	    {
	      lu = fscanf(fichier, " %d", &nombre);
	      cpt = cpt + 1;
	      if( lu != 1 )
		{
		  //Si on a pas le bon nombre de tokens
		  printf("Erreur, le nombre %d n'est pas précédé d'un espace.\n",cpt);
		}
	      else
		{
		  if( nombre > 0 )//Si le nombre est positif
		    {

		      k = (nombre - 1) % (*S).Nsymbol;//On récupère ses coordonnées et le nombre en question
		      j = ((nombre - 1) / (*S).Nsymbol) % (*S).Nsymbol;
		      i = (((nombre - 1) / (*S).Nsymbol) / (*S).Nsymbol);

		      if( (i <= (*S).Ncolumns - 1) && (i>=0) && (j>=0) && (j <= (*S).Nrows - 1) )		  
			{

			  (*S).G[i][j] = k + 1;//Si le nombre convient aux indices de la grille on remplit
			  
			}
		      else
			{
			  printf("Erreur d'indice, impossible de remplir la grille avec le nombre %d.\ni = %d, j = %d, k = %d\n",cpt,i,j,k);
			}
		    }
		}
	    }

	}
        printf("****Lecture terminée****\n");	
    }
}
