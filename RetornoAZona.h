#pragma once

#include <string>
using namespace std;

string retornoazona(string const &numerojugador, string const &ladoJugador, pair<pair<float, float>, float> const &coordenadas);

bool zonaJuego(string numerojugador, string lado, pair<float, float> coordenadas);