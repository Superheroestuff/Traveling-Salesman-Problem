// AIhomework3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include<vector>
using namespace std;



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

	bool operator==(const Town& t) {
		if (t.x == this->x && t.y == this->y) {
			return true;
		}
		else return false;
	}

	void printTown() {
		cout << "X: " << this->x << " Y: " << this->y << endl;
	}

};

vector<Town> allTowns;
int N;//number of towns
void init() {
	cout << "Enter number of towns: ";
	cin >> N;
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
}
int main()
{
	init();
	for (int i = 0; i < N; i++) {
		allTowns[i].printTown();
		cout << endl;
	}
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
