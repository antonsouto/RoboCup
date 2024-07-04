#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief Dado un string separa las palabras contenidas dentro del primer parentesis
 *
 *
 * @param p Palabra recibida por el servidor
 * @param container Estructura donde se almacenan los datos extraidos de la palabra.
 * @return devuelve las coordenadas absolutas del jugador
 */
vector<string> separarPalabras(const string &palabra);
vector<string> separarParentesis(const string &p);
pair<string, string> buscarValores(const std::string &input, const std::string &inicio);
string trim_left(const std::string &str);