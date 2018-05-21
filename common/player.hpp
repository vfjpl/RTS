#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <SFML/Network.hpp>

class Player
{
    sf::IpAddress ip;
    unsigned short port;

public:
    Player();
    Player(const sf::IpAddress& ip, unsigned short port);
    void set_ip_port(const sf::IpAddress& ip, unsigned short port);
    sf::IpAddress get_ip() const;
    unsigned short get_port() const;

    bool compare(const sf::IpAddress& ip, unsigned short port);

};

#endif // PLAYER_HPP_INCLUDED
