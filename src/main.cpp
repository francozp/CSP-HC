#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <iomanip>
#include <algorithm>
#include <random>
#include <time.h>
using namespace std;

vector<int> gen_initial_solution(vector<vector<int>> classes,int num_classes, int num_vehicles){
    srand(time(NULL));
    vector<int> initialsol;
    int cont = 0;
    int cont1 = 0;
    int cars;
    while(cont < num_classes){
        cars = classes[cont][0];
        cont1 = 0;
        while(cont1 < cars){
            initialsol.push_back(cont);
            cont1++;
        }
        cont++;
    }
    random_shuffle(initialsol.begin(), initialsol.end());
    return initialsol;
}

float eval(vector<int> solution, vector<int> blockSize, vector<int> carsBlock, int num_vehicles, int num_options, int num_classes)
{
    int eval;
    vector <int> iter(num_vehicles, 0);
    for(int i = 0; i < num_vehicles; i++){
        iter[solution[i]] += 1;
    }
    return eval;
}

int main()
{   
    vector<int> initial_sol;
    int cont = 0;
    int clase = 0;
    int num_vehicles, num_classes, num_options;
    int detail;
    ifstream inFile;
    inFile.open("Instancias/test1.txt");
    if (!inFile){
        cout << "Unable to open file";
        exit(1);
    }
    inFile >> num_vehicles;
    inFile >> num_options;
    inFile >> num_classes;
    vector<vector<int>> classes(num_classes, vector<int>(num_options + 1));   
    vector<int> carsBlock(num_options);
    vector<int> blockSize(num_options);
    while(cont < num_options){
        inFile >> detail;
        carsBlock.push_back(detail);
        cont++;
    }
    cont = 0;
    while(cont < num_options){
        inFile >> detail;
        blockSize.push_back(detail);
        cont++;
    }
    clase = -1;
    cont = num_options + 1;
    while(inFile >> detail){
        if(cont != num_options + 1){
            classes[clase][cont] = detail;
            cont++;
        }   
        else{   
            cont = 0;
            clase++;
        }
    }
    initial_sol = gen_initial_solution(classes, num_classes, num_vehicles);
    cont= 0;
    while(cont < num_vehicles){
        cout << initial_sol[cont];
        cont++;
    }
    return 0;
}