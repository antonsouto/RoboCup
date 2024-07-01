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

pair<float, float> calcularCoordenadas(vector<pair<string, pair<float, float>>> flagsmascercanas, vector<pair<string, vp>> coordenadasABS);

vector<pair<float, float>> corteCircunferencias(float a1, float a2, float R, float b1, float b2, float r);

// vector<string> separarPalabras(const string &palabra);

vector<pair<string, pair<float, float>>> buscarMenores(vector<pair<string, vp>> p);

// pair<string, string> buscarValores(const std::string &input, const std::string &inicio);

pair<pair<float, float>, float> rellenaContenedor(visioncampo &container, const string &p);

// Devuelve la congruencia de un ángulo
float congruencia_2pi(double angulo);

// Devuelve el angulo a partir de las coordenadas del jugador y las de un flag, junto con el ángulo que forma la mirada del jugador con el flag
float calcularAngulo(vector<pair<string, pair<float, float>>> const &flags, vector<pair<string, vp>> const &absolutas);

// Devuel el angulo entre la direccion de vista del jugador y un punto del campo indicado
string calculoangulogiro(float x, float y, float xgiro, float ygiro, float angulojugador);