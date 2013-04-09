/*
 * Tour.h
 *
 *  Created on: 8 avr. 2013
 *      Author: Dawn
 */

#ifndef TOUR_H_
#define TOUR_H_

#include <algorithm>
#include <cstdlib>
#include <vector>
#include <iostream>

class Tour {
public:
	Tour(int taille, int seed);
	Tour(Tour* ref, int method, int k, int j); // We will construct neighbours with this constructor
	~Tour();
	void evaluate(int** coef, int* ouvert, int* ferme);
	int getOmega() const;
	int* getPermutation() const;
	int getTaille() const;
	int getValue() const;
	int getCost() const;
	void print_tour();
private:
	int* permutation_;
	int omega_;
	int value_;
	int taille_;
	int cost_;
};

int myrandom(int i);

#endif /* TOUR_H_ */
