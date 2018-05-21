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

void network_lobby_packet_receive(sf::Packet& receive, sf::Packet& send, sf::Uint8& current, Player* p_tab,
                                  const sf::IpAddress& ip, unsigned short port, bool* ready_table)
{
    sf::Uint8 opcode;
    while( !receive.endOfPacket() )
    {
        receive >> opcode;
        switch( opcode )
        {
        case REQUEST_GAME_JOIN:
            ready_table[current] = false;//tutaj?
            p_tab[current].set_ip_port(ip, port);
            send<<(sf::Uint8)PLAYER_CONNECTED<<current++;//wysyłam bo jak dołączy drugi gracz to nie wie że jest drugi
            break;
        case SEND_PLAYER_READY:
        {
            sf::Uint8 id;
            receive >> id;
            ready_table[id] = true;
            send<<(sf::Uint8)PLAYER_READY<<id;
            break;
        }
        case SEND_MESSAGE:
        {
            sf::Uint8 id;
            std::wstring str;
            receive >> id >> str;
            send<<(sf::Uint8)SERVER_SEND_MESSAGE<<id<<str;
            break;
        }
        default:
            break;
        }//end switch
    }
}
