#include <iostream>
#include "parser.h"
#include "Tour.h"
#include <cstring>
#include <ctime>
#include <sys/time.h>
#include <sys/resource.h>
void solve_first(Tour*& best, int** coef, int* ouvert, int* ferme, int taille, int seed, int method)
{
	bool local_opt = false;
	bool found = false;
	int i, j;
	Tour* voisin;
	best = new Tour(taille, seed);
	best->print_tour();
	best->evaluate(coef,ouvert,ferme);
	while(!local_opt)
	{
		if(method == 1)
		{
			i= 1;
			while((!found) && (i<(taille-1)))
			{
				voisin = new Tour(best, 1, i,i+1);
				voisin->evaluate(coef, ouvert, ferme);
				i++;
				if(voisin->getOmega() < best->getOmega())
				{
					found= true;
					delete best;
					best = voisin;
				}else if(voisin->getOmega() == best->getOmega())
				{
					if(voisin->getValue() < best->getValue())
					{
						found= true;
						delete best;
						best = voisin;
					}else{
						delete voisin;
					}
				}else
				{
					delete voisin;
				}
			}

		}
		//end of method 1
		if(method == 2)
		{
			i= 1;
			j=1;
			while((!found) && (i < taille-1 || j < taille-1))
			{
				if(i != j){
					voisin = new Tour(best, 2, i,j);
					voisin->evaluate(coef, ouvert, ferme);
					j++;
					if(voisin->getOmega() < best->getOmega())
					{
						found= true;
						delete best;
						best = voisin;
					}else if(voisin->getOmega() == best->getOmega())
					{
						if(voisin->getValue() < best->getValue())
						{
							found= true;
							delete best;
							best = voisin;
						}else{
							delete voisin;
						}
					}else
					{
						delete voisin;
					}
				}else
				{
					j++;
				}
				if(j > taille-1)
				{
					j=1;
					i++;
				}
			}

		}
		//end of method 2
		if(method == 3)
		{
			i= 1;
			j=i+1;
			while((!found) && (j <= taille-1))
			{
					voisin = new Tour(best, 3, i,j);
					voisin->evaluate(coef, ouvert, ferme);
					j++;
					if(voisin->getOmega() < best->getOmega())
					{
						found= true;
						delete best;
						best = voisin;
					}else if(voisin->getOmega() == best->getOmega())
					{
						if(voisin->getValue() < best->getValue())
						{
							found= true;
							delete best;
							best = voisin;
						}else{
							delete voisin;
						}
					}else
					{
						delete voisin;
					}
				if(j > taille-1)
				{
					i++;
					j = i+1;
				}
			}

		}
		//end of method 3
		if(found)
		{
			found = false;
		}else
		{
			local_opt = true;
		}
	}

}

