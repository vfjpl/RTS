#include "engine.hpp"
#include "../common/network_opcodes.hpp"
#include <iostream>

void Server_Engine::init()
{
    socket.bind(7000);
}

void Server_Engine::setup_lobby()
{
    lobby_loop = true;
    game_loop = false;
    packet_to_send << (sf::Uint8)SERVER_GAME_STATUS << false;
}

void Server_Engine::setup_game()
{
    lobby_loop = true;
    game_loop = true;
    set_all_players_ready_status(false);
    packet_to_send << (sf::Uint8)SERVER_GAME_STATUS << true;
}

void Server_Engine::send_packets()
{
    for(sf::Uint8 i = 0; i < players.size(); ++i)
        socket.send(packet_to_send, players[i].get_ip(), players[i].get_port());
    packet_to_send.clear();
}

bool Server_Engine::get_lobby_loop() const
{
    return lobby_loop;
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

    return players.size();
}

bool Server_Engine::get_ready_status_of_players() const
{
    for(sf::Uint8 i = 0; i < players.size(); ++i)
        if(!players[i].get_ready_status())
            return false;

    return true;
}

void Server_Engine::set_all_players_ready_status(bool status)
{
    for(sf::Uint8 i = 0; i < players.size(); ++i)
        players[i].set_ready_status(status);
    packet_to_send << (sf::Uint8)SERVER_SET_ALL_PLAYERS_READY_STATUS << status;
}

void Server_Engine::connect_player(sf::IpAddress ip, unsigned short port)
{
    sf::Uint8 id = players.size();
    players.emplace_back(ip, port);
    packet_to_send << (sf::Uint8)SERVER_GAME_STATUS << game_loop;
    packet_to_send << (sf::Uint8)SERVER_PLAYER_CONNECTED << id;
}

void Server_Engine::disconnect_player(sf::Uint8 id)
{
    players.erase(players.begin() + id);
    packet_to_send << (sf::Uint8)SERVER_PLAYER_DISCONNECTED << id;
}

void Server_Engine::debug_show_size() const
{
    //keep up to date!
    std::wcout << sizeof(units) << L'\n'
               << sizeof(players) << L'\n'
               << sizeof(packet_to_send) << L'\n'
               << sizeof(received_packet) << L'\n'
               << sizeof(socket) << L'\n'
               << sizeof(clock) << L'\n'
               << sizeof(time) << L'\n'
               << sizeof(lobby_loop) << L'\n'
               << sizeof(game_loop) << L'\n';
}
