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


	bool operator==(const Town& t) {
		if (t.x == this->x && t.y == this->y) {
			return true;
		}
		return false;
	}

	bool operator!=(const Town& t) const{
		if (t.x != this->x || t.y != this->y) {
			return true;
		}
		else return false;
	}

	void printTown() {
		cout << "X: " << this->x << " Y: " << this->y << endl;
	}
	int calculateDistance(Town&t) {
		return sqrt(pow(x-t.x, 2) + pow(y-t.y, 2));
	}
};




vector<Town> allTowns;


//one Chromosome is one configuration of the Towns
struct Chromosome {
private:
	vector<Town> arrTowns;//arrangement of Towns
	double fitness;

public:

	vector<Town> getArrTowns(){
		return this->arrTowns;
	}

	double getFitness(){
		return this->fitness;
	}

	Chromosome(vector<Town> &towns) {
		arrTowns = towns;
		calculateFitness();
	}

	bool hasTown(Town &t){
        for(int i = 0; i<N; i++){
            if(arrTowns[i]==t) return true;
        }
        return false;
	}

	bool operator==(const Chromosome& ch) const{
		for (int i = 0; i < N; i++){
			if (this->arrTowns[i] != ch.arrTowns[i]) {
				return false;
			}
		}
		return true;
	}

	bool operator<(const Chromosome& ch) {
		return this->fitness < ch.fitness;
	}

	void calculateFitness() {
		this->fitness = 0;
		for (int i = 1; i < N; i++) {
			this->fitness += arrTowns[i].calculateDistance( arrTowns[i - 1]);
		}
		this->fitness += arrTowns[arrTowns.size() - 1].calculateDistance( arrTowns[0]);//distance between last and first Town
	}

	void mutate(){
        int randFactor = rand()%100;
        if(randFactor<=10){
            int firstIdx = rand()%arrTowns.size();
            int secondIdx;
            do{
                secondIdx = rand()%arrTowns.size();
            }while(firstIdx==secondIdx);

            swap(arrTowns[firstIdx],arrTowns[secondIdx]);
            calculateFitness();
        }
	}

	void printChromosome() {
		for (int i = 0; i < N; i++) {
			this->arrTowns[i].printTown();
		}
		cout<<"Fitness:" << this->fitness<<endl;
	}
};

bool hasVectorMember(vector<Town> &towns, Town &t){
    for(int i = 0 ; i< towns.size(); i++){
        if(towns[i] == t) return true;
    }
    return false;
}

struct Population {
private:
	vector<Chromosome> population;
	int currPopulationSize = 0;

public:

    int getCurrPopulationSize(){
        return currPopulationSize;
    }

	bool addChromosome(Chromosome &ch) {
		if (hasChromosome(ch) && currPopulationSize > 0) {
			return false;
		}
		population.push_back(ch);
		currPopulationSize++;
		return true;
	}
	bool hasChromosome(Chromosome &ch) {
		for (int i = 0; i < currPopulationSize; i++) {
			if (population[i] == ch) return true;
		}
		return false;
	}

	void initPopulation() {
		for (int i = 0; i < populationSize; i++) {
			vector<Town> randChromosome = allTowns;
			random_shuffle(randChromosome.begin(), randChromosome.end());
			Chromosome newChromosome(randChromosome);
			if (!addChromosome(newChromosome)) {
				i--;
				continue;
			}
		}
	}

	void removeWeakChromosomes(){
        for(int i = 0; i< populationSize/2; i++){
            population.pop_back();
        }
        currPopulationSize = population.size();
	}



	void crossover(){
        int firstParentIdx = rand()%currPopulationSize;
        int secondParentIdx ;
        do{
            secondParentIdx = rand()%currPopulationSize;
        }while(firstParentIdx == secondParentIdx);

        vector<Town> firstChromosome = population[firstParentIdx].getArrTowns();
        vector<Town> secondChromosome = population[secondParentIdx].getArrTowns();

        int randTownIdx = rand()%N;


        vector<Town> firstChild(firstChromosome.begin(),firstChromosome.begin()+randTownIdx);
        vector<Town> secondChild(secondChromosome.begin(),secondChromosome.begin()+randTownIdx);


        for(int i = 0; i<N; i++){
            if(!hasVectorMember(firstChild,secondChromosome[i])){
                firstChild.push_back(secondChromosome[i]);
            }
        }

        for(int i = 0; i<N; i++){
            if(!hasVectorMember(secondChild,firstChromosome[i])){
                secondChild.push_back(firstChromosome[i]);
            }
        }

       Chromosome child1(firstChild);
       Chromosome child2(secondChild);

       if((currPopulationSize+1) != populationSize){
            addChromosome(child1);
            addChromosome(child2);
       }
       else if(currPopulationSize<populationSize){
            addChromosome(child1);
       }


       //CONSTRUCTED THE CHILD, NOW WE SHOULD ADD THEM TO THE NEW POPULATION

    }

    void mutation(){
        for(int i = 0; i<populationSize; i++){
            population[i].mutate();
        }
    }
	void printPopulation() {
		for (int i = 0; i < populationSize; i++) {
			population[i].printChromosome();
			cout << endl;
		}
	}
    void sortPopulation() {// sort chromosomes in population in asc order by their fitness
        sort(population.begin(),population.end());
    }

    void printBestChromosome(){
        population[0].printChromosome();
    }

};

void initTowns() {
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
	//printPopulation();
}

void GeneticAlgorithm(Population &population, int n){//n->number of current iteration/generations)
    if(n<0){
        return;
    }
    cout<<population.getCurrPopulationSize()<<endl;
    population.sortPopulation();
    population.printBestChromosome();
    cout<<endl;

    population.removeWeakChromosomes();

    while(population.getCurrPopulationSize()<populationSize){
        population.crossover();
    }

    population.mutation();
    /*TODO::
    1.remove weak chromosomes->50%population -> check
    2.crossover the strong chromosome for the new generation
    3.mutate chromosomes
    */

    GeneticAlgorithm(population,n-1);
}

void solve(){
    initTowns();
    Population population;
    population.initPopulation();
    GeneticAlgorithm(population, 30);
}
int main()
{
	srand(time(NULL));
	solve();

}
