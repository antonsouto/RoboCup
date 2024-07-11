#include <vector>
#include <iostream>
#include "colocarjugadores.h"
#include "stringutilities.h"

using namespace std;

// Inicializa cada jugador en el campo en función del mensaje que retorne el servidor en la primera consulta, ej: (init l 1 before_kick_off)
// devuelve un string con el mensaje de posicion para este jugador, por ejemplo (move -35 28)

string inicializoJugador(const string &respuesta)
{
    vector<string> vrespuesta = separarPalabras(respuesta);
    string mensaje; // mensaje que se le envia al servidor para que instancie los jugadores en sus posiciones iniciales

    if (vrespuesta[2] == "1")
    { //(init l 1 before_kick_off)
        mensaje = "(move -51 0)";
    }
    else if (vrespuesta[2] == "2")
    {
        mensaje = "(move -35 -14)";
    }
    else if (vrespuesta[2] == "3")
    {
        mensaje = "(move -36 -3)";
    }
    else if (vrespuesta[2] == "4")
    {
        mensaje = "(move -36 3)";
    }
    else if (vrespuesta[2] == "5")
    {
        mensaje = "(move -35 14)";
    }
    else if (vrespuesta[2] == "6")
    {
        mensaje = "(move -25 9)";
    }
    else if (vrespuesta[2] == "10")
    {
        mensaje = "(move -8 20)";
    }
    else if (vrespuesta[2] == "8")
    {
        mensaje = "(move -25 -9)";
    }
    else if (vrespuesta[2] == "9")
    {
        mensaje = "(move -0.5 0)";
    }
    else if (vrespuesta[2] == "7")
    {
        mensaje = "(move -15 0)";
    }
    else if (vrespuesta[2] == "11")
    {
        mensaje = "(move -8 -20)";
    }
    return mensaje;
}
