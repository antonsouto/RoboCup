#include "stringutilities.h"
#include <vector>
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

vector<string> separarPalabras(const string &palabra)
{
    int ncaracteres = palabra.size();
    vector<string> resultado;
    string aux;

    for (int i = 0; i < ncaracteres; i++)
    {
        ;
        if (palabra[i] == '(' || palabra[i] == ')')
            continue;
        if (palabra[i] == ' ')
        {
            resultado.push_back(aux);
            aux = "";
            continue;
        }
        aux += palabra[i];
    }
    resultado.push_back(aux); // última palabra
    return resultado;
}

vector<string> separarParentesis(const string &p)
{
    if (p.empty())
    {
        throw runtime_error("Error: String is empty");
    }

    int nivel = 0;
    vector<string> resultado;
    string straux = "";
    bool firstElement = true;

    for (string::const_iterator it = p.begin(); it != p.end(); ++it)
    {
        if (*it == '(')
        {
            if (nivel > 0)
            {
                straux += *it;
            }
            nivel++;
        }
        else if (*it == ')')
        {
            nivel--;
            if (nivel < 0)
            {
                throw runtime_error("Error: More closing parentheses than opening ones");
            }
            if (nivel == 1)
            {
                straux += *it;
                resultado.push_back(straux);
                straux.clear();
            }
            else if (nivel > 0)
            {
                straux += *it;
            }
        }
        else
        {
            if (nivel == 0 && firstElement)
            {
                if (*it != ' ')
                {
                    straux += *it;
                }
                else
                {
                    resultado.push_back(straux);
                    straux.clear();
                    firstElement = false;
                }
            }
            else if (nivel > 0)
            {
                straux += *it;
            }
            else if (!isspace(*it))
            {
                throw runtime_error("Error: Text outside of parentheses");
            }
        }
    }

    if (nivel > 0)
    {
        throw runtime_error("Error: Mismatched parentheses, more opening than closing");
    }

    return resultado;
}

std::vector<std::pair<std::string, std::string>> buscarValores(const std::string &input, const std::string &inicio)
{
    std::vector<std::pair<std::string, std::string>> resultados;
    std::string fin = ")";
    size_t inicio_len = inicio.length();

    size_t pos = input.find(inicio);
    while (pos != std::string::npos)
    {
        // Encontrar el fin de la cadena de valores
        size_t end_pos = input.find(fin, pos + inicio_len);
        if (end_pos == std::string::npos)
        {
            break; // No se encontró el final de la cadena esperada
        }

        // Extraer la subcadena que contiene los valores
        std::string subcadena = input.substr(pos + inicio_len, end_pos - (pos + inicio_len));
        auto palabras = separarPalabras(subcadena);

        // Asegurarse de que hay suficientes palabras
        if (palabras.size() >= 2)
        {
            resultados.emplace_back(palabras[1], palabras[2]);
        }

        // Avanzar la posición para buscar la siguiente ocurrencia del prefijo
        pos = input.find(inicio, end_pos);
    }

    return resultados;
}