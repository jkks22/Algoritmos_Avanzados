#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

//board[i] = column of the queen in row i
bool safe(vector <int>& board, int row, int col){
    for(int i = 0; i < row; i++){
        //same column
        if (board[i] == col) {
            return false; }
        //same diagonal: the rows and columns are the same distance apart
        if (abs(board[i] - col) == row - i){
            return false;}
    }
    return true;
}

bool nQueens(vector <int>& board, int row, int n){
    //all the queens were placed
    if (row == n){
        for (int v : board)
        cout << v << ' ';
        cout << '\n';
        return true;
    };
    for (int col = 0; col < n; col++){
        if (safe(board,row,col)){
            board[row] = col;
            if (nQueens(board, row+1,n)){
                return true;
            }
        }
    }
    return false; //no column works, go back to the previous row
}


int main(){
    int n = 8;
    vector <int> board(n);
    if (!nQueens(board,0,n)){
        cout << "No solution\n";
    }
    return 0;
}
