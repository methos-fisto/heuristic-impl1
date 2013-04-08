#include "parser.h"
#include <iostream>
void parsing_file(char* fichier, int**& coef, int*& ouvert, int*& ferme, int& taille)
{


	std::ifstream* fichier_traite;
	int i, j;
	taille = 2;

	fichier_traite = new std::ifstream(fichier);

	*fichier_traite >> taille;

	coef = new int*[taille];
	for (int i = 0 ; i <taille ; i++)
	{
		coef[i] = new int[taille];
	}
	ouvert = new int[taille];
	ferme = new int[taille];

	for(i =0; i<taille ; i++)
	{
		for(j =0; j<taille ; j++)
		{
			*fichier_traite >> coef[i][j];
		}
	}

	for(i=0; i<taille; i++)
	{
		*fichier_traite >> ouvert[i];
		*fichier_traite >> ferme[i];
	}

	delete fichier_traite;

}

