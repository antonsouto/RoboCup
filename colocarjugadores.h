#include <iostream>
#pragma once

using namespace std;

// ESTO SE DEBERÁ METER EN LA CLASE JUGADOR EN UN FUTURO QUE PROBABLEMENTE SEA NUESTRA ACTUAL "funciones_de_juego.h"
/**
 * @brief FUNCION QUE GESTIONA LA COLOCACION DE LOS JUGADORES AL INICIO DE CADA PARTE
 *
 * @param respuesta (init l 1 before_kick_off) Primer mensaje enviado por el servidor con nuestros datos principales.
 * @return MENSAJE ENVIADO AL SERVIDOR PARA COLOCAR EL JUGADOR
 */

string inicializoJugador(const string &respuesta);