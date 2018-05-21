#ifndef MENU_CLIENT_HPP_INCLUDED
#define MENU_CLIENT_HPP_INCLUDED

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "../common/player.hpp"

void menu_temp(sf::RenderWindow& win, sf::UdpSocket& socket, std::vector<Player>& players,
               const sf::IpAddress& remote_ip, unsigned short remote_port);

#endif // MENU_CLIENT_HPP_INCLUDED
