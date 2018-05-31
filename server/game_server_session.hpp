#ifndef GAME_SERVER_SESSION_HPP_INCLUDED
#define GAME_SERVER_SESSION_HPP_INCLUDED

#include <SFML/Network.hpp>
#include "../common/player.hpp"

class Game_Server_Session
{
    //sort from largest to smallest!
    sf::Packet packet_to_send;//56
    sf::Packet received_packet;//56
    sf::UdpSocket socket;//48
    std::vector<Player> players;//24
    sf::Clock clock;//8
    sf::Time time;//8
    bool app_loop = true;//1
    bool game_loop = false;//1

public:
    Game_Server_Session();

    void lobby_receive_packets();
    void receive_packets();
    void send_packets();
    void lobby_logic();
    void game_logic();

    bool get_app_loop() const;
    bool get_game_loop() const;

    void debug_show_size() const;
};

#endif // GAME_SERVER_SESSION_HPP_INCLUDED
