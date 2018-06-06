#include "game_server_session.hpp"
#include "../common/network_opcodes.hpp"
#include <iostream>

Game_Server_Session::Game_Server_Session()
{
    socket.bind(7000);
}

void Game_Server_Session::lobby_logic()
{
    time = clock.restart();

    bool ready = true;
    for(sf::Uint8 i = 0; i < players.size(); )
    {
        if(players[i].get_network_timeout().asSeconds() > 1)//timeout disconnect
        {
            ready = false;//to prevent auto staring when last non ready player timeout disconnect
            players.erase(players.begin() + i);
            packet_to_send << (sf::Uint8)SERVER_PLAYER_DISCONNECTED << i;

            for(sf::Uint8 i = 0; i < players.size(); ++i)//to prevent auto starting
            {
                if(players[i].get_ready_status())
                {
                    players[i].set_ready_status(false);
                    packet_to_send<<(sf::Uint8)SERVER_PLAYER_READY_STATUS<<i<<false;
                }
            }
            continue;
        }

        ready &= players[i].get_ready_status();//ready true only if all players are ready
        players[i].set_network_timeout(players[i].get_network_timeout() + time);
        ++i;
    }

    if( ready && players.size() > 0 )//to prevent starting when there are no players in lobby
    {
        game_loop = true;
        packet_to_send << (sf::Uint8)SERVER_START_GAME;
        for(sf::Uint8 i = 0; i < players.size(); ++i)//reset ready status after game started
            players[i].set_ready_status(false);
    }
}

void Game_Server_Session::game_logic()
{
    time = clock.restart();

    for(sf::Uint8 i = 0; i < players.size(); )
    {
        if(players[i].get_network_timeout().asSeconds() > 1)//timeout disconnect
        {
            players.erase(players.begin() + i);
            packet_to_send << (sf::Uint8)SERVER_PLAYER_DISCONNECTED << i;
            continue;
        }

        players[i].set_network_timeout(players[i].get_network_timeout() + time);
        ++i;
    }

    //for the test
    packet_to_send<<(sf::Uint8)SERVER_STOP_GAME;
    game_loop = false;
}

void Game_Server_Session::receive_packets()
{
    sf::IpAddress incomming_ip;
    unsigned short incomming_port;
    sf::Uint8 opcode;
    sf::Uint8 local_id;
    for(sf::Uint8 i = 0; i <= players.size(); ++i)//[ <= ]because we are waiting for more players
    {
        socket.receive( received_packet, incomming_ip, incomming_port );
        local_id = get_player_id(incomming_ip, incomming_port);
        while( !received_packet.endOfPacket() )
        {
            received_packet >> opcode;
            switch( opcode )
            {
            case JOIN_GAME:
            {
                local_id = players.size();
                players.emplace_back(incomming_ip, incomming_port);
                packet_to_send<<(sf::Uint8)SERVER_PLAYER_CONNECTED<<local_id;
                break;
            }
            case DISCONNECT:
            {
                players.erase(players.begin() + local_id);
                packet_to_send<<(sf::Uint8)SERVER_PLAYER_DISCONNECTED<<local_id;

                for(sf::Uint8 i = 0; i < players.size(); ++i)//to prevent auto starting
                {
                    if(players[i].get_ready_status())
                    {
                        players[i].set_ready_status(false);
                        packet_to_send<<(sf::Uint8)SERVER_PLAYER_READY_STATUS<<i<<false;
                    }
                }
                break;
            }
            case SET_READY_STATUS:
            {
                bool ready_status;
                received_packet >> ready_status;
                players[local_id].set_ready_status(ready_status);
                packet_to_send<<(sf::Uint8)SERVER_PLAYER_READY_STATUS<<local_id<<ready_status;
                break;
            }
            case SEND_MESSAGE:
            {
                std::wstring str;
                received_packet >> str;
                packet_to_send<<(sf::Uint8)SERVER_PLAYER_MESSAGE<<local_id<<str;
                break;
            }
            case SET_NICKNAME:
            {
                std::wstring str;
                received_packet >> str;
                players[local_id].set_nickname(str);
                packet_to_send<<(sf::Uint8)SERVER_PLAYER_NICKNAME<<local_id<<str;
                break;
            }
            default:
            {
                received_packet.clear();
                break;
            }
            }//end switch
        }//end while
        players[local_id].set_network_timeout( sf::Time::Zero );
    }//end for
}

void Game_Server_Session::send_packets()
{
    for(sf::Uint8 i = 0; i < players.size(); ++i)
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
    for(sf::Uint8 i = 0; i < players.size(); ++i)
        if(players[i].compare(ip,port))
            return i;

    return 255;//if there is no connected player with this ip and port
}

void Game_Server_Session::debug_show_size() const
{
    //keep up to date!
    std::cout << sizeof(units) << "\n"
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
