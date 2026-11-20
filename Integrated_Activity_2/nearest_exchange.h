/*
? PART 3.
Given the location of several exchanges, decides which exchange is geographically
closest to a new service contract and displays the distance and its location.
There is not necessarily one exchange for each neighborhood.
*/

#ifndef nearest_exchange_H
#define nearest_exchange_H

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//^ Euclidean distance 

void nearestExchange(const vector<pair<double, double>>& exchanges, pair<double, double> contract){
    //~ step 1: compare the contract with every exchange and keep the closest one
    int closest = 0;
    double minDistance = INFINITY;
    for (int i = 0; i < exchanges.size(); i++){
        double dx = exchanges[i].first - contract.first;  //distance in x
        double dy = exchanges[i].second - contract.second;  //disrance in y
        double distance = sqrt(dx * dx + dy * dy);  //linear distance
        if (distance < minDistance){ //the new distance is lower than the last saved?
            minDistance = distance;
            closest = i;
        }
    }

    //~ step 2: print the closest exchange and how far it is
    cout << "Contract (" << contract.first << "," << contract.second << ") -> exchange ("
         << exchanges[closest].first << "," << exchanges[closest].second << "), distance: "
         << minDistance << endl;
}
#endif
