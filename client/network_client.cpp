#include "network_client.hpp"
#include "../common/network_opcodes.hpp"

void network_packet_receive(sf::Packet& receive_packet)
{
    sf::Uint8 opcode;
    while( !receive_packet.endOfPacket() )
    {
        receive_packet >> opcode;
        switch( opcode )
        {
        case ADD_UNIT_TO_GAME:
        {
            sf::Uint8 BP_jednostki;
            sf::Uint8 x;
            sf::Uint8 y;
            receive_packet >> BP_jednostki >> x >> y;

            break;
        }
        case SET_UNIT_POSITION:
        {
            sf::Uint8 ID_jednostki;
            sf::Uint8 x;
            sf::Uint8 y;
            receive_packet >> ID_jednostki >> x >> y;

            break;
        }
        default:
        {
            break;
        }
        }//end switch
    }
}

void network_menu_packet_receive(sf::Packet& receive_packet)
{
    sf::Uint8 opcode;
    while( !receive_packet.endOfPacket() )
    {
        receive_packet >> opcode;
        switch( opcode )
        {
        case PLAYER_CONNECTED:
            break;
        default:
            break;
        }//end switch
    }
}
