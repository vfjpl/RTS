#ifndef GAME_CLIENT_SESSION_HPP_INCLUDED
#define GAME_CLIENT_SESSION_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "../common/network_data.hpp"
#include "../common/game_unit.hpp"
#include <deque>

class Client_Engine
{
    //sort from largest to smallest!
    sf::RenderWindow window;//528
    std::deque<Game_Unit> units;//80
    Network_Data server;//56
    sf::Packet packet_to_send;//56
    sf::Packet received_packet;//56
    sf::UdpSocket socket;//48
    std::vector<Network_Data> players;//24
    sf::Clock clock;//8
    sf::Time time;//8
    bool app_loop = true;//1
    bool game_loop = false;//1

public:
    Client_Engine();

    void lobby_receive_inputs();
    void lobby_logic();
    void lobby_draw_frame();

    void game_receive_inputs();
    void game_logic();
    void game_draw_frame();

    void receive_packets();
    void send_packets();
    bool get_app_loop() const;
    bool get_game_loop() const;

    void debug_show_size() const;

private:
    void set_all_players_ready_status(bool status);
    void game_receive_inputs_keypress(const sf::Event& event);
    void game_receive_inputs_mousepress(const sf::Event& event);
};

#endif // GAME_CLIENT_SESSION_HPP_INCLUDED
