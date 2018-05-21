#ifndef NETWORK_SERVER_HPP_INCLUDED
#define NETWORK_SERVER_HPP_INCLUDED

#include <SFML/Network.hpp>
#include "../common/player.hpp"

void network_packet_receive(sf::Packet& receive_packet);
void network_lobby_packet_receive(sf::Packet& receive, sf::Packet& send, sf::Uint8& current, Player* p_tab,
                                  const sf::IpAddress& ip, unsigned short port, bool* ready_table);

#endif // NETWORK_SERVER_HPP_INCLUDED
