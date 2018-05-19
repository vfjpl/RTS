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
        case MOVE_UNIT:
        {
            sf::Uint8 ID_jednostki;
            sf::Uint8 x;
            sf::Uint8 y;
            receive_packet >> ID_jednostki >> x >> y;

            break;
        }
        case ATTACK:
        {
            sf::Uint8 ID_naszej;
            sf::Uint8 ID_atakowanej;
            receive_packet >> ID_naszej >> ID_atakowanej;

            break;
        }
        case CREATE_UNIT:
        {
            sf::Uint8 ID_budynku;
            sf::Uint8 BP_jednostki;
            receive_packet >> ID_budynku >> BP_jednostki;

            break;
        }
        case CREATE_BUILDING:
        {
            sf::Uint8 BP_budynku;
            sf::Uint8 x;
            sf::Uint8 y;
            receive_packet >> BP_budynku >> x >> y;

            break;
        }
        default:
        {
            break;
        }
        }//end switch
    }
}

void network_players_init(sf::UdpSocket& socket, player* players, sf::Uint8 number_of_players)
{
    sf::Packet send_packet;
    sf::Packet receive_packet;
    sf::IpAddress incomming_ip;
    unsigned short incomming_port;

    for(int i = 0; i < number_of_players; )
    {
        socket.receive( receive_packet, incomming_ip, incomming_port );
        sf::Uint8 opcode;
        receive_packet >> opcode;
        if( opcode == REQUEST_GAME_JOIN )
            players[i++] = player( incomming_ip, incomming_port );
    }

    send_packet << SERVER_STARTED_GAME;
    for(int i = 0; i < number_of_players; i++)
        socket.send( send_packet, players[i].get_ip(), players[i].get_port() );
}
