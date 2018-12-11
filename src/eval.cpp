#include "eval.h"
using namespace std;

int eval(vector<int> &solution,  vector<vector<int>> &options, vector<int> &blockSize, vector<int> &carsBlock, int num_vehicles, int num_options) // Funcion para evaluar calidad de solucion
{
    int eval = 0;
    int windowSize;
    int iter;
    for(int i = 0; i < num_options; i++){ //iterar sobre las distintas opciones
        windowSize = blockSize[i]; // tamaño de la ventana para la opcion i
        for(int j = 0; j < num_vehicles; j++){ //comienzo de la ventana
            iter = 0;
            for(int k = j; k < j + windowSize && k < num_vehicles; k++){ //movimiento por la ventana
                iter += options[solution[k]][i]; //opciones de la clase=
                if(iter > carsBlock[i]){
                    eval++;
                }
            }
        }
    }
    return eval;
}
