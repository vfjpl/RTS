#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <SFML/Network.hpp>

class player
{
    sf::IpAddress ip;
    unsigned short port;

public:
    player();
    player( sf::IpAddress ip, unsigned short port );
    void set_ip_port( sf::IpAddress ip, unsigned short port );
    sf::IpAddress get_ip() const;
    unsigned short get_port() const;

};

#endif // PLAYER_HPP_INCLUDED
