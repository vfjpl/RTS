#ifndef CLIENT_ENGINE_HPP_INCLUDED
#define CLIENT_ENGINE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "client_network_data.hpp"
#include "client_resources_manager.hpp"
#include "../common/network_player.hpp"
#include "../common/game_unit.hpp"
#include <deque>

class Client_Engine
{
    //sort from largest to smallest!
    sf::RenderWindow window;//528
    Resources_Manager resources_manager;//504
    std::deque <Game_Unit> units;//80
    sf::Packet packet_to_send;//56
    sf::Packet received_packet;//56
    sf::UdpSocket socket;//48
    std::wstring text_buffer;//32
    std::vector <Network_Player> players;//24
    Client_Network_Data server;//24
    sf::Clock clock;//8
    sf::Time time;//8
    bool app_loop = true;//1
    bool lobby_loop = false;//1
    bool game_loop = false;//1

public:
    Client_Engine();

    void main_menu();

    void lobby_logic();
    void game_logic();

    void receive_packets();
    void receive_inputs();
    void draw_frame();
    void send_packets();

    bool get_app_loop() const;
    bool get_lobby_loop() const;
    bool get_game_loop() const;

    void debug_show_size() const;

private:
    void set_all_players_ready_status(bool status);
    void receive_inputs_keypress(const sf::Event& event);
    void receive_inputs_mousepress(const sf::Event& event);
};

#endif // CLIENT_ENGINE_HPP_INCLUDED
