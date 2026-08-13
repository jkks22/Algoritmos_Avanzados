/*

Uriel Anzures: Fibonacci Tabulation approach with data structure to store the result
Daniela Angulo: Research and implement the Fibonacci sequence using dynamic programming techniques, including memoization and tabulation.
Josue Gomez: Fibonacci Tabulation approach without storing the result

*/

#include <iostream>
#include <vector>

using namespace std;

// Fibonacci without dianmic programming
int fibonacci(int n) {
    //base case: if n is 0 or 1, return n
    if (n <= 1) {
        //return n
        return n;
    }
    else {
        //recursive case: return the sum of the previous two fibonacci numbers
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

// Fibonacci with memoization
int fibonacciMemo(int n) {
    //vector to store the result
    vector <int> memo = {0,1};
    //if n is less than the size of the vector, return the value at that index
    if (n < memo.size()) {
        //return the value at that index
        return memo[n];
    }
    else{
        //calculate the fibonacci number by adding the previous two fibonacci numbers
        int f = fibonacciMemo(n - 1) + fibonacciMemo(n - 2);
        //add the calculated fibonacci number to the vector
        memo.push_back(f);
        return f;
    } 
}

// Fibonacci with tabulation, store the reult  
int fibonacciTab(int n){
    //vector to store the result
    vector <int> a = {0,1};
    //while the size of the vector is less than or equal to n,
    //calculate the next fibonacci number and add it to the vector
    while( n >= a.size()){
        //calculate the next fibonacci number by adding the last two numbers in the vector
        int i = a[a.size()-1] + a[a.size()-2];
        //add the next fibonacci number to the vector
        a.push_back(i);
    }
    //return the nth fibonacci number
    return a[n];
}

// Dont need to store the result
int fibonacciTab2(int n){
    //variables to store the last two fibonacci numbers
    int a = 0, b = 1, c;
    //if n is 0, return a which is 0
    if (n == 0) {
        //return the first fibonacci number
        return a;
    }
    //if n is 1, return b which is 1
    else if (n == 1) {
        //return the second fibonacci number
        return b;
    }
    //loop from 2 to n, calculating the next fibonacci number by adding the last two
    for (int i = 2; i <= n; i++) {
        //calculate the next fibonacci number
        c = a + b;
        //update the last two fibonacci numbers
        a = b;
        b = c;
    }
    //return the nth fibonacci number
    return b; 
}

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;

    cout << "fibonacci without dynamic programming: " << fibonacci(n) << endl;
    cout << "fibonacci with memoization: " << fibonacciMemo(n) << endl;
    cout << "fibonacci with tabulation: " << fibonacciTab(n) << endl;
    cout << "fibonacci with tabulation without storing the result: " << fibonacciTab2(n) << endl;

    return 0;
}