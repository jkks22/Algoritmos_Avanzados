/*
? DESCRIPTION
Program that helps a company that wants to venture into Internet services.
It reads the fixed-name file input.txt and:
    - Part 1. Finds the optimal way to wire the neighborhoods with optical fiber.
    - Part 2. Finds the shortest route that visits every neighborhood once
    and returns to the origin.
    - Part 3. Finds the exchange that is geographically closest to each new contract.

? INPUT (input.txt)
N -> number of neighborhoods
N x N matrix -> distances in km between neighborhoods (0 = no cable possible)
N ordered pairs (x,y) -> location of the exchanges
any number of ordered pairs (x,y) -> location of the new contracts

? OUTPUT
1. list of arcs (A,B) to wire with fiber
2. route for the delivery personnel, starting and ending in A
3. closest exchange to each new contract and its distance

*/

#include <iostream>
#include <fstream>
#include <vector>
#include "fiber_wiring.h"
#include "delivery_route.h"
#include "nearest_exchange.h"

using namespace std;

//reads an N x N matrix from the file
vector<vector<int>> readMatrix(ifstream& file, int n){
    vector<vector<int>> matrix(n, vector<int>(n, 0));  //"default matrix" only with zeros
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            file >> matrix[i][j];  //fill the matrix
        }
    }
    return matrix;
}

//reads one ordered pair of the form (x,y), returns false when there are no more
bool readPoint(ifstream& file, pair<double, double>& point){
    char open, comma, close;
    return (file >> open >> point.first >> comma >> point.second >> close) && open == '(' && comma == ',' && close == ')';
}

int main(){
    ifstream file("input.txt");  //open file
    if(!file){  //error
        cout << "Can't open input.txt" << endl;
        return 1;
    }

    int n;
    if (!(file >> n) || n < 2 || n > 26){ //if there isn't any number, are less than 2 neighborhoods or more than 26
        cout << "N must be between 2 and 26" << endl;  //error
        return 1;
    }
    vector<vector<int>> distance = readMatrix(file, n);  //everything ok, read the matrix

    vector<pair<double, double>> exchanges;
    pair<double, double> point;
    for(int i = 0; i < n && readPoint(file, point); i++){  //saves every server
        exchanges.push_back(point);
    }
    vector<pair<double, double>> contracts;
    while(readPoint(file, point)){  //saves every new contract
        contracts.push_back(point);
    }

    if(!file.eof() || exchanges.size() != n){  //error in txt
        cout << "input.txt does not have the expected format" << endl;
        return 1;
    }
    //print
    cout << "--- Part 1. fiber wiring: ---" << endl;
    fiberWiring(distance);
    cout << endl;

    cout << "--- Part 2. delivery route: ---" << endl;
    deliveryRoute(distance);
    cout << endl;

    cout << "--- Part 3. nearest exchange: ---" << endl;
    for(int i = 0; i < contracts.size(); i++){
        nearestExchange(exchanges, contracts[i]);
    }
    cout << endl;

    return 0;
};
