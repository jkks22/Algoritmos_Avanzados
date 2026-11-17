/*
? DESCRIPTION
Program that helps a company that wants to venture into Internet services.
It reads the fixed-name file input.txt and:
    - Part 1. Finds the optimal way to wire the neighborhoods with optical fiber.
    - Part 2. Finds the shortest route that visits every neighborhood once
    and returns to the origin.
    - Part 3. Finds the maximum information flow from the initial node to the final node.
    - Part 4. Finds the exchange that is geographically closest to each new contract.

? INPUT (input.txt)
N -> number of neighborhoods
N x N matrix -> distances in km between neighborhoods (0 = no cable possible)
N x N matrix -> maximum data transmission capacity between neighborhoods
N ordered pairs (x,y) -> location of the exchanges
any number of ordered pairs (x,y) -> location of the new contracts

? OUTPUT
1. list of arcs (A,B) to wire with fiber
2. route for the delivery personnel, starting and ending in A
3. max information flow from the first to the last neighborhood
4. closest exchange to each new contract and its distance

*/

#include <iostream>
#include <fstream>
#include <vector>
#include "fiber_wiring.h"
#include "delivery_route.h"
#include "max_flow.h"
#include "nearest_exchange.h"

using namespace std;

//reads an N x N matrix from the file
vector<vector<int>> readMatrix(ifstream& file, int n){
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            file >> matrix[i][j];
        }
    }
    return matrix;
};

//reads one ordered pair of the form (x,y), returns false when there are no more
bool readPoint(ifstream& file, pair<double, double>& point){
    char open, comma, close;
    return (file >> open >> point.first >> comma >> point.second >> close) && open == '(' && comma == ',' && close == ')';
};

int main(){
    ifstream file("input.txt");
    if(!file){
        cout << "Can't open input.txt" << endl;
        return 1;
    }

    int n;
    if(!(file >> n) || n < 2 || n > 26){ //cities are named A..Z
        cout << "N must be between 2 and 26" << endl;
        return 1;
    }
    vector<vector<int>> distance = readMatrix(file, n);
    vector<vector<int>> capacity = readMatrix(file, n);

    vector<pair<double, double>> exchanges;
    pair<double, double> point;
    for(int i = 0; i < n && readPoint(file, point); i++){
        exchanges.push_back(point);
    }
    vector<pair<double, double>> contracts;
    while(readPoint(file, point)){
        contracts.push_back(point);
    }

    if(!file.eof() || exchanges.size() != n){
        cout << "input.txt does not have the expected format" << endl;
        return 1;
    }

    cout << "--- Part 1. fiber wiring: ---" << endl;
    fiberWiring(distance);
    cout << endl;

    cout << "--- Part 2. delivery route: ---" << endl;
    deliveryRoute(distance);
    cout << endl;

    cout << "--- Part 3. max information flow: ---" << endl;
    maxFlow(capacity);
    cout << endl;

    cout << "--- Part 4. nearest exchange: ---" << endl;
    for(int i = 0; i < contracts.size(); i++){
        nearestExchange(exchanges, contracts[i]);
    }
    cout << endl;

    return 0;
};
