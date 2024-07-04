#pragma once
#include <iostream>

using namespace std;

// POSIBLEMENTE ESTO SEA NUESTRA CLASE JUGADOR EN UN FUTURO

/**
 * @brief FUNCION QUE GESTIONA LA LLEGADA DE INFORMACIÓN
 * Gestiona tambien las dos funciones que rigen el comportamiento del jugador : Ver() y Escuchar()
 *
 *
 * @param received_message_content mensaje en CRUDO recibido del servidor
 * @param ladojugador, numero, team_name parametros por copia que representan la información de nuestro jugador
 * @return MENSAJE ENVIADO AL SERVIDOR EN CADA CICLO
 */
string procesado(string received_message_content, string ladoJugador, string numero, string team_name);

/**
 * @brief FUNCION QUE GESTIONA LA LLEGADA DE INFORMACIÓN
 * Gestiona tambien las dos funciones que rigen el comportamiento del jugador : Ver() y Escuchar()
 *
 *
 * @param received_message_content mensaje en CRUDO recibido del servidor
 * @param ladojugador, numero, team_name parametros por copia que representan la información de nuestro jugador
 * @return MENSAJE ENVIADO AL SERVIDOR EN CADA CICLO
 */

// ESTAS DOS LAS QUITO CUANDO PONGO LOS COOMENTARIOS PORQUE ESTAN DEFINIDAS EN OTRO ARCHIVO
// bool zonaJuego(string numerojugador, string lado, pair<float, float> coordenadas);

// string calculoangulogiro(float x, float y, float xgiro, float ygiro, float angulojugador);
