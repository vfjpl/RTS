#ifndef LOBBY_SERVER_HPP_INCLUDED
#define LOBBY_SERVER_HPP_INCLUDED

#include <SFML/Network.hpp>
#include "../common/player.hpp"

void lobby_server(sf::UdpSocket& socket, std::vector<Player>& players);

#endif // LOBBY_SERVER_HPP_INCLUDED
