// AIhomework3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include<vector>
#include<cmath>
#include<time.h>
#include<algorithm>
using namespace std;

int N;//number of towns
int populationSize;

struct Town {
private:

	int x;
	int y;

public:
	void setX(int x) {
		this->x = x;
	}

	void setY(int y) {
		this->y = y;
	}

	int getX() {
		return this->x;
	}

	int getY() {
		return this->y;
	}

	void operator=(const Town& t) {
		this->x = t.x;
		this->y = t.y;
	}

	bool operator==(const Town& t) {
		if (t.x == this->x && t.y == this->y) {
			return true;
		}
		else return false;
	}

	bool operator!=(const Town& t) {
		if (t.x != this->x || t.y != this->y) {
			return true;
		}
		else return false;
	}

	void printTown() {
		cout << "X: " << this->x << " Y: " << this->y << endl;
	}

};


int calculateDistance(Town &first, Town&second) {
	return sqrt(pow((first.getX()-second.getX()),2)+ pow((first.getY() - second.getY()), 2));
}

vector<Town> allTowns;


//one Chromosome is one configuration of the Towns
struct Chromosome {
private:
	vector<Town> arrTowns;//arrangement of Towns
	int fitness;

public:

	vector<Town> getArrTowns(){
		return this->arrTowns;
	}

	int getFitness(){
		return this->fitness;
	}

	Chromosome(vector<Town> towns) {
		arrTowns = towns;
		calculateFitness();	
	}

	bool operator==(const Chromosome& ch) {
		for (int i = 0; i < N; i++){
			if (this->arrTowns[i] != ch.arrTowns[i]) {
				return false;
			}
		}
		return true;
	}

	void calculateFitness() {
		this->fitness = 0;
		for (int i = 1; i < N; i++) {
			this->fitness += calculateDistance(arrTowns[i], arrTowns[i - 1]);
		}
		this->fitness += calculateDistance(arrTowns[arrTowns.size() - 1], arrTowns[0]);//distance between last and first Town
	}

	void printChromosome() {
		for (int i = 0; i < N; i++) {
			this->arrTowns[i].printTown();
		}
	}
};

vector<Chromosome> population;

void initPopulation() {
	for (int i = 0; i < populationSize; i++) {
		vector<Town> randChromosome = allTowns;
		random_shuffle(randChromosome.begin(), randChromosome.end());
		if (find(population.begin(), population.end(), randChromosome) == population.end()) {//if we do not have this chromosome in the population => we add it
			population.push_back(randChromosome);
		}
		else {//if this chromosome is already in the population, we go one step back, because we need to get population with size = populationsize
			i--;
		}
	}
}

void printPopulation() {
	for (int i = 0; i < populationSize; i++) {
		population[i].printChromosome();
		cout << endl;
	}
}

void init() {
	cout << "Enter number of towns: ";
	cin >> N;
	bool flag=0;
	char answer;
	
	cout << "Do you want to set population size? (If not, it will be default size 10000)" << endl;
	while (flag == 0) {
		cin >> answer;
		if (answer == 'y') {
			cout << "Enter size of population: ";
			cin >> populationSize;
			flag = 1;
		}
		else if (answer == 'n') {
			populationSize = 10000;
			flag = 1;
		}
		else {
			cout << "You must write y or n" << endl;
			flag = 0;
		}
	}
	
	//populationSize = 10000;
	int x, y, NorP;
	for (int i = 0; i < N; i++) {
		Town newTown;
		x = rand() % 100;
		NorP = rand() % 2;
		if (NorP % 2 == 1) {
			x = -1 * x;
		}
		NorP = rand() % 2;
		y = rand() % 100;
		if (NorP % 2 == 1) {
			y = -1 * y;
		}
		newTown.setX(x);
		newTown.setY(y);
		allTowns.push_back(newTown);
	}
	initPopulation();
	//printPopulation();
}
int main()
{
	srand(time(NULL));
	init();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
