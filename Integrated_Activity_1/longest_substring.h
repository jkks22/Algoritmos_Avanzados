/*
& Change history:
Created by: Daniela Angulo on October 4th, 2026


? PART 3. 
The program analyzes how similar the transmission files are, it 
should display the starting position and the ending position (starting at 1) 
of the first file where the longest common substring between both stream files is found.

*/

#ifndef longest_substring_H
#define longest_substring_H

#include <iostream>
#include <string>
using namespace std;

void longestsub(const string& s1,const string& s2){
    //largo del substring
    int largo=0;
    //Posicion en el primer string empezando desde 1
    int inicio=0;
    //i para s1, j para s2
    for(int i=0; i <s1.size() ;i++){
        for (int j=0; j < s2.size();j++){
            //contador para los caracteres iguales
            int c=0;
            //bucle con limite para no salir nos arreglos y generar basura(ademas claro de lleavr el contador).
            while(i+c<s1.size() && j+c<s2.size()){
                //caracteres distintos=salir del bucle
                if (s1[i+c] != s2[j+c]){break;}
                c++;

            }
            // Si el counter es mayor que el anterior pues es una coincidencia majora
            if (c > largo){
                largo = c;
                inicio = i;
            }
        }
    }
    // Inicio y fin 
    cout << inicio + 1 << " " << inicio + largo << endl;

}


#endif