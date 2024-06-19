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

using namespace std;
bool enJuego = false;

bool Escuchar(string received_message_content, string ladoJugador)
{
    if ((received_message_content.find("play_on") != -1) || (received_message_content.find("kick_off_l") != -1))
    {
        return enJuego = true;
    }
    else
        return false;
}

string Ver(string received_message_content, string ladoJugador)
{

    string resultado;

    if (received_message_content.find("(b)") != -1)
    {
        auto balon = buscarValores(received_message_content, "((b)");
        // Aquí se procesan los valores de "(b)" en "balon"
        for (const auto &par : balon)
        {
            std::cout << "Valor 1: " << par.first << ", Valor 2: " << par.second << std::endl;
            if (stoi(par.first) < 0.6)
            {

                if (ladoJugador == "l")
                { // Ve el balon y la porteria de la dcha
                    if (received_message_content.find("(g r)") != -1)
                    {
                        auto porteria = buscarValores(received_message_content, "((g r)");
                        for (const auto &lugar : porteria)
                        {
                            return resultado = "(kick 100 " + lugar.second + ")";
                        }
                    } // Ve el balon y el centro del campo
                    else if ((received_message_content.find("(f c)") != -1))
                    {
                        auto centro = buscarValores(received_message_content, "((f c)");
                        for (const auto &lugar : centro)
                        {
                            return resultado = "(kick 100 " + lugar.second + ")";
                        }
                    } ////Ve el balon pero no ve ni la porteria de la dcha ni el centro del campo
                    else if ((received_message_content.find("(f c)") == -1) && (received_message_content.find("(g r)") == -1))
                    {
                        return resultado = "(dash 100 30)";
                    }
                }
                else
                {
                    if (received_message_content.find("(g l)") != -1)
                    { // Ve el balon y la porteria de la izq
                        auto porteria = buscarValores(received_message_content, "((g l)");
                        for (const auto &lugar : porteria)
                        {
                            return resultado = "(kick 100 " + lugar.second + ")";
                        }
                    } // Ve el balon y el centro del campo
                    else if ((received_message_content.find("(f c)") != -1))
                    {
                        auto centro = buscarValores(received_message_content, "((f c)");
                        for (const auto &lugar : centro)
                        {
                            return resultado = "(kick 100 " + lugar.second + ")";
                        }
                    } // Ve el balon pero no ve ni la porteria de la izq ni el centro del campo
                    else if ((received_message_content.find("(f c)") == -1) && (received_message_content.find("(g l)") == -1))
                    {
                        return resultado = "(dash 100 30)";
                    }
                }
            }
            else // Cuando ve la pelota y esta lejos
            {
                return resultado = "(dash 100 " + par.second + ")";
            }
            // Aquí puedes realizar otras operaciones con los valores extraídos
        }
    }
    else if (received_message_content.find("(b)") == -1) // Cuando no ve el balon
    {
        return resultado = "(turn 80)";
    }
    return resultado;
}

string procesado(string received_message_content, string ladoJugador)
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
        return resultado = Ver(received_message_content, ladoJugador);
    }
    return resultado;
}