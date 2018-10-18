#include "engine.hpp"
#include "../common/network_opcodes.hpp"
#include <iostream>

void Client_Engine::init()
{
    socket.setBlocking(false);
    window.setFramerateLimit(60);
    window.create(sf::VideoMode(800, 600), L"Kelajno");//sf::Style::Fullscreen
    server.set_ip_port(sf::IpAddress::LocalHost, 7000);
    resources_manager.load_resources();
    menu.init();
}

void Client_Engine::quit_engine()
{
    menu_loop = false;
    lobby_loop = false;
    game_loop = false;
}

void Client_Engine::receive_packets()
{
    sf::IpAddress incomming_ip;
    unsigned short incomming_port;
    sf::Uint8 opcode;
    while ( !socket.receive( received_packet, incomming_ip, incomming_port ) )
    {
        if( server.compare(incomming_ip, incomming_port) )
        {
            server.set_network_timeout( sf::Time::Zero );
            while( !received_packet.endOfPacket() )
            {
                received_packet >> opcode;
                switch( opcode )
                {
                case SERVER_GAME_STATUS:
                {
                    bool game_status;
                    received_packet >> game_status;
                    game_loop = game_status;
                    break;
                }
                case SERVER_SET_ALL_PLAYERS_READY_STATUS:
                {
                    bool ready_status;
                    received_packet >> ready_status;
                    set_all_players_ready_status(ready_status);
                    break;
                }
                case SERVER_PLAYER_CONNECTED:
                {
                    sf::Uint8 id;
                    received_packet >> id;
                    if(id > players.size())
                        players.resize(id);
                    players.emplace_back();
                    break;
                }
                case SERVER_PLAYER_DISCONNECTED:
                {
                    sf::Uint8 id;
                    received_packet >> id;
                    players.erase(players.begin() + id);
                    break;
                }
                case SERVER_PLAYER_READY_STATUS:
                {
                    sf::Uint8 id;
                    bool ready_status;
                    received_packet >> id >> ready_status;
                    players[id].set_ready_status(ready_status);
                    break;
                }
                case SERVER_PLAYER_MESSAGE:
                {
                    sf::Uint8 id;
                    std::wstring str;
                    received_packet >> id >> str;

                    break;
                }
                case SERVER_PLAYER_NICKNAME:
                {
                    sf::Uint8 id;
                    std::wstring str;
                    received_packet >> id >> str;
                    players[id].set_nickname(str);
                    break;
                }
                case SERVER_PLAYER_TEAM:
                {
                    sf::Uint8 id;
                    sf::Uint8 team;
                    received_packet >> id >> team;
                    players[id].set_team(team);
                    break;
                }
                default:
                {
                    received_packet.clear();
                    break;
                }
                }//end switch
            }//end while
        }//end if
    }//end while
}

void Client_Engine::draw_frame()
{
    window.clear();
    menu.draw(window);
    window.display();
}

void Client_Engine::send_packets()
{
    socket.send(packet_to_send, server.get_ip(), server.get_port());
    packet_to_send.clear();
}

bool Client_Engine::get_menu_loop() const
{
    return menu_loop;
}

bool Client_Engine::get_lobby_loop() const
{
    return lobby_loop;
}

bool Client_Engine::get_game_loop() const
{
    return game_loop;
}

void Client_Engine::set_all_players_ready_status(bool status)
{
    for(sf::Uint8 i = 0; i < players.size(); ++i)
        players[i].set_ready_status(status);
}

void Client_Engine::debug_show_size() const
{
    //keep up to date!
    std::wcout << sizeof(window) << L"\n"
               << sizeof(units) << L"\n"
               << sizeof(players) << L"\n"
               << sizeof(packet_to_send) << L"\n"
               << sizeof(received_packet) << L"\n"
               << sizeof(socket) << L"\n"
               << sizeof(clock) << L"\n"
               << sizeof(time) << L"\n"
               << sizeof(menu_loop) << L"\n"
               << sizeof(lobby_loop) << L"\n"
               << sizeof(game_loop) << L"\n";
}
