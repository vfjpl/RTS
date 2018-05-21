#include "lobby_server.hpp"
#include "network_server.hpp"
#include "../common/network_opcodes.hpp"

void lobby_server(sf::UdpSocket& socket, std::vector<Player>& players)
{
    bool ready = false;
    sf::Packet send_packet;
    sf::Packet receive_packet;
    sf::IpAddress incomming_ip;
    unsigned short incomming_port;

    while( !ready )
    {
        for(sf::Uint8 i = 0; i <= players.size(); i++)//+1 bo czekamy na kolejnych
        {
            socket.receive( receive_packet, incomming_ip, incomming_port );
            network_lobby_packet_receive( receive_packet, send_packet, players,
                                          incomming_ip, incomming_port );
        }

        for(sf::Uint8 i = 0; i < players.size(); i++)
            socket.send( send_packet, players[i].get_ip(), players[i].get_port() );
        send_packet.clear();



        ready = true;
        for(sf::Uint8 i = 0; i < players.size(); i++)
            ready = ready && players[i].get_ready_status();
    }

    send_packet << (sf::Uint8)SERVER_START_GAME;
    for(sf::Uint8 i = 0; i < players.size(); i++)
        socket.send( send_packet, players[i].get_ip(), players[i].get_port() );
}
