#include "game_client_session.hpp"
#include "../common/network_opcodes.hpp"
#include <iostream>

Game_Client_Session::Game_Client_Session()
{
    socket.setBlocking(false);
    window.create(sf::VideoMode(800, 600), "Kelajno");//sf::Style::Fullscreen
    window.setFramerateLimit(60);
}

void Game_Client_Session::main_menu_receive_packets()
{
    sf::IpAddress incomming_ip;
    unsigned short incomming_port;
    sf::Uint8 opcode;
    while ( !socket.receive( received_packet, incomming_ip, incomming_port ) )
    {
        while( !received_packet.endOfPacket() )
        {
            received_packet >> opcode;
            switch( opcode )
            {
            case SERVER_START_GAME:
            {
                game_loop = true;
                break;
            }
            case SERVER_PLAYER_CONNECTED:
            {
                sf::Uint8 id;
                received_packet >> id;
                players.resize(id + 1);
                break;
            }
            case SERVER_PLAYER_DISCONNECTED:
            {
                sf::Uint8 id;
                received_packet >> id;
                players.erase(players.begin() + id);
                break;
            }
            case SERVER_PLAYER_READY:
            {
                sf::Uint8 id;
                bool status;
                received_packet >> id >> status;
                players[id].set_ready_status(status);
                break;
            }
            case SERVER_MESSAGE:
            {
                sf::Uint8 id;
                std::wstring str;
                received_packet >> id >> str;
                break;
            }
            case SERVER_PLAYER_NAME:
            {
                sf::Uint8 id;
                std::wstring str;
                received_packet >> id >> str;
                players[id].set_name(str);
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

void Game_Client_Session::main_menu_receive_inputs()
{
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

void Game_Client_Session::main_menu_logic()
{
    time = clock.restart();
}

void Game_Client_Session::main_menu_draw_frame()
{
    window.clear();
    window.display();
}

void Game_Client_Session::game_receive_packets()
{
    sf::IpAddress incomming_ip;
    unsigned short incomming_port;
    sf::Uint8 opcode;
    while ( !socket.receive( received_packet, incomming_ip, incomming_port ) )
    {
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

void Game_Client_Session::game_receive_inputs()
{
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
            game_receive_inputs_keypress();
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            game_receive_inputs_mousepress();
            break;
        }
        default:
        {
            break;
        }
        }//end switch
    }
}

void Game_Client_Session::game_receive_inputs_keypress()
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

void Game_Client_Session::game_receive_inputs_mousepress()
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
}

void Game_Client_Session::game_draw_frame()
{
    window.clear();
    window.display();
}

void Game_Client_Session::send_packets()
{
    socket.send( packet_to_send, remote_ip, remote_port );
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
              << sizeof(packet_to_send) << "\n"
              << sizeof(received_packet) << "\n"
              << sizeof(socket) << "\n"
              << sizeof(players) << "\n"
              << sizeof(event) << "\n"
              << sizeof(clock) << "\n"
              << sizeof(time) << "\n"
              << sizeof(remote_ip) << "\n"
              << sizeof(remote_port) << "\n"
              << sizeof(app_loop) << "\n"
              << sizeof(game_loop) << "\n";
}
