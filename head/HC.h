#ifndef HILLCLIMBING
#define HILLCLIMBING
#include <vector>
using namespace std;

vector<int> climbing(int actual_eval, vector<int> &solution,  vector<vector<int>> &options, vector<int> &blockSize, vector<int> &carsBlock, int num_vehicles, int num_options);
pair<vector<int>, int> HillClimbing(vector<vector<int>> &options, vector<int> &blockSize, vector<int> &carsBlock, int num_vehicles, int num_options, vector<int> &carsQty, int num_classes);


#endif