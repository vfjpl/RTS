#include "engine.hpp"
#include "resources_manager.hpp"
#include "lobby.hpp"
#include "../common/network_data.hpp"
#include "../common/network_opcodes.hpp"

extern sf::RenderWindow window;
extern Resources_Manager resources_manager;
extern Lobby lobby;
extern Network_Data server;

void Client_Engine::lobby_receive_packets()
{
    sf::IpAddress incomming_ip;
    unsigned short incomming_port;
    sf::Uint8 opcode;
    while ( !socket.receive(received_packet, incomming_ip, incomming_port) )
    {
        if(server.compare(incomming_ip, incomming_port))
        {
            server.reset_network_timeout();
            while( !received_packet.endOfPacket() )
            {
                received_packet >> opcode;
                switch(opcode)
                {
                case SERVER_GAME_STATUS:
                {
                    bool game_status;
                    received_packet >> game_status;
                    if(game_status)
                        setup_game();
                    else
                        setup_lobby();
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
                    players.resize(id + 1);
                    lobby.add_player(id + 1);
                    send_player_info();
                    break;
                }
                case SERVER_PLAYER_DISCONNECTED:
                {
                    sf::Uint8 id;
                    received_packet >> id;
                    players.erase(players.begin() + id);
                    lobby.remove_player(id);
                    break;
                }
                case SERVER_PLAYER_READY_STATUS:
                {
                    sf::Uint8 id;
                    bool ready_status;
                    received_packet >> id >> ready_status;
                    players[id].set_ready_status(ready_status);
                    lobby.refresh_player(id, players[id]);
                    break;
                }
                case SERVER_PLAYER_MESSAGE:
                {
                    sf::Uint8 id;
                    std::wstring str;
                    received_packet >> id >> str;
                    lobby.add_chat_message(id, str);
                    break;
                }
                case SERVER_PLAYER_NICKNAME:
                {
                    sf::Uint8 id;
                    std::wstring str;
                    received_packet >> id >> str;
                    players[id].set_nickname(str);
                    lobby.refresh_player(id, players[id]);
                    break;
                }
                case SERVER_PLAYER_TEAM:
                {
                    sf::Uint8 id;
                    sf::Uint8 team;
                    received_packet >> id >> team;
                    players[id].set_team(team);
                    lobby.refresh_player(id, players[id]);
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

void Client_Engine::lobby_logic()
{
    time = clock.restart();

    if(server.get_network_timeout() > sf::seconds(1))
    {
        //setup_menu();//back to menu
        return;
    }
    server.add_network_timeout(time);
}

void Client_Engine::lobby_draw_frame()
{
    window.clear();
    window.draw(resources_manager.get_background());
    lobby.draw();
    window.display();
}

void Client_Engine::lobby_receive_inputs()
{
    sf::Event event;
    while( window.pollEvent(event) )
    {
        switch(event.type)
        {
        case sf::Event::Closed:
        {
            quit_engine();
            break;
        }
        case sf::Event::Resized:
        {
            window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
            break;
        }
        case sf::Event::TextEntered:
        {
            lobby.text_entered(event);
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            lobby.mouse_click(event);
            break;
        }
        case sf::Event::MouseMoved:
        {
            lobby.mouse_move(event);
            break;
        }
        default:
        {
            break;
        }
        }//end switch
    }
}
