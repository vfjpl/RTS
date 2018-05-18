#ifndef PACKET_HANDLING_HPP_INCLUDED
#define PACKET_HANDLING_HPP_INCLUDED

#include <SFML/Network.hpp>
#include "../common/player.hpp"

void network_packet_receive(sf::Packet &receive_packet);
void network_players_init(sf::UdpSocket &socket, player *players, sf::Uint8 number_of_players);

#endif // PACKET_HANDLING_HPP_INCLUDED
