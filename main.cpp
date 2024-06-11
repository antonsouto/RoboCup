#include <iostream>

using namespace std;

#include <MinimalSocket/udp/UdpSocket.h>
#include "stringutils.h"
#include "types.h"
#include "parsemessages.h"
#include "tictoc.h"
#include <chrono>
#include <thread>

// main with two args
int main(int argc, char *argv[])
{
    // check if the number of arguments is correct
    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " <team-name> <this-port>" << endl;
        return 1;
    }

    // get the team name and the port
    string team_name = argv[1];
    MinimalSocket::Port this_socket_port = std::stoi(argv[2]);

    cout << "Creating a UDP socket" << endl;

    MinimalSocket::udp::Udp<true> udp_socket(this_socket_port, MinimalSocket::AddressFamily::IP_V6);

    cout << "Socket created" << endl;

    bool success = udp_socket.open();

    if (!success)
    {
        cout << "Error opening socket" << endl;
        return 1;
    }

    MinimalSocket::Address other_recipient_udp = MinimalSocket::Address{"127.0.0.1", 6000};
    cout << "(init " + team_name + "(version 19))";

    udp_socket.sendTo("(init " + team_name + "(version 19))", other_recipient_udp);
    cout << "Init Message sent" << endl;

    std::size_t message_max_size = 1000;
    cout << "Waiting for a message" << endl;
    auto received_message = udp_socket.receive(message_max_size);
    std::string received_message_content = received_message->received_message;

    // update upd port to provided by the other udp
    MinimalSocket::Address other_sender_udp = received_message->sender;
    MinimalSocket::Address server_udp = MinimalSocket::Address{"127.0.0.1", other_sender_udp.getPort()};
































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
            auto received_message = udp_socket.receive(message_max_size);
            std::string received_message_content = received_message->received_message;
            try
            {
                player = Parser::parseSeverMessage(received_message_content, player);
            }
            catch (const std::exception &e)
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