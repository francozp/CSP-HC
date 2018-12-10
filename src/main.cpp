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

vector<int> gen_initial_solution(vector<int> carsQty,int num_classes){
    srand(time(NULL));
    vector<int> initialsol;
    int cont = 0;
    int cont1 = 0;
    int cars;
    while(cont < num_classes){
        cars = carsQty[cont];
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

int eval(vector<int> solution,  vector<vector<int>> options, vector<int> blockSize, vector<int> carsBlock, int num_vehicles, int num_options) // Funcion para evaluar calidad de solucion
{
    int eval = 0;
    int windowSize;
    int iter;
    for(int i = 0; i < num_options; i++){ //iterar sobre las distintas opciones
        windowSize = blockSize[i]; // tamaño de la ventana para la opcion i
        iter = 0;
        for(int j = 0; j < num_vehicles; j++){ //comienzo de la ventana
            for(int k = j; k < j + windowSize && k < num_vehicles; k++){ //movimiento por la ventana
                iter += options[solution[k]][i]; //opciones de la clase=
            }
            if(iter > carsBlock[i]){
                eval++;
            }
        }
    }
    return eval;
}

int neighbor(vector<int> solution, int Position, int nextPosition){
    iter_swap(solution.begin() + Position,solution.begin()+ nextPosition);
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
    vector<vector<int>> options(num_classes, vector<int>(num_options));
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
                options[clase][cont] = detail;
            }
            cont++;
        }   
        else{   
            cont = 0;
            clase++;
        }
    }
    initial_sol = gen_initial_solution(carsQty, num_classes);
    cont= 0;
    /*while(cont < num_vehicles){
        cout << initial_sol[cont];
        cont++;
    }*/
    cout << eval(initial_sol, options, blockSize, carsBlock, num_vehicles, num_options);
    return 0;
}