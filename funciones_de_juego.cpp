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

using namespace std;
bool enJuego = false;
visioncampo micontainer;

bool Escuchar(string received_message_content, string ladoJugador)
{
    if ((received_message_content.find("play_on") != -1) || (received_message_content.find("kick_off_l") != -1))
    {
        return enJuego = true;
    }
    else
        return false;
}

string Ver(string received_message_content, string ladoJugador, string numerojugador)
{

    string resultado;
    pair<pair<float, float>, float> coordenadas = rellenaContenedor(micontainer, received_message_content);
    cout << "\n\t Mis coordenadas en este momento son : " << coordenadas.first.first << " " << coordenadas.first.second << " mirando con un angulo absoluto : " << coordenadas.second << endl;
    if (received_message_content.find("(b) ") != -1)
    {
        auto balon = buscarValores(received_message_content, "((b) ");
        // Aquí se procesan los valores de "(b)" en "balon"
        // std::cout << "Valor 1: " << par.first << ", Valor 2: " << par.second << std::endl;
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
            {
                return resultado = "(turn " + balon.second + ")";
            }
            else if (stoi(balon.first) > 60)
            {
                return resultado = "(dash 20 " + balon.second + ")";
            }
            else if (stoi(balon.first) > 30)
            {
                return resultado = "(dash 50 " + balon.second + ")";
            }
            else if (stoi(balon.first) > 20)
            {
                return resultado = "(dash 80 " + balon.second + ")";
            }
            else
            {
                return resultado = "(dash 100 " + balon.second + ")";
            }
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

string procesado(string received_message_content, string ladoJugador, string numero)
{
    std::string prefix = "(hear";
    std::string prefix2 = "(see";
    string resultado;
    // Verificar si la cadena comienza con el prefijo
    if (received_message_content.compare(0, prefix.size(), prefix) == 0)
    {
        bool enJuego = Escuchar(received_message_content, ladoJugador);
    }
    if (received_message_content.compare(0, prefix2.size(), prefix2) == 0 && enJuego)
    {
        return resultado = Ver(received_message_content, ladoJugador, numero);
    }
    return resultado;
}