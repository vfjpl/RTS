#include "engine.hpp"
#include "../common/network_opcodes.hpp"

void Server_Engine::lobby_receive_packets()
{
    sf::IpAddress incomming_ip;
    unsigned short incomming_port;
    sf::Uint8 local_id;
    sf::Uint8 opcode;
    for(sf::Uint8 i = 0; i <= players.size(); ++i)// <= because we are waiting for more players
    {
        socket.receive(received_packet, incomming_ip, incomming_port);
        local_id = get_player_id(incomming_ip, incomming_port);

        if(local_id == players.size())//check if we got new player
            connect_player(incomming_ip, incomming_port);

        players[local_id].reset_network_timeout();
        while( !received_packet.endOfPacket() )
        {
            received_packet >> opcode;
            switch(opcode)
            {
            case CLIENT_SET_READY_STATUS:
            {
                bool ready_status;
                received_packet >> ready_status;
                players[local_id].set_ready_status(ready_status);
                packet_to_send << (sf::Uint8)SERVER_PLAYER_READY_STATUS << local_id << ready_status;

                if(get_ready_status_of_players())//check if all players are ready
                    setup_game();//start new game
                break;
            }
            case CLIENT_SEND_MESSAGE:
            {
                std::wstring str;
                received_packet >> str;
                packet_to_send << (sf::Uint8)SERVER_PLAYER_MESSAGE << local_id << str;
                break;
            }
            case CLIENT_SET_NICKNAME:
            {
                std::wstring str;
                received_packet >> str;
                players[local_id].set_nickname(str);
                packet_to_send << (sf::Uint8)SERVER_PLAYER_NICKNAME << local_id << str;
                break;
            }
            case CLIENT_SET_TEAM:
            {
                sf::Uint8 team;
                received_packet >> team;
                players[local_id].set_team(team);
                packet_to_send << (sf::Uint8)SERVER_PLAYER_TEAM << local_id << team;
                break;
            }
            default:
            {
                received_packet.clear();
                break;
            }
            }//end switch
        }//end while
    }//end for
}

void Server_Engine::lobby_logic()
{
    time = clock.restart();

    for(sf::Uint8 i = 0; i < players.size(); )
        if(players[i].get_network_timeout() > sf::seconds(1))
            disconnect_player(i);
        else
            players[i++].add_network_timeout(time);
}
