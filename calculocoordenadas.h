#pragma once

#include <functional>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <cmath>
#include "stringutilities.h"
using namespace std;
typedef pair<string, string> vp;

//--------------------------------------------------------------------------------VECTOR DE COORDENADAS ABSOLUTAS DEL CAMPO
vector<pair<string, vp>> coordenadasABS = {
    // {"cornersupizq", {"-52.5","-34"}},
    // {"cornersupder", {"52.5","-34"}},
    // {"cornerinfizq", {"-52.5","34"}},
    // {"cornerinfder", {"52.5","34"}},
    // {"centrosup", {"0","-34"}},
    // {"centro", {"0","0"}},
    // {"centroinf", {"0","34"}},
    // {"areasupizq", {"-36","-20"}},
    // {"areacentroizq", {"-36","0"}},
    // {"areainfizq", {"-36","20"}},
    // {"areasupder", {"36","-20"}},
    // {"areacentroder", {"36","0"}},
    // {"areainfder", {"36","20"}},
    // {"portsupder", {"52.5","-7"}},
    // {"portcentroder",{"52.5","0"}},
    // {"portinfder", {"52.5","7"}},
    // {"portsupizq", {"-52.5","-7"}},
    // {"portcentroizq", {"-52.5","0"}},
    // {"portinfizq", {"-52.5","7"}},
    // banda superior
    {"((f t l 50) ", {"-50", "-39"}},
    {"((f t l 40) ", {"-40", "-39"}},
    {"((f t l 30) ", {"-30", "-39"}},
    {"((f t l 20) ", {"-20", "-39"}},
    {"((f t l 10) ", {"-10", "-39"}},
    {"((f t) ", {"0", "-39"}},
    {"((f t r 50) ", {"50", "-39"}},
    {"((f t r 40) ", {"40", "-39"}},
    {"((f t r 30) ", {"30", "-39"}},
    {"((f t r 20) ", {"20", "-39"}},
    {"((f t r 10) ", {"10", "-39"}},
    // banda inferior
    {"((f b l 50) ", {"-50", "39"}},
    {"((f b l 40) ", {"-40", "39"}},
    {"((f b l 30) ", {"-30", "39"}},
    {"((f b l 20) ", {"-20", "39"}},
    {"((f b l 10) ", {"-10", "39"}},
    {"((f b) ", {"0", "39"}},
    {"((f b r 50) ", {"50", "39"}},
    {"((f b r 40) ", {"40", "39"}},
    {"((f b r 30) ", {"30", "39"}},
    {"((f b r 20) ", {"20", "39"}},
    {"((f b r 10) ", {"10", "39"}},
    // banda derecha
    {"((f r b 30) ", {"57.5", "30"}},
    {"((f r b 20) ", {"57.5", "20"}},
    {"((f r b 10) ", {"57.5", "10"}},
    {"((f r 0) ", {"57.5", "0"}},
    {"((f r t 30) ", {"57.5", "-30"}},
    {"((f r t 20) ", {"57.5", "-20"}},
    {"((f r t 10) ", {"57.5", "-10"}},
    // banda izquierda
    {"((f l b 30) ", {"-57.5", "30"}},
    {"((f l b 20) ", {"-57.5", "20"}},
    {"((f l b 10) ", {"-57.5", "10"}},
    {"((f l 0) ", {"-57.5", "0"}},
    {"((f l t 30) ", {"-57.5", "-30"}},
    {"((f l t 20) ", {"-57.5", "-20"}},
    {"((f l t 10) ", {"-57.5", "-10"}},

};

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

pair<float, float> rellenaContenedor(visioncampo &container, const string &p);
