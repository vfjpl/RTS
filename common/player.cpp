#include "player.hpp"

player::player() {}

player::player( sf::IpAddress ip, unsigned short port )
{
    this->ip = ip;
    this->port = port;
}

void player::set_ip_port( sf::IpAddress ip, unsigned short port )
{
    this->ip = ip;
    this->port = port;
}

sf::IpAddress player::get_ip() const
{
    return ip;
}

unsigned short player::get_port() const
{
    return port;
}
