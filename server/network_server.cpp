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
            ready_table[current] = false;
            p_tab[current++].set_ip_port(ip, port);
            send<<PLAYER_CONNECTED;
            break;
        case SEND_PLAYER_READY:
        {
            sf::Uint8 id;
            receive >> id;
            ready_table[id] = true;
            break;
        }
        case SEND_MESSAGE:
            break;
        default:
            break;
        }//end switch
    }
}

void network_players_init(sf::UdpSocket& socket, Player* players, sf::Uint8 number_of_players)
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
            socket.send( send_packet, incomming_ip, incomming_port );
        send_packet.clear();

        ready = true;
        for(sf::Uint8 i = 0; i < current_number_of_players; i++)
            ready = ready && ready_table[i];//sprawdza czy gracze są ready jeśli tak to wychodzi z pętli
    }

    send_packet << SERVER_STARTED_GAME;
    for(sf::Uint8 i = 0; i < number_of_players; i++)
        socket.send( send_packet, players[i].get_ip(), players[i].get_port() );
}
//TODO:
//ogarnąć jak zarządzać na ilu graczy gra
