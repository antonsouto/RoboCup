#pragma once
#include <iostream>

using namespace std;

string procesado(string received_message_content, string ladoJugador, string numero, string team_name);
bool zonaJuego(string numerojugador, string lado, pair<float, float> coordenadas);
string calculoangulogiro(float x, float y, float xgiro, float ygiro, float angulojugador);
