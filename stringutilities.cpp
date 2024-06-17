#include"stringutilities.h"
#include<vector>
#include<iostream>
#include <string>
#include <stdexcept>


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

vector<string> separarParentesis(const string& p) {
    if (p.empty()) {
        throw runtime_error("Error: String is empty");
    }

    int nivel = 0;
    vector<string> resultado;
    string straux = "";
    bool firstElement = true;

    for (string::const_iterator it = p.begin(); it != p.end(); ++it) {
        if (*it == '(') {
            if (nivel > 0) {
                straux += *it;
            }
            nivel++;
        } else if (*it == ')') {
            nivel--;
            if (nivel < 0) {
                throw runtime_error("Error: More closing parentheses than opening ones");
            }
            if (nivel == 1) {
                straux += *it;
                resultado.push_back(straux);
                straux.clear();
            } else if (nivel > 0) {
                straux += *it;
            }
        } else {
            if (nivel == 0 && firstElement) {
                if (*it != ' ') {
                    straux += *it;
                } else {
                    resultado.push_back(straux);
                    straux.clear();
                    firstElement = false;
                }
            } else if (nivel > 0) {
                straux += *it;
            } else if (!isspace(*it)) {
                throw runtime_error("Error: Text outside of parentheses");
            }
        }
    }

    if (nivel > 0) {
        throw runtime_error("Error: Mismatched parentheses, more opening than closing");
    }

    return resultado;
}