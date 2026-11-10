#ifndef TSP_H
#define TSP_H

//! function tsp, solves the traveling salesman problem using branch and bound
int tsp(int current, int currentCost, int level, int start) {
    //! all the cities were visited: go back to the start
    if (level == n) {
        int total = currentCost + cost[current][start];
        if (total < bestCost) {
            bestCost = total;
            bestRoute = route;
        }
        return 0;
    }

    //! branch, try every city that is not visited yet
    for (int next = 0; next < n; next++) {
        if (!visited[next] && next != current) {
            int newCost = currentCost + cost[current][next];

            visited[next] = true;
            route.push_back(next);

            //! bound, only continue if this branch can still beat the best route
            if (bound(next, newCost) < bestCost) {
                tsp(next, newCost, level + 1, start);
            }

            //! backtracking, undo the move
            visited[next] = false;
            route.pop_back();
        }
    }
    return 0;
}