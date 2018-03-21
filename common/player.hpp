#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <SFML/Network.hpp>

class player
{
    sf::Uint16 port;
    sf::IpAddress ip;

public:
    player( sf::IpAddress ip, sf::Uint16 port );

};

#endif // PLAYER_HPP_INCLUDED
