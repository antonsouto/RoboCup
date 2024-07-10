// tirar, correr y girar
#include "funciones_de_juego.h"
#include <iostream>
#include "colocarjugadores.h"
#include "Minimal-Socket/src/header/MinimalSocket/udp/UdpSocket.h"
#include <random>
#include <fstream>
#include "stringutilities.h"
#include <chrono>
#include <thread>
#include "calculocoordenadas.h"
#include "RetornoAZona.h"
#include <sstream>
#include <cmath>

using namespace std;
bool enJuego = false;
bool saquebanda = false;
bool saquecentro = false;
bool corner = false;
bool falta = false;
bool saquepuerta = false;

float xjugadorprev;
float yjugadorprev;
float angulojugadorprev;
// float xbalon;
// float ybalon;
visioncampo micontainer;

enum decision
{
    CHUPARLA,
    PASARLA,
    TIRAR,
    NADA,
    DRIBLAR,
};

void AlmacenarPosicionAngulo(pair<pair<float, float>, float> coordenadas) // Funcion para guardar la posicion anterior del jugador.
{
    if (coordenadas.first.first != 0 && coordenadas.first.second != 0)
    {
        angulojugadorprev = coordenadas.second;
        xjugadorprev = coordenadas.first.first;
        yjugadorprev = coordenadas.first.second;
    }
}

// string driblar(string received_message_content, pair<pair<float, float>, float> coordenadas, string numeroJugador, string ladoJugador, string team_name)
// {
//     return "(kick 20 120)";
// }
string tirar(string received_message_content, pair<pair<float, float>, float> coordenadas, string numeroJugador, string ladoJugador, string team_name)
{
    if (ladoJugador == "l") // tiramos hacia la porteria derecha
    {

        string angulogiro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, 50, 4, coordenadas.second); // sacamos el angulo para mirar a la porteria
        return "(kick 100 " + angulogiro + ")";
    }
    else // tiramos hacia la porteria izquierda
    {
        string angulogiro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, -50, -4, coordenadas.second); // sacamos el angulo para mirar a la porteria
        return "(kick 100 " + angulogiro + ")";
    }
    return "";
}
string chuparla(string received_message_content, pair<pair<float, float>, float> coordenadas, string numeroJugador, string ladoJugador, string team_name)
{
    pair<string, string> relativasBalon = buscarValores(received_message_content, "((b) ");                                        // relativas balon
    pair<float, float> baloncoordenadas = calculoAbsoluto(coordenadas, {stof(relativasBalon.first), stof(relativasBalon.second)}); // Coordenadas absolutas balon
    auto jugadoresVistos = parsePlayerInfo(received_message_content);
    bool paseaux1 = false;
    bool paseaux2 = false;
    for (auto jugador : jugadoresVistos)
    {
        if (jugador.teamName != team_name)
        {
            if (jugador.distance < 5)
            {
                paseaux1 = true;
            }
        }
        else
        {
            if (jugador.distance > 20 && jugador.playerNumber > stoi(numeroJugador))
            {
                paseaux2 = true;
            }
        }
    }

    float angulo = coordenadas.second;
    if (angulo > 180)
        angulo = angulo - 360;
    string resultado;
    if (ladoJugador == "l")
    {
        if (coordenadas.second < 200 && coordenadas.second >= 160)
        {
            return "(kick 20 120)";
        }
        if (paseaux1 == true)
        {
            return "(kick 20 60)";
        }
        string angulogiro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, 50, 0, coordenadas.second); // sacamos el angulo para mirar a la porteria
        return "(kick 20 " + angulogiro + ")";
    }
    else
    {
        if (coordenadas.second < 20 && coordenadas.second >= 340)
        {
            return "(kick 20 120)";
        }
        if (paseaux1 == true)
        {
            return "(kick 20 60)";
        }
        string angulogiro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, -50, 0, coordenadas.second); // sacamos el angulo para mirar a la porteria
        return "(kick 20 " + angulogiro + ")";
    }
    return "";
}
string pase(string received_message_content, pair<pair<float, float>, float> coordenadas, string numeroJugador, string ladoJugador, string team_name)
{
    float aux = 99999;
    pair<float, float> jugadormascercano;
    auto jugadoresVistos = parsePlayerInfo(received_message_content);
    string resultado;

    for (auto jugador : jugadoresVistos) // recorremos todos los jugadores a los que vemos
    {
        if (jugador.teamName == team_name) // para los jugadores de nuestro equipo
        {
            float distance = jugador.distance;
            if (jugador.distance > 20 && jugador.playerNumber > stoi(numeroJugador))
            {
                jugadormascercano = {jugador.distance, jugador.angle};
                float factorp = jugador.distance * 2.55;
                if (100 < factorp)
                    factorp = 100;
                return resultado = "(kick " + to_string(factorp) + " " + to_string(jugadormascercano.second) + ")";
            }
        }
    }
    return resultado;
}

