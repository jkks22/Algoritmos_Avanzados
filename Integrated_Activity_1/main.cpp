/*
& Change history:
Created by: Daniela Angulo on October 4th, 2026

* Team:
- Daniela Angulo A01028153
- Uriel Anzures A01277273
- Josue Gomez A01

? DESCRIPTION
Program that analyzes two data transmissions looking for malicious code.
It reads 5 fixed-name files and:
    - Part 1. Checks if each mcode is contained in each transmission 
    and reports the starting position.
    - Part 2. Finds the longest palindrome in each transmission and 
    reports its start and end positions.
    - Part 3. Finds the longest common substring between both transmissions
    and reports its start and end positions in transmission1.

? INPUT
None. The 5.txt files must exist in the same folder as the executable.

? OUTPUT
6 lines -> (true | false) if the file transmission1/2.txt contains the code 
    (sequence of chars) contained in the file mcode1/2/3.txt
2 lines -> startPosition endPosition (for transmission1/2.txt) 
1 line -> startPosition endPosition (for longest common substring between stream files) 

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include "malicious_code.h"
#include "longest_palindrome.h"
#include "longest_substring.h"

using namespace std;

//Esto habre y lee el contenigo del archivo, para regresarlo en un solo string y poderlo analizar mas facil
string leerarchivo(string n){
    //literal abre el archivo(ya lo usamos con hajmed)
    ifstream archivo(n);

    //Guardamos cada cadena que se vaya leyendo
    string linea;

    //string que va a corresponder al contenido final
    string cont="";

    while(getline(archivo, linea)){
        // Pega la línea al contenido asi los saltos de línea no se guardan
        cont+=linea;
    }
    return cont;
}

int main(){

    string carpeta="test_files/";

    string s1=leerarchivo(carpeta+ "transmission1.txt");

    cout << s1.size() << endl;
    string t1="s1.txt";
    string t2="s2.txt";

    longestsub("ABCDEF", "XXCDEYY");
    




    return 0;
};