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
        default:
        {
            break;
        }
        }//end switch
    }
}

void network_menu_packet_receive(sf::Packet& receive_packet, std::vector<Player>& players, bool& quit_menu)
{
    sf::Uint8 opcode;
    while( !receive_packet.endOfPacket() )
    {
        receive_packet >> opcode;
        switch( opcode )
        {
        case SERVER_START_GAME:
        {
            quit_menu = true;
            break;
        }
        case SERVER_PLAYER_CONNECTED:
        {
            sf::Uint8 id;
            receive_packet >> id;
            if((sf::Uint8)players.size() < id)
                players.resize(id);
            players.emplace_back();
            break;
        }
        case SERVER_PLAYER_DISCONNECTED:
        {
            sf::Uint8 id;
            receive_packet >> id;
            players.erase(players.begin() + id);
            break;
        }
        case SERVER_PLAYER_READY:
        {
            sf::Uint8 id;
            receive_packet >> id;
            players[id].set_ready_status(true);
            break;
        }
        case SERVER_PLAYER_NOTREADY:
        {
            sf::Uint8 id;
            receive_packet >> id;
            players[id].set_ready_status(false);
            break;
        }
        case SERVER_MESSAGE:
        {
            break;
        }
        default:
        {
            break;
        }
        }//end switch
    }
}