decision decidir(string received_message_content, pair<pair<float, float>, float> coordenadas, string numeroJugador, string ladoJugador, string team_name)
{
    auto jugadoresVistos = parsePlayerInfo(received_message_content);
    bool resultado;

    // GESTIONAMOS DECISION DE TIRAR
    if (ladoJugador == "l" && coordenadas.first.first > 20)
        return TIRAR;
    if (ladoJugador == "r" && coordenadas.first.first < -20)
        return TIRAR;

    bool paseaux1 = false;
    bool paseaux2 = false;
    bool paseaux3 = false;

    // GESTIONAMOS DECISION DE PASAR
    for (auto jugador : jugadoresVistos)
    {
        if (jugador.teamName != team_name)
        {
            if (jugador.distance < 20)
            {
                paseaux1 = true;
            }
            if (jugador.distance < 7)
            {
                paseaux3 = true;
            }
        }
        else
        {
            if (jugador.distance > 20 && jugador.playerNumber > stoi(numeroJugador))
            {
                paseaux2 = true;
            }
        }
    }
    if (numeroJugador == "1")
    {
        if (paseaux2 == false)
            return TIRAR;
        else
            return PASARLA;
    }
    if (paseaux2 == true) // Si ve un jugador AMIGO lejos y numero MAYOR
        return PASARLA;
    // if (paseaux1 == true && paseaux2 == false)
    //     return DRIBLAR;
    // GESTIONAMOS LA DECISION DE CHUPARLA
    if ((numeroJugador == "3" || numeroJugador == "4" || numeroJugador == "5" || numeroJugador == "2") && paseaux3 == true)
        return TIRAR;
    if ((received_message_content.find("((p \"") == -1) || paseaux1 == true && paseaux2 == false || (paseaux1 == false && paseaux2 == false)) // Si no veo a nadie || veo no amigos
        return CHUPARLA;

    return NADA;
}

string ColocardeNuevo(string received_message_content, string ladoJugador, string numeroJugador)
{
    string mensaje;

    if (numeroJugador == "1")
    { //(init l 1 before_kick_off)
        mensaje = "(move -51 0)";
    }
    else if (numeroJugador == "2")
        mensaje = "(move -35 -14)";
    else if (numeroJugador == "3")
        mensaje = "(move -36 -3)";
    else if (numeroJugador == "4")
        mensaje = "(move -36 3)";
    else if (numeroJugador == "5")
        mensaje = "(move -35 14)";
    else if (numeroJugador == "6")
        mensaje = "(move -25 9)";
    else if (numeroJugador == "10")
        mensaje = "(move -8 20)";
    else if (numeroJugador == "8")
        mensaje = "(move -25 -9)";
    else if (numeroJugador == "9")
        mensaje = "(move -0.5 0)";
    else if (numeroJugador == "7")
        mensaje = "(move -15 0)";
    else if (numeroJugador == "11")
        mensaje = "(move -8 -20)";
    return mensaje;
}

