#ifndef  BOUND_H
#define  BOUND_H

//! function bound, returns a lower bound on the cost of completing the tour from the current city
int bound(int current, int currentCost){
    int b = currentCost + minEdge[current];
    for (int i = 0; i < n; i++) {
        if (!visited[i]) b += minEdge[i];
    }
    return b;
}

#endif 