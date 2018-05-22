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
            bool status;
            receive_packet >> id >> status;
            players[id].set_ready_status(status);
            send_packet<<(sf::Uint8)SERVER_PLAYER_READY<<id<<status;
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
        case CLIENT_SET_NAME:
        {
            sf::Uint8 id;
            std::wstring str;
            receive_packet >> id >> str;
            players[id].set_name(str);
            send_packet<<(sf::Uint8)SERVER_PLAYER_NAME<<id<<str;
            break;
        }
        default:
        {
            break;
        }
        }//end switch
    }
}
