#include "eval.h"
using namespace std;
/******** Funcion: eval ********************
Descripcion: calcula la cantidad de violaciones de una solucion
Parametros:
solution vector<int>: vector que representa la solucion del CSP
options vector<vector<int>>:  Vector de vectores que contiene las opciones de cada clase
blockSize vector<int>: tamaño del bloque para cada opcion
carsBlock vector<int>: cantidad maxima de autos por cada bloque
num_vehicles int: numero de vehículos en la secuencia
num_options int: cantidad de opciones disponibles
Retorno: cantidad de violaciones de la solución
************************************************/
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
