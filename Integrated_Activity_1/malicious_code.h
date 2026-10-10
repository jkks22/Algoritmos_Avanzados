/*
& Change history:
Created by: Daniela Angulo on October 4th, 2026 

? PART 1. 
The program must analyze if the contents of the files mcode1.txt, mcode2.txt, 
and mcode3.txt are contained in the files transmission1.txt and transmission2.txt and 
display a true or false if the chars sequences are contained or not. If true, it displays true,
followed by exactly one space, followed by the position in the transmissionX.txt file where 
the mcodeY.txt code starts.

*/

#ifndef malicious_code_H  
#define malicious_code_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

void mcode(const string& transmissions, const string& pattern){
    int n = transmissions.size();
    int m = pattern.size();

    // tabla LPS: lps[k] = largo del prefijo más largo de pattern[0..k] que también es sufijo
    vector<int> lps(m, 0);
    int len = 0;
    for(int k = 1; k < m; k++){
        while(len > 0 && pattern[k] != pattern[len]){
            len = lps[len - 1];
        }
        if(pattern[k] == pattern[len]){
            len++;
        }
        lps[k] = len;
    }

    // j = cuántos caracteres del mcode llevo coincidiendo
    int j = 0;
    for(int i = 0; i < n; i++){
        while(j > 0 && transmissions[i] != pattern[j]){
            j = lps[j - 1];
        }
        if(transmissions[i] == pattern[j]){
            j++;
        }
        // si j llegó a m, encontré el mcode completo
        if(j == m){
            cout << "true " << i - m + 2 << endl;
            return;
        }
    }

    // si terminó el ciclo sin encontrarlo
    cout << "false" << endl;
}

#endif
