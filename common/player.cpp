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

void Player::set_name(const std::wstring& name)
{
    this->name = name;
}

void Player::set_ready_status(bool status)
{
    this->ready = status;
}

const std::wstring& Player::get_name() const
{
    return name;
}

const sf::IpAddress& Player::get_ip() const
{
    return ip;
}

unsigned short Player::get_port() const
{
    return port;
}

bool Player::get_ready_status() const
{
    return ready;
}

bool Player::compare(const sf::IpAddress& ip, unsigned short port) const
{
    if(this->port == port)
        if(this->ip == ip)
            return true;

    return false;
}