void solve_best(Tour*& best, int** coef, int* ouvert, int* ferme, int taille, int seed, int method)
{
	bool local_opt = false;
	bool found = false;
	int i, j;
	Tour* voisin;
	Tour* meilleur_voisin;
	best = new Tour(taille, seed);
	best->evaluate(coef,ouvert,ferme);
	while(!local_opt)
	{
		meilleur_voisin = best;
		if(method == 1)
		{
			for(i = 1; i < taille-1; i++)
			{
				voisin = new Tour(best, 1, i,i+1);
				voisin->evaluate(coef, ouvert, ferme);
				if(voisin->getOmega() < meilleur_voisin->getOmega())
				{
					if(found) // if we don't have found a improving neighbour before, we would delete best
					{
						delete meilleur_voisin;
					}else{

					found= true;}
					meilleur_voisin = voisin;
				}else if(voisin->getOmega() == meilleur_voisin->getOmega())
				{
					if(voisin->getValue() < meilleur_voisin->getValue())
					{
						if(found) // if we don't have found a improving neighbour before, we would delete best
						{
							delete meilleur_voisin;
						}else{

						found= true;}
						meilleur_voisin = voisin;
					}else{
						delete voisin;
					}
				}else
				{
					delete voisin;
				}
			}

		}
		//end of method 1
		if(method == 2)
		{
			for(i = 1; i <= taille-1; i++){
				for(j= 1 ; j <= taille-1; j++){
					if(i != j){
						voisin = new Tour(best, 2, i,j);
						voisin->evaluate(coef, ouvert, ferme);
						if(voisin->getOmega() < meilleur_voisin->getOmega())
						{
							if(found) // if we don't have found a improving neighbour before, we would delete best
							{
								delete meilleur_voisin;
							}else{

							found= true;}
							meilleur_voisin = voisin;
						}else if(voisin->getOmega() == meilleur_voisin->getOmega())
						{
							if(voisin->getValue() < meilleur_voisin->getValue())
							{
								if(found) // if we don't have found a improving neighbour before, we would delete best
								{
									delete meilleur_voisin;
								}else{

								found= true;}
								meilleur_voisin = voisin;
							}else{
								delete voisin;
							}
						}else
						{
							delete voisin;
						}
					}
			}
			}
		}
		//end of method 2
		if(method == 3)
				{
					for(i = 1; i < taille-1; i++){
						for(j= i+1 ; j <= taille-1; j++){

								voisin = new Tour(best, 3, i,j);
								voisin->evaluate(coef, ouvert, ferme);
								if(voisin->getOmega() < meilleur_voisin->getOmega())
								{
									if(found) // if we don't have found a improving neighbour before, we would delete best
									{
										delete meilleur_voisin;
									}else{

									found= true;}
									meilleur_voisin = voisin;
								}else if(voisin->getOmega() == meilleur_voisin->getOmega())
								{
									if(voisin->getValue() < meilleur_voisin->getValue())
									{
										if(found) // if we don't have found a improving neighbour before, we would delete best
										{
											delete meilleur_voisin;
										}else{

										found= true;}
										meilleur_voisin = voisin;
									}else{
										delete voisin;
									}
								}else
								{
									delete voisin;
								}

					}
					}
				}
		//end of method 3
		if(found)
		{
			delete best;
			best = meilleur_voisin;
			found = false;
		}else
		{
			local_opt = true;
		}
	}

}

struct timeval start_utime, stop_utime;

void crono_start()
{
  struct rusage rusage;

  getrusage(RUSAGE_SELF, &rusage);
  start_utime = rusage.ru_utime;
}

void crono_stop()
{
  struct rusage rusage;

  getrusage(RUSAGE_SELF, &rusage);
  stop_utime = rusage.ru_utime;
}

double crono_ms()
{
  return (stop_utime.tv_sec - start_utime.tv_sec) * 1000 +
    (stop_utime.tv_usec - start_utime.tv_usec) / 1000 ;
}

int main(int argc, char *argv[]){

	Tour* best;
	int** coef;
	int* ouvert;
	int* ferme;
	int taille;
	int method = 0;
	int random= 0;
	if(strcmp(argv[2],"--transpose")==0)
	{
		method = 1;
	}
	if(strcmp(argv[2],"--insertion")==0)
	{
		method = 2;
	}
	if(strcmp(argv[2],"--exchange")==0)
	{
		method = 3;
	}
	if(strcmp(argv[3],"--init-random")==0)
	{
		random = 1;
	}

	if(method == 0 || random == 0)
	{
		std::cout << "Please use ./tsptw-ii --[pivoting rule] --[neighborhood] --init-random instancefile.txt" << std::endl;
	}else{
		srand(time(NULL));
		parsing_file(argv[4],coef,ouvert,ferme,taille);
		if(strcmp(argv[1],"--first")==0)
		{
			solve_first(best, coef, ouvert, ferme, taille, rand(), method);
		}else if(strcmp(argv[1],"--best")==0)
		{
			solve_best(best, coef, ouvert, ferme, taille, rand(), method);
		}else{
			std::cout << "Please use ./tsptw-ii --[pivoting rule] --[neighborhood] --init-random instancefile.txt" << std::endl;
		}
	}

	std::cout << "omega " << best->getOmega() << "  makespan " << best->getValue() << std::endl;
		best->print_tour();
	return 0;

}
