#include "server_engine.hpp"
#include "../common/network_opcodes.hpp"
#include <iostream>

Server_Engine::Server_Engine()
{
    socket.bind(7000);
}

void Server_Engine::receive_packets()
{
    sf::IpAddress incomming_ip;
    unsigned short incomming_port;
    sf::Uint8 opcode;
    sf::Uint8 local_id;
    for(sf::Uint8 i = 0; i <= players.size(); ++i)//[ <= ]because we are waiting for more players
    {
        socket.receive( received_packet, incomming_ip, incomming_port );
        local_id = get_player_id(incomming_ip, incomming_port);

        if(local_id == players.size())//check if we got new player
        {
            if(local_id == 6)//max 254 because sf::Uint8 is max 255
                continue;//don't add new player

            packet_to_send << (sf::Uint8)SERVER_PLAYER_CONNECTED << local_id;
            players.emplace_back(incomming_ip, incomming_port);
        }

        players[local_id].set_network_timeout( sf::Time::Zero );
        while( !received_packet.endOfPacket() )
        {
            received_packet >> opcode;
            switch( opcode )
            {
            case SET_READY_STATUS:
            {
                bool ready_status;
                received_packet >> ready_status;
                players[local_id].set_ready_status(ready_status);
                packet_to_send << (sf::Uint8)SERVER_PLAYER_READY_STATUS << local_id << ready_status;
                break;
            }
            case SEND_MESSAGE:
            {
                std::wstring str;
                received_packet >> str;
                packet_to_send << (sf::Uint8)SERVER_PLAYER_MESSAGE << local_id << str;
                break;
            }
            case SET_NICKNAME:
            {
                std::wstring str;
                received_packet >> str;
                players[local_id].set_nickname(str);
                packet_to_send << (sf::Uint8)SERVER_PLAYER_NICKNAME << local_id << str;
                break;
            }
            case SET_TEAM:
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

void Server_Engine::send_packets()
{
    for(sf::Uint8 i = 0; i < players.size(); ++i)
        socket.send( packet_to_send, players[i].get_ip(), players[i].get_port() );
    packet_to_send.clear();
}

bool Server_Engine::get_app_loop() const
{
    return app_loop;
}

bool Server_Engine::get_game_loop() const
{
    return game_loop;
}

sf::Uint8 Server_Engine::get_player_id(sf::IpAddress ip, unsigned short port) const
{
    for(sf::Uint8 i = 0; i < players.size(); ++i)
        if(players[i].compare(ip, port))
            return i;

    return players.size();//return next player id
}

void Server_Engine::set_all_players_ready_status(bool status)
{
    for(sf::Uint8 i = 0; i < players.size(); ++i)
        players[i].set_ready_status(status);
}

void Server_Engine::debug_show_size() const
{
    //keep up to date!
    std::cout << sizeof(units) << "\n"
              << sizeof(packet_to_send) << "\n"
              << sizeof(received_packet) << "\n"
              << sizeof(socket) << "\n"
              << sizeof(players) << "\n"
              << sizeof(clock) << "\n"
              << sizeof(time) << "\n"
              << sizeof(app_loop) << "\n"
              << sizeof(game_loop) << "\n";
}
