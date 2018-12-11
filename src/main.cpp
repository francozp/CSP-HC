#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <time.h>

#include "HC.h"
#include "eval.h"
#include "randomSol.h"

using namespace std;

//Parámetros
#define RESTART 200;
#define INSTANCIANAME "Problem 90-10";
int main()
{   
    unsigned t0, t1;
    t0=clock();
    srand(time(NULL));
    vector<int> bestSolution;
    string instancia = INSTANCIANAME;
    int bestEval;
    pair<vector<int>, int> hc;
    int restart = RESTART;
    int cont = 0;
    int clase = 0;
    int num_vehicles, num_classes, num_options;
    int detail;
    ifstream inFile;
    inFile.open("Instances/" + instancia + ".txt");
    if (!inFile){
        cout << "Unable to open file";
        exit(1);
    }
    inFile >> num_vehicles;
    inFile >> num_options;
    inFile >> num_classes;
    vector<vector<int>> options;
    for(int i = 0; i < num_classes; i++){
        options.push_back(vector<int>());
    }
    vector<int> carsQty;
    vector<int> carsBlock;
    vector<int> blockSize;
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
    cout << "\n";
    clase = -1;
    cont = num_options + 1;
    while(inFile >> detail){
        if(cont != num_options + 1){
            if(cont==0){
                carsQty.push_back(detail);
            }
            else{
                options[clase].push_back(detail);
            }
            cont++;
        }   
        else{   
            cont = 0;
            clase++;
        }
    }
    hc = HillClimbing(options, blockSize, carsBlock,num_vehicles, num_options, carsQty, num_classes);
    bestSolution = hc.first;
    bestEval = hc.second;
    while(restart){
        hc = HillClimbing(options, blockSize, carsBlock,num_vehicles, num_options, carsQty, num_classes);
        if(hc.second < bestEval){
            bestSolution = hc.first;
            bestEval = hc.second;
        }
        restart --;
    }
    cont = 0;
    cout << "La mejor evaluacion es: " <<bestEval<< "\n";
    cout << "La secuencia es: ";
    while(cont < num_vehicles){
        cout << bestSolution[cont] << " ";
        cont++;
    }
    cout << "\n";
    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;
    return 0;
}