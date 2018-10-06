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
    Resources_Manager resources_manager;//168
    std::deque <Game_Unit> units;//80
    sf::Packet packet_to_send;//56
    sf::Packet received_packet;//56
    sf::UdpSocket socket;//48
    std::wstring text_buffer;//32
    std::vector <Network_Player> players;//24
    std::vector <sf::Text> texts_to_draw;//24
    Client_Network_Data server;//24
    sf::Clock clock;//8
    sf::Time time;//8
    bool menu_loop = true;//1
    bool lobby_loop = false;//1
    bool game_loop = false;//1

public:
    Client_Engine();

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

    sf::Uint8 get_text_id_from_mousepress(const sf::Event& event) const;
    void set_all_players_ready_status(bool status);

    void setup_menu();
    void menu_chose_options(sf::Uint8 id);
    void menu_receive_inputs_mousepress(const sf::Event& event);
};

#endif // CLIENT_ENGINE_HPP_INCLUDED
