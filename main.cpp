#include <iostream>
#include "colocarjugadores.h"
#include "funciones_de_juego.h"
#include "Minimal-Socket/src/header/MinimalSocket/udp/UdpSocket.h"
#include <random>
#include <fstream>
#include "stringutilities.h"
#include <chrono>
#include <thread>
#include "tictoc.h"
#include "RetornoAZona.h"
// #include "stringutils.h"
// #include "types.h"
// #include "parsemessages.h"
// #include "tictoc.h"

// main with two args
int main(int argc, char *argv[])
{
    // check if the number of arguments is correct
    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " <team-name> <this-port>" << endl;
        return 1;
    }

    // get the team name and creating a random number for the local port
    string team_name = argv[1]; // Almacenamos el nombre del equipo
    random_device r;
    mt19937 gen(r());
    std::uniform_int_distribution<> distribucion(6000, 10000);
    // Genero el puerto aleatorio
    int puerto_local_aleatorio = distribucion(gen);
    MinimalSocket::Port this_socket_port = puerto_local_aleatorio; // puerto local de escucha del socket

    cout << "Creating a UDP socket" << endl;

    MinimalSocket::udp::Udp<true> udp_socket(this_socket_port, MinimalSocket::AddressFamily::IP_V6); // Establece la conexion con el puerto tipo UDP (Crea el objeto MinimalSocket)

    cout << "Socket Player preated" << endl;

    bool success = udp_socket.open(); // Abre el socket creado para la comunicación y enlaza el puerto especificado

    if (!success)
    {
        cout << "Error opening socket" << endl;
        return 1;
    }

    MinimalSocket::Address other_recipient_udp = MinimalSocket::Address{"127.0.0.1", 6000}; // Mandas un mensaje al puerto 6000 y recibes la direccion de puerto nueva del servidor
    cout << "(init " + team_name + "(version 19))";
    string tipo_jugador = argv[2];
    if (tipo_jugador == "goalie")
    {
        udp_socket.sendTo("(init " + team_name + "(version 19) (goalie))", other_recipient_udp);
    }
    else
    {
        udp_socket.sendTo("(init " + team_name + "(version 19))", other_recipient_udp);
    }

    cout << "Init Message sent" << endl;

    std::size_t message_max_size = 10000;
    cout << "Waiting for a message" << endl;

    auto received_message = udp_socket.receive(message_max_size);
    std::string received_message_content = received_message->received_message;
    auto mensajeprueba = separarPalabras(received_message_content);
    auto numerojugador = mensajeprueba[2];
    auto ladoJugador = mensajeprueba[1];

    // update upd port to provided by the other udp
    MinimalSocket::Address other_sender_udp = received_message->sender;
    MinimalSocket::Address server_udp = MinimalSocket::Address{"127.0.0.1", other_sender_udp.getPort()}; // getPort() retorna el nuevo puerto de comunicacion del servidor

    // cout << received_message_content << endl;                                                                     //string que devuelve el servidor cuando se conecta un cliente
    if (received_message_content == "(error no_more_team_or_player_or_goalie)")
    {
        cout << "\nEl equipo está completo o ya existe un portero para el mismo\n";
        return -1;
    }
    else
    {
        string inicioJugador = inicializoJugador(received_message_content);
        udp_socket.sendTo(inicioJugador, server_udp);
    }

    //---------------------------------------------------------------------------------------------------------------------EMPIEZA LA RUTINA DE JUEGO (BUCLE)

    bool enJuego = false;
    TicToc clock;
    clock.tic();
    while (true)
    {

        auto received_message = udp_socket.receive(message_max_size);
        string received_message_content = received_message->received_message;
        // Prefijo a buscar
        string resultado = procesado(received_message_content, ladoJugador, numerojugador, team_name);
        udp_socket.sendTo(resultado, server_udp);
    }

    /*
    Player player;
    player = Parser::parseInitialMessage(received_message_content, player);
    cout << player << endl;
    sendInitialMoveMessage(player, udp_socket, server_udp);

    TicToc clock;
    clock.tic();
    unsigned long cycle = 0;
    while (1)
    {
        // PROCESS MESSAGES
        do
        {
            auto received_message = udp_socket.receive(message_max_size); //AQUI SE ESCUCHA LO QUE RECIBIMOS DEL SOCKET
            std::string received_message_content = received_message->received_message;
            try
            {
                player = Parser::parseSeverMessage(received_message_content, player);
            }
            catch (const std    // Player player;
    // player = Parser::parseInitialMessage(received_message_content, player);
    // cout << player << endl;
    // sendInitialMoveMessage(player, udp_socket, server_udp);::exception &e)
            {
                cout << e.what() << endl;
            }
        } while (!received_message_content.find("(see") == std::string::npos || clock.toc() < 100);
        cout << player << endl;

        // ACTION (whenever a see message is received)

        // cout << "time: " << clock.toc() << "ms" << endl;
        clock.tic();
        // cout << player << endl;

        // PROCESS THE DATA AND SEND A COMMAND TO THE SERVER

        // udp_socket.sendTo("(bla bla bla)", server_udp);
    }
    */
    return 0;
}