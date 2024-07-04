#pragma once

#include <functional>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <cmath>
#include "stringutilities.h"
#include <sstream>
using namespace std;
typedef pair<string, string> vp;

//--------------------------------------------------------------------------------VECTOR DE COORDENADAS ABSOLUTAS DEL CAMPO
extern vector<pair<string, vp>> coordenadasABS;

struct visioncampo
{
    vp cornersupizq;  // flt
    vp cornersupder;  // frt
    vp cornerinfizq;  // flb
    vp cornerinfder;  // frb
    vp centrosup;     // fct
    vp centro;        // fc
    vp centroinf;     // fcb
    vp areasupizq;    // fplt
    vp areacentroizq; // fplc
    vp areainfizq;    // fplb
    vp areasupder;    // fprt
    vp areacentroder; // fprc
    vp areainfder;    // fprb
    vp portsupizq;    // fglt
    vp portcentroizq; // fglc
    vp portinfizq;    // fglb
    vp portsupder;    // fgrt
    vp portcentroder; // fgrc
    vp portinfder;    // fgrb
                      // banda exterior superior derecha e izquierda
    vp bandasup50ml;  // ftl50
    vp bandasup40ml;  // ftl40
    vp bandasup30ml;  // ftl30
    vp bandasup20ml;  // ftl20
    vp bandasup10ml;  // ftl10
    vp bandasup50mr;  // ftr50
    vp bandasup40mr;  // ftr40
    vp bandasup30mr;  // ftr30
    vp bandasup20mr;  // ftr20
    vp bandasup10mr;  // ftr10
    vp bandasup0m;    // ft
                      // banda exterior inferior derecha e izquierda
    vp bandainf50ml;  // fbl50
    vp bandainf40ml;  // ftl40
    vp bandainf30ml;  // ftl30
    vp bandainf20ml;  // ftl20
    vp bandainf10ml;  // ftl10
    vp bandainf50mr;  // ftr50
    vp bandainf40mr;  // ftr40
    vp bandainf30mr;  // ftr30
    vp bandainf20mr;  // ftr20
    vp bandainf10mr;  // ftr10
    vp bandainf0m;    // fb
                      // banda exterior derecha
    vp bandader30mt;  // frt30
    vp bandader20mt;  // frt20
    vp bandader10mt;  // frt10
    vp bandader30mb;  // frb30
    vp bandader20mb;  // truct visioncampo const &container,frb20
    vp bandader10mb;  // frb10
    vp bandader0m;    // fr0
                      // banda exterior izquierda
    vp bandaizq30mt;  // flt30
    vp bandaizq20mt;  // flt20
    vp bandaizq10mt;  // flt10
    vp bandaizq30mb;  // flb30
    vp bandaizq20mb;  // flb20
    vp bandaizq10mb;  // flb10
    vp bandaizq0m;    // fl0
};

/**
 * @brief CALCULA LAS COORDENADAS ABSOLUTAS DEL JUGADOR.
 *
 *
 * @param flagsmascercanas vector con dos pares, donde en cada par el PRIMER ELEMENTO es el indicativo del flag y el SEGUNDO ELEMENTO sus coordenadas VISTAS POR EL JUGADOR
 * @param coordenadasABS vector con TODOS LOS PARES (Donde van a estar los dos del primer parametro) de indicativo del flag y sus coordenadas ABSOLUTAS
 * @return Coordenadas absolutas del jugador
 */
pair<float, float> calcularCoordenadas(vector<pair<string, pair<float, float>>> flagsmascercanas, vector<pair<string, vp>> coordenadasABS);

/**
 * @brief CALCULA LOS CORTES DE DOS CIRCUNFERENCIAS DADO SUS CENTROS Y SUS RADIOS.
 *          En nuestro caso siempre deben cortarse o ser tangentes o da error. Solo aplicable al juego.
 *
 * @param a1,a2,R Corresponden a los parametros de la primera circunferencia
 * @param b1,b2,r Corresponden a los parametros de la segunda circunferencia
 * @return Coordenadas de los dos cortes, que pueden ser el mismo (tangentes)
 */
vector<pair<float, float>> corteCircunferencias(float a1, float a2, float R, float b1, float b2, float r);

/**
 * @brief CALCULA LOS PARES QUE CONTIENEN LOS DOS FLAGS VISTOS POR EL JUGADOR A MENOR DISTANCIA.
 *
 *
 * @param p Vector de pares donde el primer elemento es el indicativo y el segundo un par de distancia y angulo vistos por el jugador del flag
 * @return Vector de dos elementos de los dos flags mas cercanos
 */
vector<pair<string, pair<float, float>>> buscarMenores(vector<pair<string, vp>> p);

/**
 * @brief En cada iteracion del bucle hace uso de la informacion del servidor para almacenarla en un contenedor global.
 *
 *
 * @param p Palabra recibida por el servidor
 * @param container Estructura donde se almacenan los datos extraidos de la palabra.
 * @return devuelve las coordenadas absolutas del jugador
 */
pair<pair<float, float>, float> rellenaContenedor(visioncampo &container, const string &p);

/**
 * @brief Hace la congruencia de un algulo pasado en radianes.
 *
 *
 * @param angulo
 * @return angulo positivo <= 2pi
 */
float congruencia_2pi(double angulo);

/**
 * @brief CALCULA EL ANGULO ABSOLUTO CON EL QUE MIRA EL JUGADOR
 *
 *
 * @param flags Vector de dos elementos en el que la primera posicion es el indicativo del flag y el segundo la distancia y el angulo con el que lo ve el jugador
 * @param absolutas Referencia constante a la estructura donde tenemos las posiciones de los flags con sus indicativos
 * @return devuelve el angulo con el que mira el jugador
 */
float calcularAngulo(vector<pair<string, pair<float, float>>> const &flags, vector<pair<string, vp>> const &absolutas);

/**
 * @brief CALCULA EL ANGULO QUE DEBO GIRARME PARA MIRAR A UN FLAG EN CONCRETO
 *
 *
 * @param x, y, angulojugador coordenadas absolutas del jugador y su ángulo de vision
 * @param xgiro, ygiro coordenadas absolutas del sitio a donde quiero mirar
 * @return angulo que debo girarme en grados, POSITIVO HORARIO
 */
string calculoangulogiro(float x, float y, float xgiro, float ygiro, float angulojugador);

/**
 * @brief CALCULA LAS COORDENADAS ABSOLUTAS DE ALGO QUE ESTAS MIRANDO
 *
 *
 * @param coordenadasjugador coordenadas de mi jugador, primer elemento xy y segundo angulo de vision absoluto
 * @param objetivo coordenadas de lo que veo, distancia y angulo
 * @return coordenadas absolutas de lo que estoy viendo
 */
pair<float, float> calculoAbsoluto(pair<pair<float, float>, float> coordenadasjugador, pair<float, float> objetivo);