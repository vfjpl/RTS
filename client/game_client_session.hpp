#ifndef GAME_CLIENT_SESSION_HPP_INCLUDED
#define GAME_CLIENT_SESSION_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "../common/player.hpp"

class Game_Client_Session
{
    //sort from largest to smallest!
    sf::RenderWindow window;//528
    sf::Packet packet_to_send;//56
    sf::Packet received_packet;//56
    sf::UdpSocket socket;//48
    std::vector<Player> players;//24
    sf::Event event;//20
    sf::Clock clock;//8
    sf::Time time;//8
    sf::IpAddress remote_ip = "localhost";//8
    unsigned short remote_port = 7000;//2
    bool app_loop = true;//1
    bool game_loop = false;//1

public:
    Game_Client_Session();

    void lobby_receive_packets();
    void lobby_receive_inputs();
    void lobby_logic();
    void lobby_draw_frame();

    void game_receive_packets();
    void game_receive_inputs();
    void game_logic();
    void game_draw_frame();

    void send_packets();
    bool get_app_loop() const;
    bool get_game_loop() const;

    void debug_show_size() const;

private:
    void game_receive_inputs_keypress();
    void game_receive_inputs_mousepress();
};

#endif // GAME_CLIENT_SESSION_HPP_INCLUDED
