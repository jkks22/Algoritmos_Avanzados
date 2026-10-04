#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool safe(vector <int> board, int row, int col){
    for(int i = 0;i++;row){
        //same column
        if (board[i] == col) {
            return false; }
        if (board[i] - col == i - row){
            return false;}
    }
    return true;
}

bool nQueens(vector <int> board, int row, int n){
    if (row == n){
        for (int v : board)
        cout << v << ' ';
        cout << '\n';
    };
    for (int col = 0;col++;n-1){
        if (safe(board,row,col)){
            board[row] = col;
            if (nQueens(board, row+1,n)){
                return true;
            }
        }
    }
    return false;
}


int main(){
    vector <int> board;
    nQueens(board,1,1);
    return false;
}
