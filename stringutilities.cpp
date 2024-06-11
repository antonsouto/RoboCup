#include"stringutilities.h"
#include<vector>
#include<iostream>


using namespace std;

vector<string> separarPalabras(const string& palabra) {
    int ncaracteres = palabra.size();
    vector<string>resultado;
    string aux;

    for (int i = 0; i < ncaracteres; i++) {
       ;
        if (palabra[i] == '(' || palabra[i] == ')')continue;
        if (palabra[i] == ' ') {
            resultado.push_back(aux);
            aux = "";
            continue;
        }
        aux += palabra[i];
    }
    resultado.push_back(aux); //última palabra 
    return resultado;
}
