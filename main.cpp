#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

int main()
{
    int cont = 0;
    int clase = 0;
    int num_classes, num_options;
    int detail;
    ifstream inFile;
    inFile.open("Instancias/test1.txt");
    if (!inFile){
        cout << "Unable to open file";
        exit(1);
    }
    inFile >> num_options;
    inFile >> num_classes;
    vector<vector<int> > classes(num_classes, vector<int>(num_options+1));   
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
    clase = 0;
    cont = num_options + 1;
    while(inFile >> detail){
        if(cont != num_options + 1){
            classes[clase][cont] = detail;
            cont++;
        }
        else{
            cont = 0;
            clase++;
        }
    }
    cout << classes[2][0];
    return 0;
}