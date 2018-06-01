#include "game_server_session.hpp"
#include "../common/network_opcodes.hpp"
#include <iostream>

Game_Server_Session::Game_Server_Session()
{
    socket.bind(7000);
}

void Game_Server_Session::lobby_receive_packets()
{
    sf::IpAddress incomming_ip;
    unsigned short incomming_port;
    sf::Uint8 opcode;
    sf::Uint8 local_id;
    for(sf::Uint8 i = 0; i <= players.size(); i++)//(<=) because we are waiting for more players
    {
        socket.receive( received_packet, incomming_ip, incomming_port );
        local_id = get_player_id(incomming_ip, incomming_port);
        if(local_id != 255)
            players[local_id].set_network_timeout( sf::Time::Zero );

        while( !received_packet.endOfPacket() )
        {
            received_packet >> opcode;
            switch( opcode )
            {
            case JOIN_GAME:
            {
                clock.restart();//to prevent instant timeout disconnect
                sf::Uint8 id = players.size();
                packet_to_send<<(sf::Uint8)SERVER_PLAYER_CONNECTED<<id;
                players.emplace_back(incomming_ip, incomming_port);
                break;
            }
            case DISCONNECT:
            {
                sf::Uint8 id;
                received_packet >> id;
                players.erase(players.begin() + id);
                packet_to_send<<(sf::Uint8)SERVER_PLAYER_DISCONNECTED<<id;

                for(sf::Uint8 i = 0; i < players.size(); i++)//to prevent auto starting
                {
                    players[i].set_ready_status(false);
                    packet_to_send<<(sf::Uint8)SERVER_PLAYER_READY_STATUS<<i<<false;
                }
                break;
            }
            case SET_READY_STATUS:
            {
                sf::Uint8 id;
                bool ready_status;
                received_packet >> id >> ready_status;
                players[id].set_ready_status(ready_status);
                packet_to_send<<(sf::Uint8)SERVER_PLAYER_READY_STATUS<<id<<ready_status;
                break;
            }
            case SEND_MESSAGE:
            {
                sf::Uint8 id;
                std::wstring str;
                received_packet >> id >> str;
                packet_to_send<<(sf::Uint8)SERVER_PLAYER_MESSAGE<<id<<str;
                break;
            }
            case SET_NICKNAME:
            {
                sf::Uint8 id;
                std::wstring str;
                received_packet >> id >> str;
                players[id].set_nickname(str);
                packet_to_send<<(sf::Uint8)SERVER_PLAYER_NICKNAME<<id<<str;
                break;
            }
            default:
            {
                received_packet.clear();
                break;
            }
            }//end switch
        }
    }
}

void Game_Server_Session::lobby_logic()
{
    time = clock.restart();

    bool ready = true;
    for(sf::Uint8 i = 0; i < players.size(); i++)
    {
        players[i].set_network_timeout(players[i].get_network_timeout() + time);
        if(players[i].get_network_timeout().asSeconds() >= 1)//timeout disconnect
        {
            players.erase(players.begin() + i);
            packet_to_send << (sf::Uint8)SERVER_PLAYER_DISCONNECTED << i;
            ready = false;//to prevent auto staring when last non ready player timeout disconnect
            i--;

            for(sf::Uint8 i = 0; i < players.size(); i++)//to prevent auto starting
            {
                players[i].set_ready_status(false);
                packet_to_send<<(sf::Uint8)SERVER_PLAYER_READY_STATUS<<i<<false;
            }
        }
        else
        {
            ready &= players[i].get_ready_status();//ready true only if all players are ready
        }
    }

    if( ready && players.size() != 0 )//to prevent starting when there are no players in lobby
    {
        game_loop = true;
        packet_to_send << (sf::Uint8)SERVER_START_GAME;
    }
}

void Game_Server_Session::game_receive_packets()
{
    sf::IpAddress incomming_ip;
    unsigned short incomming_port;
    sf::Uint8 opcode;
    for(sf::Uint8 i = 0; i <= players.size(); i++)
    {
        socket.receive( received_packet, incomming_ip, incomming_port );
        while( !received_packet.endOfPacket() )
        {
            received_packet >> opcode;
            switch( opcode )
            {
            default:
            {
                received_packet.clear();
                break;
            }
            }//end switch
        }
    }
}

void Game_Server_Session::game_logic()
{
    time = clock.restart();
}

void Game_Server_Session::send_packets()
{
    for(sf::Uint8 i = 0; i < players.size(); i++)
        socket.send( packet_to_send, players[i].get_ip(), players[i].get_port() );
    packet_to_send.clear();
}

bool Game_Server_Session::get_app_loop() const
{
    return app_loop;
}

bool Game_Server_Session::get_game_loop() const
{
    return game_loop;
}

sf::Uint8 Game_Server_Session::get_player_id(sf::IpAddress ip, unsigned short port) const
{
    for(sf::Uint8 i = 0; i < players.size(); i++)
        if(players[i].compare(ip,port))
            return i;

    return 255;//if there is no connected player with this ip and port
}

void Game_Server_Session::debug_show_size() const
{
    //keep up to date!
    std::cout << sizeof(packet_to_send) << "\n"
              << sizeof(received_packet) << "\n"
              << sizeof(socket) << "\n"
              << sizeof(players) << "\n"
              << sizeof(clock) << "\n"
              << sizeof(time) << "\n"
              << sizeof(app_loop) << "\n"
              << sizeof(game_loop) << "\n";
}
