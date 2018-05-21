#ifndef NETWORK_CLIENT_HPP_INCLUDED
#define NETWORK_CLIENT_HPP_INCLUDED

#include <SFML/Network.hpp>
#include "../common/player.hpp"

void network_packet_receive(sf::Packet& receive_packet);
void network_menu_packet_receive(sf::Packet& receive_packet, std::vector<Player>& players, bool& quit_menu);

#endif // NETWORK_CLIENT_HPP_INCLUDED
