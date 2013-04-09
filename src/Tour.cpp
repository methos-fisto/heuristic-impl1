#include "Tour.h"

int myrandom(int i){
	return std::rand()%i;
}

Tour::Tour(int taille, int seed) {
	// TODO Auto-generated constructor stub
	taille_ = taille;
	permutation_ = new int[taille];
	permutation_[0] = 0;
	std::vector<int> shuffler;
	for(int i = 1 ; i < taille; i++)
	{
		shuffler.push_back(i);
	}
	std::srand(seed);
	std::random_shuffle(shuffler.begin(), shuffler.end(), myrandom);
	for(int i = 0 ; i < taille-1; i++)
		{
			permutation_[i+1] = shuffler.at(i);
		}
}

Tour::Tour(Tour* ref, int method, int k, int j)
{
	int i;
	int* temp = ref->getPermutation();
	taille_ = ref->getTaille();
	permutation_ = new int[taille_];
	if(method == 1)
	{
		for(i = 0; i< taille_; i++)
		{
			if(i == k)
			{
				permutation_[k] = temp[k+1];
			}else if(i == k+1)
			{
				permutation_[k+1] = temp[k];
			}else
			{
				permutation_[i] = temp[i];
			}
		}
	}
	if(method == 2)
	{
		if(k < j){
			for(i = 0; i< k; i++)
			{
				permutation_[i] = temp[i];
			}
			for(i = k; i< j; i++)
			{
				permutation_[i] = temp[i+1];
			}
			for(i = j; i< taille_; i++)
			{
				permutation_[i] = temp[i];
			}
			permutation_[j]= temp[k];
			}
		if(k > j)
		{
			for(i = 0; i< j; i++)
			{
				permutation_[i] = temp[i];
			}
			for(i = j; i< k; i++)
			{
				permutation_[i] = temp[i-1];
			}
			for(i = k; i< taille_; i++)
			{
				permutation_[i] = temp[i];
			}
			permutation_[j]= temp[k];
			permutation_[k]= temp[k-1];
		}
	}
	if(method == 3)
		{
			for(i = 0; i< taille_; i++)
			{

					permutation_[i] = temp[i];

			}
			permutation_[k] = temp[j];
			permutation_[j] = temp[k];
		}
}

Tour::~Tour() {
	// TODO Auto-generated destructor stub
	delete[] permutation_;
}

int Tour::getOmega() const {
	return omega_;
}

int* Tour::getPermutation() const {
	return permutation_;
}

int Tour::getTaille() const {
	return taille_;
}

int Tour::getValue() const {
	return value_;
}

int Tour::getCost() const {
	return cost_;
}

void Tour::evaluate(int** coef, int* ouvert, int* ferme)
{
	omega_ = 0;
	value_ = ouvert[0];
	cost_ = 0;
int temp;

	for(int i = 0; i < taille_-1; i++)
	{

		temp = value_ + coef[permutation_[i]][permutation_[i+1]];
		cost_ += coef[permutation_[i]][permutation_[i+1]];
		if(temp < ouvert[permutation_[i+1]])
		{
			temp = ouvert[permutation_[i+1]];

		}
		if(temp > ferme[permutation_[i+1]])
		{

			omega_++;
		}
		value_ = temp;
	}
	//std::cout << "dernier\n";
	temp = value_ + coef[permutation_[taille_-1]][permutation_[0]];
	cost_ += coef[permutation_[taille_-1]][permutation_[0]];
	if(temp > ferme[0])
	{
		omega_++;
	}
	value_ = temp;
}

void Tour::print_tour()
{
	for(int i = 0; i < taille_; i++)
	{
		std::cout << permutation_[i] << " - ";
	}
	std::cout << "\n\n";
}
