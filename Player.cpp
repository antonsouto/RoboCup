
#include <iostream>
#include <vector>
#include "stringutilities.h"
#include <string>
#include "Player.h"
#include "Minimal-Socket/src/header/MinimalSocket/udp/UdpSocket.h"

using namespace std;

Player::Player() {}
Player::~Player() { cout << "Elimino jugador" << endl; }

void Player::setPlayer(const string &cadena, const string &equipo)
{
    vector<string> aux = separarPalabras(cadena); // {"init r 1 before_kick_off"}

    if (aux.at(0) != "init")
    {
        throw runtime_error("Error: No se puede ejecutar getPlayer porque no es un mensaje init");
    }

    if (aux.at(1) == "l")
    {
        this->datos.field = LEFT;
    }
    else
    {
        this->datos.field = RIGHT;
    }

    this->datos.dorsal = stoi(aux.at(2));
    this->datos.equipo = equipo;
}

void setDatos(const string &cadena)
{
}
