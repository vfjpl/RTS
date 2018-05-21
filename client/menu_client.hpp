#ifndef MENU_CLIENT_HPP_INCLUDED
#define MENU_CLIENT_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

void menu_temp(sf::RenderWindow& win, sf::UdpSocket& socket, const sf::IpAddress& r_ip, unsigned short r_port);

#endif // MENU_CLIENT_HPP_INCLUDED
