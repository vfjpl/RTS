#include "player.hpp"

Player::Player() {}

Player::Player(const sf::IpAddress& ip, unsigned short port)
{
    this->ip = ip;
    this->port = port;
}

void Player::set_ip_port(const sf::IpAddress& ip, unsigned short port)
{
    this->ip = ip;
    this->port = port;
}

sf::IpAddress Player::get_ip() const
{
    return ip;
}

unsigned short Player::get_port() const
{
    return port;
}

bool Player::compare(const sf::IpAddress& ip, unsigned short port)
{
    if(this->port == port)
        if(this->ip == ip)
            return true;

    return false;
}
