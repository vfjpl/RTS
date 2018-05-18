#include "player.hpp"

player::player() {}

player::player( sf::IpAddress ip, unsigned short port )
{
    this->ip = ip;
    this->port = port;
}

sf::IpAddress player::get_ip()
{
    return ip;
}

unsigned short player::get_port()
{
    return port;
}
