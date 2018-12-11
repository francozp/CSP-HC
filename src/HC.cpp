#include "HC.h"
#include "eval.h"
#include "randomSol.h"
using namespace std;

vector<int> climbing(int actual_eval, vector<int> &solution,  vector<vector<int>> &options, vector<int> &blockSize, vector<int> &carsBlock, int num_vehicles, int num_options){
    int min = actual_eval;// AL ESCALAR VERIFICAR PUNTOS EN QUE SE MUEVE ENTRE DOS SOLUCIONES, GUARDAR LA PENULTIMA PARA VERIFICIAR SI ES IGUAL A LA ACTUAL, EN CUYO CASO SE HACE BREAK
    int neighbor_eval;
    vector<int> bestClimb;
    copy(solution.begin(), solution.end(), back_inserter(bestClimb)); 
    for(int i = 0; i < num_vehicles - 1; i++){
        iter_swap(solution.begin() + i,solution.begin()+ i + 1); //vecino
        neighbor_eval = eval(solution,options, blockSize, carsBlock, num_vehicles, num_options);
        if(neighbor_eval <= min){
            min = neighbor_eval;
            bestClimb = solution;
        }
        iter_swap(solution.begin() + i,solution.begin()+ i + 1);
    } 
    return bestClimb;
}

pair<vector<int>, int> HillClimbing(vector<vector<int>> &options, vector<int> &blockSize, vector<int> &carsBlock, int num_vehicles, int num_options, vector<int> &carsQty, int num_classes){
    vector <int> initial_sol = gen_initial_solution(carsQty, num_classes);
    int prev_eval = eval(initial_sol, options, blockSize, carsBlock, num_vehicles, num_options);
    int actual_eval;
    bool repetition = true;
    while(repetition){
        initial_sol = climbing(prev_eval,initial_sol, options, blockSize, carsBlock, num_vehicles, num_options);
        actual_eval = eval(initial_sol, options, blockSize, carsBlock, num_vehicles, num_options);
        if(prev_eval <= actual_eval){
            repetition = false;
        }
        else{
            prev_eval = actual_eval;
        }
    }
    pair<vector<int>, int> sol = make_pair(initial_sol,actual_eval);
    return sol;
}