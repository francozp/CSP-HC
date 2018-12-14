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
#define RESTART 100;
#define INSTANCIANAME "Problem Test";

int main()
{   
    srand (time(NULL));
    vector<int> bestSolution;
    string instancia = INSTANCIANAME;
    int bestEval;
    pair<vector<int>, int> hc;
    int restart = RESTART;
    int cont;
    int clase;
    int num_vehicles, num_classes, num_options;
    int detail;
    ifstream inFile;
    cont = 0;
    clase = 0;
    inFile.open("Instances/" + instancia + ".txt");
    if (!inFile){
        cout << "Unable to open file";
        exit(1);
    }

    //Lectura del archivo
    inFile >> num_vehicles;
    inFile >> num_options;
    inFile >> num_classes;
    vector<vector<int>> options;
    for(int i = 0; i < num_classes; i++){ 
        options.push_back(vector<int>()); //crear vector de opciones
    }
    vector<int> carsQty;
    vector<int> carsBlock;
    vector<int> blockSize;
    while(cont < num_options){
        inFile >> detail;
        carsBlock.push_back(detail); //crear vector de autos x bloque
        cont++;
    }
    cont = 0;
    while(cont < num_options){
        inFile >> detail;
        blockSize.push_back(detail); //crear vector de tamaño del bloque
        cont++;
    }
    clase = -1;
    cont = num_options + 1;
    while(inFile >> detail){ 
        if(cont != num_options + 1){
            if(cont==0){
                carsQty.push_back(detail); //crear vectores de cantidad de autos por clase
            }
            else{
                options[clase].push_back(detail); //asignar valores al vector de opciones
            }
            cont++;
        }   
        else{   
            cont = 0;
            clase++;
        }
    }
    inFile.close();
    hc = HillClimbing(options, blockSize, carsBlock,num_vehicles, num_options, carsQty, num_classes);
    bestSolution = hc.first;
    bestEval = hc.second;
    while(restart){ // repetir el algoritmo la cantidad de veces especificadas
        hc = HillClimbing(options, blockSize, carsBlock,num_vehicles, num_options, carsQty, num_classes); //hacer hill climbing 
        if(hc.second < bestEval){ //seleccionar la mejor solucion
            bestSolution = hc.first;
            bestEval = hc.second;
        }
        restart --;
    }
    int cont1 = 0;
    cont = 0;
    ofstream outputFile;
    outputFile.open ("INSTANCIA.out"); //archivo sobre el que se ecribiran los resultados
    while(cont < num_vehicles){ //escribir el output
        outputFile << to_string(bestSolution[cont]) + "  ";
        cont1 = 0;
        while(cont1 < num_options){
            outputFile << to_string(options[bestSolution[cont]][cont1]);
            cont1++;
        }
        outputFile << "\n";
        cont++;
    }
    outputFile.close();
    return 0;
}