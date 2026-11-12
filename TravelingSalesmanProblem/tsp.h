#ifndef TSP_H
#define TSP_H

//~ function bound, returns a lower bound on the cost of completing the tour from the current city
int bound(int current, int currentCost){
    int b = currentCost + minEdge[current];
    for (int i = 0; i < n; i++) {
        if (!visited[i]) 
            b += minEdge[i];
    }
    return b;
}

//~ function tsp, solves the traveling salesman problem using branch and bound
int tsp(int current, int currentCost, int level, int start) {
    //case 1: all the cities were visited: go back to the start
    if (level == n) {
        int total = currentCost + cost[current][start];
        if (total < bestCost) {
            bestCost = total;
            bestRoute = route;
        }
        return 0;
    }

    //case 2: try every city that is not visited yet
    for (int next = 0; next < n; next++) {
        if (!visited[next] && next != current) {
            int newCost = currentCost + cost[current][next];

            visited[next] = true;
            route.push_back(next);

            //only continue if this branch can still beat the best route
            if (bound(next, newCost) < bestCost) {
                tsp(next, newCost, level + 1, start);
            }

            // backtracking, undo the move
            visited[next] = false;
            route.pop_back();
        }
    }
    return 0;
}

//~ returns the cost of the best route found so far
int bestRouteCost() {
    int total = 0;
    for (int i = 0; i < bestRoute.size() - 1; i++) {
        total += cost[bestRoute[i]][bestRoute[i + 1]];
    }
    total += cost[bestRoute.back()][bestRoute[0]]; // return to start
    return total;
}

#endif