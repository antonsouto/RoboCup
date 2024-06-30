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
            if (numerojugador == "1" && ladoJugador == "l")
            {
                auto giro = calculoangulogiro(coordenadas.first.first, coordenadas.first.second, -50, 0, coordenadas.second);
                return resultado = "(dash 100 " + giro + ")";
            }
            else if (numerojugador == "2" || numerojugador == "5")
            {
                return resultado = "(dash 80 180)";
            }
            else if (numerojugador == "3" || numerojugador == "4")
            {
                return resultado = "(dash 80 180)";
            }
            else if ((numerojugador == "6" || numerojugador == "8"))
            {
                return resultado = "(dash 80 180)";
            }
            else if ((numerojugador == "7" || numerojugador == "11") && (ladoJugador == "l"))
            {
                return resultado = "(dash 80 180)";
            }
            else if ((numerojugador == "7" || numerojugador == "11") && (ladoJugador == "r"))
            {
                return resultado = "(dash 80 180)";
            }
            else if ((numerojugador == "10") && (ladoJugador == "l"))
            {
                return resultado = "(dash 80 180)";
            }
            else if ((numerojugador == "10") && (ladoJugador == "r"))
            {
                return resultado = "(dash 80 180)";
            }
            else if ((numerojugador == "9") && (ladoJugador == "l"))
            {
                return resultado = "(dash 80 180)";
            }
            else if ((numerojugador == "9") && (ladoJugador == "r"))
            {
                return resultado = "(dash 80 180)";
            }
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

bool zonaJuego(string numerojugador, string lado, pair<float, float> coordenadas)
{
    float x = abs(coordenadas.first);
    float y = abs(coordenadas.second);

    if (numerojugador == "1")
    {
        return ((37 <= x && x <= 52) && (y < 19));
    }
    else if (numerojugador == "2" || numerojugador == "5")
    {
        return ((25 <= y && y <= 33));
    }
    else if (numerojugador == "3" || numerojugador == "4")
    {
        return ((25 <= x && x <= 52) && (0 <= y && y <= 25));
    }
    else if ((numerojugador == "6" || numerojugador == "8"))
    {
        return ((10 <= x && x <= 40) && (0 <= y && y <= 25));
    }
    else if ((numerojugador == "7" || numerojugador == "11") && (lado == "l"))
    {
        return ((-10 <= coordenadas.first && coordenadas.first <= 40) && (5 <= y && y <= 33));
    }
    else if ((numerojugador == "7" || numerojugador == "11") && (lado == "r"))
    {
        return ((10 >= coordenadas.first && coordenadas.first >= -40) && (5 <= y && y <= 33));
    }
    else if ((numerojugador == "10") && (lado == "l"))
    {
        return ((-25 <= coordenadas.first && coordenadas.first <= 40) && (0 <= y && y <= 25));
    }
    else if ((numerojugador == "10") && (lado == "r"))
    {
        return ((25 >= coordenadas.first && coordenadas.first >= -40) && (0 <= y && y <= 25));
    }
    else if ((numerojugador == "9") && (lado == "l"))
    {
        return ((-15 <= coordenadas.first && coordenadas.first <= 50) && (0 <= y && y <= 25));
    }
    else if ((numerojugador == "9") && (lado == "r"))
    {
        return ((-50 <= coordenadas.first && coordenadas.first <= 15) && (0 <= y && y <= 25));
    }
    else
    {
        return false;
    }
}

string calculoangulogiro(float x, float y, float xgiro, float ygiro, float angulojugador)
{
    float angulogiro;
    float beta = atan((ygiro - y) / (xgiro - x));
    beta = beta * 180 / M_PI;

    if (xgiro > x)
    {
        if (beta > 0)
        {
            angulogiro = angulojugador + beta;
            if (angulogiro > 180)
            {
                angulogiro = angulogiro - 360;
            }
        }
        else
        {
            angulogiro = angulojugador - abs(beta);
            if (angulogiro > 180)
            {
                angulogiro = angulogiro - 360;
            }
        }
    }
    else
    {
        if (beta > 0)
        {
            beta = 180 - abs(beta);
            angulogiro = angulojugador - beta;
            if (angulogiro > 180)
            {
                angulogiro = angulogiro - 360;
            }
        }
        else
        {
            beta = abs(beta) + 180;
            angulogiro = angulojugador - beta;
            if (angulogiro > 180)
            {
                angulogiro = angulogiro - 360;
            }
        }
    }

    ostringstream giro2;
    giro2 << angulogiro;
    string giro(giro2.str());
    return giro;
}