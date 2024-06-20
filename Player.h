#pragma once
#include <iostream>
#include "estructuras.h"

using namespace std;

class Player
{
private:
    MatchInit datos;
    Datos_Partido informacion_externa;

public:
    Player();
    ~Player();

    void setPlayer(const string &cadena, const string &equipo);
    void setDatos(const string &cadena);
};