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

bool zonaJuego(string numerojugador, string lado, pair<float, float> coordenadas)
{
    float x = abs(coordenadas.first);
    float y = abs(coordenadas.second);

    if (numerojugador == "1")
    {
        return ((37 <= x && x <= 52) && (y < 19));
    }
    else if (numerojugador == "2" || numerojugador == "5")
    {
        return ((25 <= y && y <= 33));
    }
    else if (numerojugador == "3" || numerojugador == "4")
    {
        return ((25 <= x && x <= 52) && (0 <= y && y <= 25));
    }

    else if ((numerojugador == "6" || numerojugador == "8") && (lado == "l"))
    {
        return ((-40 <= coordenadas.first && coordenadas.first <= 30) && (5 <= y && y <= 33));
    }
    else if ((numerojugador == "6" || numerojugador == "8") && (lado == "r"))
    {
        return ((40 >= coordenadas.first && coordenadas.first >= -30) && (5 <= y && y <= 33));
    }
    else if ((numerojugador == "7" || numerojugador == "11") && (lado == "l"))
    {
        return ((-10 <= coordenadas.first && coordenadas.first <= 40) && (5 <= y && y <= 33));
    }
    else if ((numerojugador == "7" || numerojugador == "11") && (lado == "r"))
    {
        return ((10 >= coordenadas.first && coordenadas.first >= -40) && (5 <= y && y <= 33));
    }
    else if ((numerojugador == "10") && (lado == "l"))
    {
        return ((-25 <= coordenadas.first && coordenadas.first <= 40) && (0 <= y && y <= 25));
    }
    else if ((numerojugador == "10") && (lado == "r"))
    {
        return ((25 >= coordenadas.first && coordenadas.first >= -40) && (0 <= y && y <= 25));
    }
    else if ((numerojugador == "9") && (lado == "l"))
    {
        return ((-15 <= coordenadas.first && coordenadas.first <= 50) && (0 <= y && y <= 25));
    }
    else if ((numerojugador == "9") && (lado == "r"))
    {
        return ((-50 <= coordenadas.first && coordenadas.first <= 15) && (0 <= y && y <= 25));
    }
    else
    {
        return false;
    }
}