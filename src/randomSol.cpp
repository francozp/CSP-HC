#include <algorithm>
#include "randomSol.h"
using namespace std;
/******** Funcion: get_initial_solution ********************
Descripcion: crea una solucion inicial aleatoria considerando la cantidad de vehiculos que se deben producir de cada clase
Parametros:
carsQty vector<int>: numeros de autos de cada clase
num_classes int: numero de clases de autos distintas
Retorno: vector con una solucion aleatoria
************************************************/
vector<int> gen_initial_solution(vector<int> &carsQty,int num_classes){
    vector<int> initialsol;
    int cont = 0;
    int cont1 = 0;
    int cars;
    while(cont < num_classes){//Colocar los autos necesarios en el vector
        cars = carsQty[cont];
        cont1 = 0;
        while(cont1 < cars){
            initialsol.push_back(cont);
            cont1++;
        }
        cont++;
    }
    random_shuffle(initialsol.begin(), initialsol.end());//desordenar el vector
    return initialsol;
}
