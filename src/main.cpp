#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <time.h>
#include <sstream>
#include "HC.h"
#include "eval.h"
#include "randomSol.h"

using namespace std;

//Parámetros
#define RESTART 500;
#define INSTANCIANAME "Problem 60-03";
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
    int cont;
    int clase;
    int num_vehicles, num_classes, num_options;
    int detail;
    string archivos[12] = {"Problem 60-10","Problem 65-04","Problem 65-09","Problem 70-03","Problem 75-08","Problem 80-01","Problem 80-02","Problem 85-05","Problem 90-01","Problem 90-04","Problem 90-07","Problem 90-10"};
    ifstream inFile;
    int arch = 0;
    while(arch < 12){
        cont = 0;
        clase = 0;
        inFile.open("Instances/" + archivos[arch] + ".txt");
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
        inFile.close();
        int testing;
        int testing1 = 0;
        int restarts[6] = {10, 25, 50, 100, 150, 200};
        ofstream myfile;
        vector<double> times;
        vector<int> evals; //500 - 400 = 300 = 200 = 150 = 100 = 50 = 25 = 10
        while(testing1 < 6){
            testing = 0;
            restart = restarts[testing1];
            myfile.open ("Testing/" + to_string(restart) + " Restarts - " + archivos[arch] + ".csv");
            myfile << "Evals;Tiempos\n";
            while(testing < 100){
                restart = restarts[testing1];
                t0=clock();
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
                t1 = clock();
                double time = (double(t1-t0)/CLOCKS_PER_SEC);
                myfile << to_string(bestEval) + ";" + to_string(time) + "\n";
                testing ++;
            }
            cout << "Hice los " + to_string(restarts[testing1]) + "!!!!\n";
            myfile.close();
            evals.clear();
            times.clear();
            testing1++;
        }
        arch++;
    }
    
    
    /*cont = 0;
    cout << "La mejor evaluacion es: " <<bestEval<< "\n";
    cout << "La secuencia es: ";
    while(cont < num_vehicles){
        cout << bestSolution[cont] << " ";
        cont++;
    }
    cout << "\n";
    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;*/
    return 0;
}