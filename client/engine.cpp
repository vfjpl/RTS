#include "engine.hpp"
#include "resources_manager.hpp"
#include "menu.hpp"
#include "lobby.hpp"
#include "network_data.hpp"
#include <iostream>

extern sf::RenderWindow window;
extern Resources_Manager resources_manager;
extern Menu menu;
extern Lobby lobby;
extern Network_Data server;

void Client_Engine::init()
{
    socket.setBlocking(false);
    server.set_ip_port(sf::IpAddress::LocalHost, 7000);
    resources_manager.load_resources();
    setup_window(false);
    menu.setup();
}

void Client_Engine::setup_window(bool fullscreen)
{
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    if(fullscreen)
    {
        window.create(mode, L"kelajno", sf::Style::Fullscreen);
    }
    else
    {
        mode.width = (mode.width*2)/3;
        mode.height = (mode.height*2)/3;
        window.create(mode, L"kelajno", sf::Style::Close);
    }
    window.setFramerateLimit(60);
}

void Client_Engine::setup_menu()
{
    menu_loop = true;
    lobby_loop = false;
    game_loop = false;
    server.reset_network_timeout();
    players.clear();
    units.clear();
    lobby.clear();
    menu.setup();
}

void Client_Engine::setup_lobby()
{
    menu_loop = true;
    lobby_loop = true;
    game_loop = false;
    menu.clear();
    lobby.setup();
}

void Client_Engine::setup_game()
{
    menu_loop = true;
    lobby_loop = true;
    game_loop = true;
    menu.clear();
    lobby.clear();
}

void Client_Engine::quit_engine()
{
    menu_loop = false;
    lobby_loop = false;
    game_loop = false;
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
    std::wcout << sizeof(units) << L'\n'
               << sizeof(players) << L'\n'
               << sizeof(packet_to_send) << L'\n'
               << sizeof(received_packet) << L'\n'
               << sizeof(socket) << L'\n'
               << sizeof(clock) << L'\n'
               << sizeof(time) << L'\n'
               << sizeof(menu_loop) << L'\n'
               << sizeof(lobby_loop) << L'\n'
               << sizeof(game_loop) << L'\n';
}
