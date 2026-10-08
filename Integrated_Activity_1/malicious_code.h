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
using namespace std;

void mcode(string t,string m){
    // i es la posición de la transmisión donde pruebo si empieza el mcode
    for(int i=0; i < t.size();i++){
        //counter
        int c=0;
        // Se repite mientras no me salga del mcode ni de la transmisión
        while(c<m.size() && i+c<t.size()){
            if (t[i + c] != m[c]){break;}
               c++;
        }
        // Si c llegó al tamaño del mcode, coincidieron todos los caracteres
        if (c == m.size()){
            cout << "true " << i + 1 << endl;
            return;
        }
    }
    // Si el ciclo terminó sin encontrarlo
    cout << "false" << endl;
}






#endif