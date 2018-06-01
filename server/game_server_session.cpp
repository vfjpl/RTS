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
    for(sf::Uint8 i = 0; i <= players.size(); i++)
    {
        socket.receive( received_packet, incomming_ip, incomming_port );
        while( !received_packet.endOfPacket() )
        {
            received_packet >> opcode;
            switch( opcode )
            {
            case JOIN_GAME:
            {
                packet_to_send<<(sf::Uint8)SERVER_PLAYER_CONNECTED<<(sf::Uint8)players.size();
                players.emplace_back(incomming_ip, incomming_port);
                break;
            }
            case DISCONNECT:
            {
                sf::Uint8 id;
                received_packet >> id;
                players.erase(players.begin() + id);
                packet_to_send<<(sf::Uint8)SERVER_PLAYER_DISCONNECTED<<id;
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

    if(players.size() == 0)
        return;

    game_loop = true;
    for(sf::Uint8 i = 0; i < players.size(); i++)
        game_loop &= players[i].get_ready_status();

    if( game_loop )
        packet_to_send << (sf::Uint8)SERVER_START_GAME;
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
