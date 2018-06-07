#include "game_client_session.hpp"
#include "../common/network_opcodes.hpp"
#include <iostream>

Game_Client_Session::Game_Client_Session()
{
    server.set_ip_port(sf::IpAddress::LocalHost, 7000);
    socket.setBlocking(false);
    window.create(sf::VideoMode(800, 600), "Kelajno");//sf::Style::Fullscreen
    window.setFramerateLimit(60);
}

void Game_Client_Session::lobby_receive_inputs()
{
    sf::Event event;
    while( window.pollEvent(event) )
    {
        switch(event.type)
        {
        case sf::Event::Closed:
        {
            app_loop = false;
            game_loop = false;
            break;
        }
        default:
        {
            break;
        }
        }//end switch
    }
}

void Game_Client_Session::lobby_logic()
{
    time = clock.restart();
    if(server.get_network_timeout().asSeconds() > 1)
    {
        //connection to server lost, back to main menu
        server.set_network_timeout( sf::Time::Zero );
        players.clear();
        return;
    }
    server.add_network_timeout(time);
}

void Game_Client_Session::lobby_draw_frame()
{
    window.clear();
    window.display();
}

void Game_Client_Session::game_receive_inputs()
{
    sf::Event event;
    while( window.pollEvent(event) )
    {
        switch(event.type)
        {
        case sf::Event::Closed:
        {
            app_loop = false;
            game_loop = false;
            break;
        }
        case sf::Event::KeyPressed:
        {
            game_receive_inputs_keypress(event);
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            game_receive_inputs_mousepress(event);
            break;
        }
        default:
        {
            break;
        }
        }//end switch
    }
}

void Game_Client_Session::game_receive_inputs_keypress(const sf::Event& event)
{
    switch(event.key.code)
    {
    case sf::Keyboard::Escape:
    {
        app_loop = false;
        game_loop = false;
        break;
    }
    default:
    {
        break;
    }
    }//end switch
}

void Game_Client_Session::game_receive_inputs_mousepress(const sf::Event& event)
{
    switch(event.mouseButton.button)
    {
    case sf::Mouse::Middle:
    {
        app_loop = false;
        game_loop = false;
        break;
    }
    default:
    {
        break;
    }
    }//end switch
}

void Game_Client_Session::game_logic()
{
    time = clock.restart();
    if(server.get_network_timeout().asSeconds() > 1)
    {
        //connection to server lost, back to main menu
        game_loop = false;
        server.set_network_timeout( sf::Time::Zero );
        players.clear();
        units.clear();
        return;
    }
    server.add_network_timeout(time);
}

void Game_Client_Session::game_draw_frame()
{
    window.clear();
    window.display();
}

void Game_Client_Session::receive_packets()
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
                case SERVER_START_GAME:
                {
                    game_loop = true;
                    for(sf::Uint8 i = 0; i < players.size(); ++i)//reset ready status after game started
                        players[i].set_ready_status(false);
                    break;
                }
                case SERVER_STOP_GAME:
                {
                    game_loop = false;
                    units.clear();
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

void Game_Client_Session::send_packets()
{
    socket.send( packet_to_send, server.get_ip(), server.get_port() );
    packet_to_send.clear();
}

bool Game_Client_Session::get_app_loop() const
{
    return app_loop;
}

bool Game_Client_Session::get_game_loop() const
{
    return game_loop;
}

void Game_Client_Session::debug_show_size() const
{
    //keep up to date!
    std::cout << sizeof(window) << "\n"
              << sizeof(units) << "\n"
              << sizeof(server) << "\n"
              << sizeof(packet_to_send) << "\n"
              << sizeof(received_packet) << "\n"
              << sizeof(socket) << "\n"
              << sizeof(players) << "\n"
              << sizeof(blueprints) << "\n"
              << sizeof(clock) << "\n"
              << sizeof(time) << "\n"
              << sizeof(app_loop) << "\n"
              << sizeof(game_loop) << "\n";
}
