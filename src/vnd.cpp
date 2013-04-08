#include <iostream>
#include "parser.h"
#include "Tour.h"
#include <cstring>
#include <ctime>
#include <sys/time.h>
#include <sys/resource.h>

void solve_first(Tour*& best, int** coef, int* ouvert, int* ferme, int taille, int method)
{
	bool local_opt = false;
	bool found = false;
	int i, j;
	Tour* voisin;
	//best = new Tour(taille, seed);
	//best->print_tour();
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


void solve_vnd(Tour*& best, int** coef, int* ouvert, int* ferme, int taille, int seed, int order)
{
	bool local_opt = false;
	bool found = false;
	int i, j;
	int method = 1;
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
			if((method == 1) && (order == 1))
			{
				method = 3;
			}else if((method == 1) && (order == 2))
			{
				method = 2;
			}else if((method == 3) && (order == 1))
			{
				method = 2;
			}else if((method == 2) && (order == 2))
			{
				method = 3;
			}else
			{
				local_opt = true;
			}
		}
	}

}

void solve_piped_vnd(Tour*& best, int** coef, int* ouvert, int* ferme, int taille, int seed, int order)
{
	bool local_opt = false;
	bool found = false;
	int i, j;
	int method = 1;
	Tour* voisin;
	best = new Tour(taille, seed);
	best->print_tour();
	best->evaluate(coef,ouvert,ferme);
	solve_first(best,coef,ouvert,ferme,taille,method);


			if(order == 1)
			{
				method = 3;
			}else
			{
				method = 2;
			}

	solve_first(best,coef,ouvert,ferme,taille,method);

			if(order == 1)
			{
				method = 2;
			}else
			{
				method = 3;
			}

	solve_first(best,coef,ouvert,ferme,taille,method);

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
	if(strcmp(argv[2],"--first-order")==0)
	{
		method = 1;
	}
	if(strcmp(argv[2],"--second-order")==0)
	{
		method = 2;
	}

	if(method == 0)
	{
		std::cout << "Please use ./tsptw-vnd --[standard or piped] --[first-order or second-order]  instancefile.txt" << std::endl;
	}else{
		srand(time(NULL));
		parsing_file(argv[3],coef,ouvert,ferme,taille);
		if(strcmp(argv[1],"--standard")==0)
		{
			solve_vnd(best, coef, ouvert, ferme, taille, rand(), method);
		}else if(strcmp(argv[1],"--piped")==0)
		{
			solve_piped_vnd(best, coef, ouvert, ferme, taille, rand(), method);
		}else{
			std::cout << "Please use ./tsptw-vnd --[standard or piped] --[first-order or second-order]  instancefile.txt" << std::endl;
		}
	}

	std::cout << "omega " << best->getOmega() << "  makespan " << best->getValue() << std::endl;
		best->print_tour();
	return 0;

}
