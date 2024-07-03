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
float xbalon;
float ybalon;
visioncampo micontainer;

struct PlayerInfo
{
    std::string teamName;
    int playerNumber;
    float distance;
    float angle;
};

std::vector<PlayerInfo> parsePlayerInfo(const std::string &input)
{
    std::vector<PlayerInfo> players;
    std::string::size_type start = 0;

    while ((start = input.find("((p \"", start)) != std::string::npos)
    {
        start += 5; // Move past "((p \""
        std::string::size_type endQuote = input.find("\"", start);
        std::string teamName = input.substr(start, endQuote - start);

        // Move past the closing quote
        start = endQuote + 1;

        int playerNumber = -1;
        if (input[start] == ' ')
        {
            ++start; // Move past the space
            if (isdigit(input[start]))
            {
                std::string::size_type endNum = input.find(")", start);
                std::string numStr = input.substr(start, endNum - start);
                playerNumber = std::stoi(numStr);
                start = endNum; // Move past the number
            }
        }

        // Move to the data part
        start = input.find(") ", start) + 2; // Move past ") "
        std::string::size_type dataEnd = input.find(' ', start);
        float distance = std::stof(input.substr(start, dataEnd - start));

        start = dataEnd + 1;
        dataEnd = input.find(' ', start);
        float angle = std::stof(input.substr(start, dataEnd - start));

        PlayerInfo player = {teamName, playerNumber, distance, angle};
        players.push_back(player);

        // Move past the current player data to continue the search
        start = dataEnd;
    }

    return players;
}

string ColocardeNuevo(string received_message_content, string ladoJugador, string numeroJugador)
{
    string mensaje;
    ostringstream xbalon2;
    xbalon2 << xbalon;
    string x(xbalon2.str());
    ostringstream ybalon2;
    ybalon2 << ybalon;
    string y(ybalon2.str());
    if (numeroJugador == "1")
    { //(init l 1 before_kick_off)
        mensaje = "(move -51 0)";
    }
    else if (numeroJugador == "2")
        mensaje = "(move -35 -28)";
    else if (numeroJugador == "3")
        mensaje = "(move -42 -14)";
    else if (numeroJugador == "4")
        mensaje = "(move -42 14)";
    else if (numeroJugador == "5")
        mensaje = "(move -35 28)";
    else if (numeroJugador == "6")
        mensaje = "(move -25 11)";
    else if (numeroJugador == "7")
        mensaje = "(move -8 20)";
    else if (numeroJugador == "8")
        mensaje = "(move -25 -11)";
    else if (numeroJugador == "9")
        mensaje = "(move -5 0)";
    else if (numeroJugador == "10")
        mensaje = "(move -15 0)";
    else if (numeroJugador == "11")
        mensaje = "(move -8 -20)";
    return mensaje;
}

pair<float, float> calculoAbsoluto(pair<pair<float, float>, float> coordenadasjugador, pair<float, float> objetivo)
{
    float anguloobjetivo = -coordenadasjugador.second + objetivo.second;
    anguloobjetivo = anguloobjetivo * M_PI / 180;
    xbalon = objetivo.first * cos(anguloobjetivo) + coordenadasjugador.first.first;
    ybalon = objetivo.first * sin(anguloobjetivo) + coordenadasjugador.first.second;
    return {xbalon, ybalon};
}

bool Escuchar(string received_message_content, string ladoJugador)
{

    if ((received_message_content.find("play_on") != -1) || (received_message_content.find("kick_off") != -1))
    {
        return enJuego = true;
        saquebanda = false;
    }
    else if (received_message_content.find("goal") != -1 || received_message_content.find("before_kick_off") != -1)
    {
        return enJuego = false;
        saquebanda = false;
    }
    else if ((received_message_content.find("kick_in") != -1))
    {
        enJuego = false;
        saquebanda = true;
    }
    return enJuego;
}

