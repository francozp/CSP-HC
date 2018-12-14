#include "HC.h"
#include "eval.h"
#include "randomSol.h"
using namespace std;
/******** Funcion: climbing ********************
Descripcion: busca la mejor solucion dentro del vecindario de una solucion actual
Parametros:
actual_eval int: violaciones de la cantidad actual
solution vector<int>: vector que representa la solucion del CSP
options vector<vector<int>>:  Vector de vectores que contiene las opciones de cada clase
blockSize vector<int>: tamaño del bloque para cada opcion
carsBlock vector<int>: cantidad maxima de autos por cada bloque
num_vehicles int: numero de vehículos en la secuencia
num_options int: cantidad de opciones disponibles
Retorno: vector con la solucion obtenida tras ver el vecindario
************************************************/
vector<int> climbing(int actual_eval, vector<int> &solution,  vector<vector<int>> &options, vector<int> &blockSize, vector<int> &carsBlock, int num_vehicles, int num_options){
    int min = actual_eval;
    int neighbor_eval;
    vector<int> bestClimb;
    copy(solution.begin(), solution.end(), back_inserter(bestClimb)); 
    for(int i = 0; i < num_vehicles - 1; i++){
        iter_swap(solution.begin() + i,solution.begin()+ i + 1); //vecino
        neighbor_eval = eval(solution,options, blockSize, carsBlock, num_vehicles, num_options);//evaluar calidad de la solucion
        if(neighbor_eval <= min){ //seleccionar solucion solo si es igual o mejora la actual
            min = neighbor_eval;
            bestClimb = solution;
        }
        iter_swap(solution.begin() + i,solution.begin()+ i + 1);//volver a la solucion inicial
    } 
    return bestClimb;
}

/******** Funcion: HillClimbing ********************
Descripcion: busca la mejor solucion posible y la entrega junto a su cantidad de violaciones
Parametros:
options vector<vector<int>>:  Vector de vectores que contiene las opciones de cada clase
blockSize vector<int>: tamaño del bloque para cada opcion
carsBlock vector<int>: cantidad maxima de autos por cada bloque
num_vehicles int: numero de vehículos en la secuencia
num_options int: cantidad de opciones disponibles
carsQty vector<int>: numeros de autos de cada clase
num_classes int: numero de clases de autos distintas
Retorno: vector con la solucion obtenida tras ver el vecindario y su cantidad de violaciones
************************************************/
pair<vector<int>, int> HillClimbing(vector<vector<int>> &options, vector<int> &blockSize, vector<int> &carsBlock, int num_vehicles, int num_options, vector<int> &carsQty, int num_classes){
    vector <int> initial_sol = gen_initial_solution(carsQty, num_classes); //generar solucion aleatoria
    int prev_eval = eval(initial_sol, options, blockSize, carsBlock, num_vehicles, num_options);
    int actual_eval;
    bool repetition = true;
    while(repetition){ // Buscar soluciones hasta que no se encuentre una solucion mejor
        initial_sol = climbing(prev_eval,initial_sol, options, blockSize, carsBlock, num_vehicles, num_options); //Mejor mejora
        actual_eval = eval(initial_sol, options, blockSize, carsBlock, num_vehicles, num_options); // evaluar
        if(prev_eval <= actual_eval){ //si es peor, terminar 
            repetition = false;
        }
        else{
            prev_eval = actual_eval;
        }
    }
    pair<vector<int>, int> sol = make_pair(initial_sol,actual_eval);
    return sol;
}