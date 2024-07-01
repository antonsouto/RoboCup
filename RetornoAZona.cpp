#include "RetornoAZona.h"
#include "funciones_de_juego.h"
#include <iostream>
#include <thread>
#include <sstream>

using namespace std;

string retornoazona(string const &numerojugador, string const &ladoJugador, pair<pair<float, float>, float> const &coordenadas)
{

    string resultado;

    if (ladoJugador == "l")
    {
        if (numerojugador == "1")
        {
            auto giro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, -50, 0, coordenadas.second);
            return resultado = "(dash 100 " + giro + ")";
        }
        else if (numerojugador == "2")
        {
            auto giro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, -35, -28, coordenadas.second);
            return resultado = "(dash 100 " + giro + ")";
        }
        else if (numerojugador == "5")
        {
            auto giro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, -35, 28, coordenadas.second);
            return resultado = "(dash 100 " + giro + ")";
        }
        else if (numerojugador == "3")
        {
            auto giro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, -42, -14, coordenadas.second);
            return resultado = "(dash 100 " + giro + ")";
        }
        else if (numerojugador == "4")
        {
            auto giro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, -42, 14, coordenadas.second);
            return resultado = "(dash 100 " + giro + ")";
        }
        else if (numerojugador == "6")
        {
            auto giro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, -25, 11, coordenadas.second);
            return resultado = "(dash 100 " + giro + ")";
        }
        else if (numerojugador == "8")
        {
            auto giro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, -25, -11, coordenadas.second);
            return resultado = "(dash 100 " + giro + ")";
        }
        else if (numerojugador == "11")
        {
            auto giro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, -8, -20, coordenadas.second);
            return resultado = "(dash 100 " + giro + ")";
        }
        else if (numerojugador == "7")
        {
            auto giro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, -8, 20, coordenadas.second);
            return resultado = "(dash 100 " + giro + ")";
        }
        else if (numerojugador == "10")
        {
            auto giro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, -15, 0, coordenadas.second);
            return resultado = "(dash 100 " + giro + ")";
        }
        else if (numerojugador == "9")
        {
            auto giro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, -5, 0, coordenadas.second);
            return resultado = "(dash 100 " + giro + ")";
        }
    }
    else
    {
        if (numerojugador == "1")
        {
            auto giro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, 50, 0, coordenadas.second);
            return resultado = "(dash 100 " + giro + ")";
        }
        else if (numerojugador == "2")
        {
            auto giro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, 35, -28, coordenadas.second);
            return resultado = "(dash 100 " + giro + ")";
        }
        else if (numerojugador == "5")
        {
            auto giro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, 35, 28, coordenadas.second);
            return resultado = "(dash 100 " + giro + ")";
        }
        else if (numerojugador == "3")
        {
            auto giro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, 42, -14, coordenadas.second);
            return resultado = "(dash 100 " + giro + ")";
        }
        else if (numerojugador == "4")
        {
            auto giro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, 42, 14, coordenadas.second);
            return resultado = "(dash 100 " + giro + ")";
        }
        else if (numerojugador == "6")
        {
            auto giro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, 25, 11, coordenadas.second);
            return resultado = "(dash 100 " + giro + ")";
        }
        else if (numerojugador == "8")
        {
            auto giro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, 25, -11, coordenadas.second);
            return resultado = "(dash 100 " + giro + ")";
        }
        else if (numerojugador == "11")
        {
            auto giro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, 8, -20, coordenadas.second);
            return resultado = "(dash 100 " + giro + ")";
        }
        else if (numerojugador == "7")
        {
            auto giro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, 8, 20, coordenadas.second);
            return resultado = "(dash 100 " + giro + ")";
        }
        else if (numerojugador == "10")
        {
            auto giro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, 15, 0, coordenadas.second);
            return resultado = "(dash 100 " + giro + ")";
        }
        else if (numerojugador == "9")
        {
            auto giro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, 5, 0, coordenadas.second);
            return resultado = "(dash 100 " + giro + ")";
        }
    }
    return resultado;
}