#ifndef ENGINE_HPP_INCLUDED
#define ENGINE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "network_data.hpp"
#include "../common/network_player.hpp"
#include "../common/game_unit.hpp"
#include <deque>

class Client_Engine
{
    //sort from largest to smallest!
    sf::RenderWindow window;//528
    std::deque <Game_Unit> units;//80
    sf::Packet packet_to_send;//56
    sf::Packet received_packet;//56
    sf::UdpSocket socket;//48
    std::vector <Network_Player> players;//24
    Network_Data server;//24
    sf::Clock clock;//8
    sf::Time time;//8
    bool menu_loop = true;//1
    bool lobby_loop = false;//1
    bool game_loop = false;//1

public:
    void init();

    void menu_receive_inputs();
    void lobby_receive_inputs();
    void game_receive_inputs();

    void menu_logic();
    void lobby_logic();
    void game_logic();

    void receive_packets();
    void draw_frame();
    void send_packets();

    bool get_menu_loop() const;
    bool get_lobby_loop() const;
    bool get_game_loop() const;

    void debug_show_size() const;

private:
    void quit_engine();

    void set_all_players_ready_status(bool status);
};

#endif // ENGINE_HPP_INCLUDED
