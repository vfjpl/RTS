#ifndef ENGINE_HPP_INCLUDED
#define ENGINE_HPP_INCLUDED

#include "../common/game_unit.hpp"
#include "../common/network_data.hpp"
#include <deque>

class Server_Engine
{
    //sort from largest to smallest!
    std::deque <Game_Unit> units;//80
    std::deque <Network_Data> players;//80
    sf::Packet packet_to_send;//56
    sf::Packet received_packet;//56
    sf::UdpSocket socket;//48
    sf::Clock clock;//8
    sf::Time time;//8
    bool lobby_loop = true;//1
    bool game_loop = false;//1

public:
    void init();

    void lobby_receive_packets();
    void lobby_logic();

    void game_receive_packets();
    void game_logic();

    void send_packets();

    bool get_lobby_loop() const;
    bool get_game_loop() const;

    void debug_show_size() const;

private:
    void setup_game();
    void setup_lobby();

    sf::Uint8 get_player_id(sf::IpAddress ip, unsigned short port) const;
    bool get_ready_status_of_players() const;
    void set_all_players_ready_status(bool status);
    void connect_player(sf::IpAddress ip, unsigned short port);
    void disconnect_player(sf::Uint8 id);
};

#endif // ENGINE_HPP_INCLUDED
