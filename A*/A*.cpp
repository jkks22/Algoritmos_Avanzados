#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
using namespace std;

const int INF = 1000000000; //? infinity

//? heuristic: Manhattan distance from (r, c) to the goal, never overestimates on a 4-direction grid
int heuristic(int r, int c, int goalR, int goalC) {
    return abs(r - goalR) + abs(c - goalC);
}

//? prints the path from the start cell to "cell" following the previous[] array
void printPath(vector<int>& previous, int cell, int cols) {
    if (previous[cell] != -1) {
        printPath(previous, previous[cell], cols); //? first print how we got to the previous cell
        cout << " -> ";
    }
    cout << "(" << cell / cols << "," << cell % cols << ")";
}

int main() {
    //! step 1: the map, 0 = free cell, 1 = wall
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 1, 0},
        {1, 1, 0, 1, 1, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 1, 0},
    };
    int rows = grid.size();
    int cols = grid[0].size();
    int startR = 0, startC = 0; //? start cell
    int goalR = 4, goalC = 3;   //? goal cell

    //! step 2: prepare the arrays, each cell is saved as one number: r * cols + c
    vector<int> g(rows * cols, INF);      //? real cost from the start to each cell
    vector<int> previous(rows * cols, -1); //? from which cell we arrive (to build the path)
    vector<bool> closed(rows * cols, false); //? if the cell is already final

    //? open list ordered by f = g + h, the smallest f comes out first
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> open;
    int start = startR * cols + startC;
    int goal = goalR * cols + goalC;
    g[start] = 0;
    open.push({heuristic(startR, startC, goalR, goalC), start});

    int dr[] = {-1, 1, 0, 0}; //? up, down, left, right
    int dc[] = {0, 0, -1, 1};

    //! step 3: repeat until the open list is empty or we reach the goal
    while (!open.empty()) {
        int current = open.top().second;
        open.pop();
        if (closed[current]) continue; //? old copy of a cell we already improved
        closed[current] = true;
        if (current == goal) break;

        //! step 4: update the neighbors of current
        int r = current / cols;
        int c = current % cols;
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || grid[nr][nc] == 1) continue; //? outside or wall
            int next = nr * cols + nc;
            if (!closed[next] && g[current] + 1 < g[next]) {
                g[next] = g[current] + 1;
                previous[next] = current;
                open.push({g[next] + heuristic(nr, nc, goalR, goalC), next});
            }
        }
    }

    //! step 5: print the result
    if (g[goal] == INF) {
        cout << "There is no path to the goal\n";
        return 0;
    }
    cout << "Path: ";
    printPath(previous, goal, cols);
    cout << "\nCost: " << g[goal] << "\n";
    return 0;
}
