#include "network_server.hpp"
#include "../common/network_opcodes.hpp"

void network_packet_receive(sf::Packet& receive_packet)
{
    sf::Uint8 opcode;
    while( !receive_packet.endOfPacket() )
    {
        receive_packet >> opcode;
        switch( opcode )
        {
        default:
        {
            break;
        }
        }//end switch
    }
}

void network_lobby_packet_receive(sf::Packet& receive_packet, sf::Packet& send_packet, std::vector<Player>& players,
                                  const sf::IpAddress& ip, unsigned short port)
{
    sf::Uint8 opcode;
    while( !receive_packet.endOfPacket() )
    {
        receive_packet >> opcode;
        switch( opcode )
        {
        case CLIENT_JOIN_GAME:
        {
            send_packet<<(sf::Uint8)SERVER_PLAYER_CONNECTED<<(sf::Uint8)players.size();
            players.emplace_back(ip, port);
            break;
        }
        case CLIENT_DISCONNECT:
        {
            sf::Uint8 id;
            receive_packet >> id;
            players.erase(players.begin() + id);
            send_packet<<(sf::Uint8)SERVER_PLAYER_DISCONNECTED<<id;
            break;
        }
        case CLIENT_READY:
        {
            sf::Uint8 id;
            receive_packet >> id;
            players[id].set_ready_status(true);
            send_packet<<(sf::Uint8)SERVER_PLAYER_READY<<id;
            break;
        }
        case CLIENT_NOTREADY:
        {
            sf::Uint8 id;
            receive_packet >> id;
            players[id].set_ready_status(false);
            send_packet<<(sf::Uint8)SERVER_PLAYER_NOTREADY<<id;
            break;
        }
        case CLIENT_SEND_MESSAGE:
        {
            sf::Uint8 id;
            std::wstring str;
            receive_packet >> id >> str;
            send_packet<<(sf::Uint8)SERVER_MESSAGE<<id<<str;
            break;
        }
        default:
        {
            break;
        }
        }//end switch
    }
}