bool Escuchar(string received_message_content, string ladoJugador, string numero)
{

    if ((received_message_content.find("play_on") != -1) || (received_message_content.find("kick_off") != -1))
    {
        if ((received_message_content.find("kick_off_l") != -1) && (ladoJugador == "l") && (stoi(numero) == 9))
        {
            saquecentro = true;
        }
        else if ((received_message_content.find("kick_off_r") != -1) && (ladoJugador == "r" && (stoi(numero) == 9)))
        {
            saquecentro = true;
        }
        enJuego = true;
        saquebanda = false;
        corner = false;
        falta = false;
        saquepuerta = false;
    }
    else if (received_message_content.find("goal_l") != -1 || received_message_content.find("goal_r") != -1 || received_message_content.find("before_kick_off") != -1 || received_message_content.find("half_time") != -1 || received_message_content.find("time_over") != -1 || received_message_content.find("foul_charge") != -1 || received_message_content.find("foul_push") != -1 || received_message_content.find("foul_multiple") != -1 || received_message_content.find("foul_ballout") != -1 || received_message_content.find("goalie_catch_ball") != -1 || received_message_content.find("back_pass") != -1 || received_message_content.find("illegal_defense") != -1)
    {
        saquecentro = false;
        enJuego = false;
        saquebanda = false;
        corner = false;
        falta = false;
        saquepuerta = false;
    }
    else if ((received_message_content.find("kick_in") != -1))
    {
        if ((received_message_content.find("kick_in_l") != -1) && (ladoJugador == "l"))
        {
            saquebanda = true;
        }
        else if ((received_message_content.find("kick_in_r") != -1) && (ladoJugador == "r"))
        {
            saquebanda = true;
        }
        saquecentro = false;
        enJuego = false;
        corner = false;
        falta = false;
        saquepuerta = false;
    }
    else if (received_message_content.find("corner_kick") != -1)
    {
        if ((received_message_content.find("corner_kick_l") != -1) && (ladoJugador == "l"))
        {
            corner = true;
        }
        else if ((received_message_content.find("corner_kick_r") != -1) && (ladoJugador == "r"))
        {
            corner = true;
        }
        saquecentro = false;
        enJuego = false;
        saquebanda = false;
        falta = false;
        saquepuerta = false;
    }
    else if (received_message_content.find("free_kick") != -1 || received_message_content.find("indirect_free_kick") != -1)
    {
        if ((received_message_content.find("free_kick_l") != -1) && (ladoJugador == "l") || (received_message_content.find("indirect_free_kick_l") != -1) && (ladoJugador == "l"))
        {
            falta = true;
        }
        else if ((received_message_content.find("free_kick_r") != -1) && (ladoJugador == "r") || (received_message_content.find("indirect_free_kick_r") != -1) && (ladoJugador == "r"))
        {
            falta = true;
        }
        saquecentro = false;
        enJuego = false;
        saquebanda = false;
        corner = false;
        saquepuerta = false;
    }
    else if (received_message_content.find("goal_kick") != -1)
    {
        if ((received_message_content.find("goal_kick_l") != -1) && (ladoJugador == "l") && (stoi(numero) == 1))
        {
            saquepuerta = true;
        }
        else if ((received_message_content.find("goal_kick_r") != -1) && (ladoJugador == "r") && (stoi(numero) == 1))
        {
            saquepuerta = true;
        }
        saquecentro = false;
        enJuego = false;
        saquebanda = false;
        corner = false;
        falta = false;
    }
    return enJuego;
}

