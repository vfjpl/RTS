#include "network_server.hpp"
#include "../common/network_opcodes.hpp"

void lobby_server(sf::UdpSocket& socket, Player* players, sf::Uint8 number_of_players)
{
    sf::Packet send_packet;
    sf::Packet receive_packet;
    sf::IpAddress incomming_ip;
    unsigned short incomming_port;

    sf::Uint8 current_number_of_players = 0;
    bool *ready_table = new bool[number_of_players];
    bool ready = false;

    while( !ready )
    {
        for(sf::Uint8 i = 0; i <= current_number_of_players; i++)//+1 bo czekamy na kolejnych
        {
            socket.receive( receive_packet, incomming_ip, incomming_port );
            network_lobby_packet_receive( receive_packet, send_packet, current_number_of_players, players,
                                          incomming_ip, incomming_port, ready_table );
        }

        for(sf::Uint8 i = 0; i < current_number_of_players; i++)
            socket.send( send_packet, players[i].get_ip(), players[i].get_port() );
        send_packet.clear();

        ready = true;
        for(sf::Uint8 i = 0; i < current_number_of_players; i++)
            ready = ready && ready_table[i];//sprawdza czy gracze są ready jeśli tak to wychodzi z pętli
    }

    send_packet << SERVER_STARTED_GAME;
    for(sf::Uint8 i = 0; i < number_of_players; i++)
        socket.send( send_packet, players[i].get_ip(), players[i].get_port() );

    delete[] ready_table;
}
//TODO:
//ogarnąć jak zarządzać na ilu graczy gra
