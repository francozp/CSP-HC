#include <algorithm>
#include "randomSol.h"
using namespace std;

vector<int> gen_initial_solution(vector<int> &carsQty,int num_classes){
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