string Ver(string received_message_content, string ladoJugador, string numerojugador, string team_name)
{

    string resultado;
    pair<pair<float, float>, float> coordenadas = rellenaContenedor(micontainer, received_message_content);
    if (received_message_content.find("(b) ") != -1)
    {
        auto balon = buscarValores(received_message_content, "((b) ");
        auto xybalon = calculoAbsoluto(coordenadas, {stof(balon.first), stof(balon.second)});
    }
    if (enJuego)
    {
        if (saquecentro)
        {
            saquecentro = false;
            if (ladoJugador == "l")
            {
                string paseinicial = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, -15, 0, coordenadas.second);
                return "(kick 50 " + paseinicial + ")";
            }
            else
            {
                string paseinicial = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, 15, 0, coordenadas.second);
                return "(kick 50 " + paseinicial + ")";
            }
        }
        if (received_message_content.find("(b) ") != -1)
        {

            auto balon = buscarValores(received_message_content, "((b) ");
            // Aquí se procesan los valores de "(b)" en "balon"
            if (abs(stof(balon.second)) > 15 && numerojugador != "1") //// !!!!!!!!!CAMBIO
                return "(turn " + balon.second + ")";                 // si vemos el balon lo enfocamos
            if (stoi(balon.first) >= 2 && stoi(balon.first) < 15 && numerojugador == "1")
            {

                if (ladoJugador == "l")
                {
                    if (-36 < coordenadas.first.first)
                    {
                        return resultado = retornoazona(numerojugador, ladoJugador, coordenadas);
                    }
                }
                if (ladoJugador == "r")
                    if (36 > coordenadas.first.first)
                    {
                        return resultado = retornoazona(numerojugador, ladoJugador, coordenadas);
                    }
                return resultado = "(dash 100 " + balon.second + ")";
            }
            else if (stoi(balon.first) >= 0.6 && stoi(balon.first) < 8)
            {

                return resultado = "(dash 100 " + balon.second + ")";
            }
            if (numerojugador == "1" && stoi(balon.first) < 2)
            {
                if (abs(coordenadas.first.first) < 39)
                {
                    return tirar(received_message_content, coordenadas, numerojugador, ladoJugador, team_name);
                }
                return "(catch " + balon.second + ")";
            }
            else if (stoi(balon.first) < 0.6)
            {
                auto decisionconbalon = decidir(received_message_content, coordenadas, numerojugador, ladoJugador, team_name);

                switch (decisionconbalon)
                {
                case TIRAR:
                    // return tirar(received_message_content, coordenadas, numerojugador, ladoJugador, team_name);
                    return tirar(received_message_content, coordenadas, numerojugador, ladoJugador, team_name);
                    break;
                case CHUPARLA:
                    // return chuparla(received_message_content, coordenadas, numerojugador, ladoJugador, team_name);
                    return chuparla(received_message_content, coordenadas, numerojugador, ladoJugador, team_name);
                    break;
                case PASARLA:
                    return pase(received_message_content, coordenadas, numerojugador, ladoJugador, team_name);
                    break;
                case NADA:

                    break;
                default:

                    break;
                }
            }
            else if (zonaJuego(numerojugador, ladoJugador, coordenadas.first)) // Cuando ve la pelota y esta lejos
            {
                if (numerojugador == "1") // 5 = dist que me da igual la zona
                {
                    auto xybalon = calculoAbsoluto(coordenadas, {stof(balon.first), stof(balon.second)});
                    auto diferencia_y = xybalon.second - coordenadas.first.second;
                    cout << balon.second << endl;

                    if (abs(stoi(balon.second)) >= 20)
                    {
                        return resultado = "(turn " + balon.second + ")";
                    }
                    // Si la y del portero es diferente al balon
                    else if (xybalon.second != coordenadas.first.second)
                    {
                        float y;
                        float yactual = xybalon.second;
                        if (7 < xybalon.second) // la y del balon es mayor a la y del borde superior del area chica
                        {
                            y = 7; // el portero solo va a subir hasta el borde superior del area chica
                        }
                        else if (-7 > xybalon.second) // igual pero con el inferior
                        {
                            y = -7;
                        }
                        else
                        {
                            y = yactual; // en caso de que la y del balon este dentro de lo que es el area chica
                        }

                        // se mira el lado del que es y se cambia la x a la que tienen que ir
                        if (ladoJugador == "l")
                        {
                            auto giro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, -48, y, coordenadas.second);
                            return resultado = "(dash 100 " + giro + ")";
                        }
                        else
                        {
                            auto giro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, 48, y, coordenadas.second);
                            return resultado = "(dash 100 " + giro + ")";
                        }
                    }
                    return resultado;
                }
                else if (stoi(balon.first) > 70)
                    return resultado = "(turn " + balon.second + ")";
                else if (stoi(balon.first) > 60)
                    return resultado = "(dash 5 " + balon.second + ")";
                else if (stoi(balon.first) > 30)
                    return resultado = "(dash 20 " + balon.second + ")";
                else if (stoi(balon.first) > 20)
                    return resultado = "(dash 80 " + balon.second + ")";
                else
                    return resultado = "(dash 100 " + balon.second + ")";
            }
            else if (!zonaJuego(numerojugador, ladoJugador, coordenadas.first)) // cuando no esta dentro de la zona
            {

                return resultado = retornoazona(numerojugador, ladoJugador, coordenadas);
            }

            // Aquí puedes realizar otras operaciones con los valores extraídos
        }
        else if (received_message_content.find("(b) ") == -1) // Cuando no ve el balon
        {
            if (numerojugador == "1")
                return resultado = "(turn 90)";
            return resultado = "(turn 60)";
        }
        return resultado;
    }
    if (saquebanda)
    {
        if (received_message_content.find("(b) ") == -1)
        {
            return resultado = "(turn 80)";
        }
        else
        {
            auto balon = buscarValores(received_message_content, "((b) ");
            auto xybalon = calculoAbsoluto(coordenadas, {stof(balon.first), stof(balon.second)});
            float aux = 99999;
            pair<float, float> jugadormascercano;
            auto jugadoresVistos = parsePlayerInfo(received_message_content);
            for (auto jugador : jugadoresVistos)
            {
                if (jugador.teamName == team_name)
                {
                    // distancia angulo a la que veo el jugador
                    auto jugadoraux = calculoAbsoluto(coordenadas, {jugador.distance, jugador.angle});
                    // distancia a la que esta el jugador del balon
                    float distance = sqrt((xybalon.first - jugadoraux.first) * (xybalon.first - jugadoraux.first) + (xybalon.second - jugadoraux.second) * (xybalon.second - jugadoraux.second));
                    if (distance < aux)
                    {
                        aux = distance;                                        // distancia del jugador visto hasta el balon
                        jugadormascercano = {jugador.distance, jugador.angle}; // distancia a la que ves el jugador mas cercano y su angulo
                    }
                }
            }
            if (abs(stof(balon.first)) < 1)
            {
                return resultado = "(kick 90 180)";
            }
            else if (stof(balon.first) > aux)
            {
                return resultado = "(dash 0 0)";
            }
            else if (received_message_content.find("((b)") == -1)
            {
                return "(turn 45)";
            }
            else if (stof(balon.first) < aux)
            {
                return resultado = "(dash 100 " + balon.second + ")";
            }
        }
        return "(turn 45)";
    }
    if (corner)
    {

        auto balon = buscarValores(received_message_content, "((b) ");
        auto xybalon = calculoAbsoluto(coordenadas, {stof(balon.first), stof(balon.second)});
        float aux = 99999;
        pair<float, float> jugadormascercano;
        auto jugadoresVistos = parsePlayerInfo(received_message_content);

        if (abs(stof(balon.second)) > 5)
            return "(turn " + balon.second + ")"; // si vemos el balon lo enfocamos
        for (auto jugador : jugadoresVistos)
        {
            if (jugador.teamName == team_name)
            {
                auto jugadoraux = calculoAbsoluto(coordenadas, {jugador.distance, jugador.angle});
                float distance = sqrt((xybalon.first - jugadoraux.first) * (xybalon.first - jugadoraux.first) + (xybalon.second - jugadoraux.second) * (xybalon.second - jugadoraux.second));
                if (distance < aux)
                {
                    aux = distance;                                        // distancia del jugador visto hasta el balon
                    jugadormascercano = {jugador.distance, jugador.angle}; // distancia a la que ves el jugador mas cercano y su angulo
                }
            }
        }
        if (abs(stof(balon.first)) < 1)
        {
            if (ladoJugador == "l")
            {
                string angulocorner = calculoangulogiro(xjugadorprev, yjugadorprev, 20, 0, angulojugadorprev);
                return "(kick 90 " + angulocorner + ")";
            }
            else if (ladoJugador == "r")
            {
                string angulocorner = calculoangulogiro(xjugadorprev, yjugadorprev, -20, 0, angulojugadorprev);
                return "(kick 90 " + angulocorner + ")";
            }
        }
        else if (stof(balon.first) > aux)
        {
            return resultado = "(dash 0 0)";
        }
        else if (received_message_content.find("((b)") == -1)
        {
            return "(turn 45)";
        }
        else if (stof(balon.first) < aux)
        {
            AlmacenarPosicionAngulo(coordenadas);
            return resultado = "(dash 100 " + balon.second + ")";
        }
        return "(turn 45)";
    }
    if (falta)
    {
        auto balon = buscarValores(received_message_content, "((b) ");
        auto xybalon = calculoAbsoluto(coordenadas, {stof(balon.first), stof(balon.second)});
        float aux = 99999;
        pair<float, float> jugadormascercano;
        auto jugadoresVistos = parsePlayerInfo(received_message_content);

        if (abs(stof(balon.second)) > 5)
            return "(turn " + balon.second + ")"; // si vemos el balon lo enfocamos
        for (auto jugador : jugadoresVistos)
        {
            if (jugador.teamName == team_name)
            {
                auto jugadoraux = calculoAbsoluto(coordenadas, {jugador.distance, jugador.angle});
                float distance = sqrt((xybalon.first - jugadoraux.first) * (xybalon.first - jugadoraux.first) + (xybalon.second - jugadoraux.second) * (xybalon.second - jugadoraux.second));
                if (distance < aux)
                {
                    aux = distance;                                        // distancia del jugador visto hasta el balon
                    jugadormascercano = {jugador.distance, jugador.angle}; // distancia a la que ves el jugador mas cercano y su angulo
                }
            }
        }
        if (abs(stof(balon.first)) < 1)
        {
            return tirar(received_message_content, coordenadas, numerojugador, ladoJugador, team_name);
        }
        else if (received_message_content.find("((b)") == -1)
        {
            return "(turn 45)";
        }
        else if (stof(balon.first) > aux)
        {
            return resultado = "(dash 0 0)";
        }
        else if (stof(balon.first) < aux)
        {
            AlmacenarPosicionAngulo(coordenadas);
            return resultado = "(dash 100 " + balon.second + ")";
        }
    }
    if (saquepuerta)
    {
        auto balon = buscarValores(received_message_content, "((b) ");
        if (abs(stof(balon.second)) > 5)
            return "(turn " + balon.second + ")"; // si vemos el balon lo enfocamos
        if (abs(stof(balon.first)) < 1)
        {
            if (received_message_content.find("((p \"" + team_name + "\"") != -1)
            {
                return pase(received_message_content, coordenadas, numerojugador, ladoJugador, team_name);
            }
            else
            {
                return tirar(received_message_content, coordenadas, numerojugador, ladoJugador, team_name);
            }
        }
        else if (received_message_content.find("((b)") == -1)
        {
            return "(turn 45)";
        }
        else if (stof(balon.first) >= 1)
        {
            return resultado = "(dash 100 " + balon.second + ")";
        }
    }
    return resultado;
}

string procesado(string received_message_content, string ladoJugador, string numero, string team_name)
{
    string prefix = "(hear";
    string prefix2 = "(see";
    string resultado;
    // Verificar si la cadena comienza con el prefijo
    if (received_message_content.compare(0, prefix.size(), prefix) == 0)
    {

        enJuego = Escuchar(received_message_content, ladoJugador, numero);
        if ((received_message_content.find("goal") != -1) || (received_message_content.find("half_time") != -1))
        {
            resultado = ColocardeNuevo(received_message_content, ladoJugador, numero);
        }
    }
    if (received_message_content.compare(0, prefix2.size(), prefix2) == 0)
    {
        return resultado = Ver(received_message_content, ladoJugador, numero, team_name);
    }
    return resultado;
}