#ifndef NETWORK_SERVER_HPP_INCLUDED
#define NETWORK_SERVER_HPP_INCLUDED

#include <SFML/Network.hpp>
#include "../common/player.hpp"

void network_packet_receive(sf::Packet& receive_packet);
void network_lobby_packet_receive(sf::Packet& receive_packet, sf::Packet& send_packet, std::vector<Player>& players,
                                  const sf::IpAddress& ip, unsigned short port);

#endif // NETWORK_SERVER_HPP_INCLUDED
