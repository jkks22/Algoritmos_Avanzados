#ifndef BESTROUTE_H
#define BESTROUTE_H

//! function bestRouteCost, returns the cost of the best route found so far
int bestRouteCost() {
    int total = 0;
    for (int i = 0; i < bestRoute.size() - 1; i++) {
        total += cost[bestRoute[i]][bestRoute[i + 1]];
    }
    total += cost[bestRoute.back()][bestRoute[0]]; //? return to start
    return total;
}

#endif