string Ver(string received_message_content, string ladoJugador, string numerojugador, string team_name)
{

    string resultado;
    pair<pair<float, float>, float> coordenadas = rellenaContenedor(micontainer, received_message_content);
    // cout << "\n\t Mis coordenadas en este momento son : " << coordenadas.first.first << " " << coordenadas.first.second << " mirando con un angulo absoluto : " << coordenadas.second << endl;
    if (received_message_content.find("(b) ") != -1)
    {
        auto balon = buscarValores(received_message_content, "((b) ");
        auto xybalon = calculoAbsoluto(coordenadas, {stof(balon.first), stof(balon.second)});
        cout << xybalon.first << " " << xybalon.second << endl;
    }
    if (enJuego)
    {
        if (received_message_content.find("(b) ") != -1)
        {
            auto balon = buscarValores(received_message_content, "((b) ");
            // Aquí se procesan los valores de "(b)" en "balon"
            // std::cout << "Valor 1: " << par.first << ", Valor 2: " << par.second << std::endl;

            if (stoi(balon.first) >= 0.6 && stoi(balon.first) < 5)
            {
                return resultado = "(dash 100 " + balon.second + ")";
            }
            if (stoi(balon.first) < 0.6)
            {
                if (ladoJugador == "l")
                { // Ve el balon y la porteria de la dcha
                    if (received_message_content.find("(g r) ") != -1)
                    {
                        auto porteria = buscarValores(received_message_content, "((g r) ");
                        return resultado = "(kick 100 " + porteria.second + ")";

                    } // Ve el balon y el centro del campo
                    else if ((received_message_content.find("(f c) ") != -1))
                    {
                        if (coordenadas.first.first < 0)
                        { // solo dispara al centro si esta en el lado izquierdo del campo
                            auto centro = buscarValores(received_message_content, "((f c) ");
                            return resultado = "(kick 100 " + centro.second + ")";
                        }

                    } ////Ve el balon pero no ve ni la porteria de la dcha ni el centro del campo
                    else if ((received_message_content.find("(f c) ") == -1) && (received_message_content.find("(g r) ") == -1))
                    {
                        return resultado = "(dash 100 30)";
                    }
                }
                else
                {
                    if (received_message_content.find("(g l) ") != -1)
                    { // Ve el balon y la porteria de la izq
                        auto porteria = buscarValores(received_message_content, "((g l) ");
                        return resultado = "(kick 100 " + porteria.second + ")";

                    } // Ve el balon y el centro del campo
                    else if ((received_message_content.find("(f c) ") != -1))
                    {
                        if (coordenadas.first.second > 0)
                        { // solo dispara al centro si esta en el lado derecho del campo
                            auto centro = buscarValores(received_message_content, "((f c) ");
                            return resultado = "(kick 100 " + centro.second + ")";
                        }

                    } // Ve el balon pero no ve ni la porteria de la izq ni el centro del campo
                    else if ((received_message_content.find("(f c) ") == -1) && (received_message_content.find("(g l) ") == -1))
                    {
                        return resultado = "(dash 100 30)";
                    }
                }
                return resultado = "(dash 100 " + balon.second + ")";
            }
            else if (zonaJuego(numerojugador, ladoJugador, coordenadas.first)) // Cuando ve la pelota y esta lejos
            {

                if (stoi(balon.first) > 70)
                    return resultado = "(turn " + balon.second + ")";
                else if (stoi(balon.first) > 60)
                    return resultado = "(dash 10 " + balon.second + ")";
                else if (stoi(balon.first) > 30)
                    return resultado = "(dash 30 " + balon.second + ")";
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
            return resultado = "(turn 80)";
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
                    auto jugadoraux = calculoAbsoluto(coordenadas, {jugador.distance, jugador.angle});
                    float distance = sqrt((xybalon.first - jugadoraux.first) * (xybalon.first - jugadoraux.first) + (xybalon.second - jugadoraux.second) * (xybalon.second - jugadoraux.second));
                    if (distance < aux)
                    {
                        aux = distance;
                        jugadormascercano = {jugador.distance, jugador.angle};
                    }
                }
            }
            if (stof(balon.first) < 0.6)
            {
                if (received_message_content.find("((p)) ") == -1)
                {
                    return resultado = "(dash 100 30)";
                }
                else
                {
                    float potencia = jugadormascercano.first;
                    ostringstream angulojugador;
                    angulojugador << jugadormascercano.second;
                    string angulo(angulojugador.str());
                    return resultado = "(kick 30 " + angulo + ")";
                }
            }
            else if (stof(balon.first) > aux)
            {
                return resultado = "(dash 0 0)";
            }
            else if (stof(balon.first) < aux)
            {
                return resultado = "(dash 100 " + balon.second + ")";
            }
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
        enJuego = Escuchar(received_message_content, ladoJugador);
        if (received_message_content.find("goal") != -1)
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