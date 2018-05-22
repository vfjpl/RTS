#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <SFML/Network.hpp>

class Player
{
    std::wstring name;
    sf::IpAddress ip;
    unsigned short port;
    bool ready;

public:
    Player();
    Player(const sf::IpAddress& ip, unsigned short port);
    void set_ip_port(const sf::IpAddress& ip, unsigned short port);
    void set_name(const std::wstring& name);
    void set_ready_status(bool status);

    const std::wstring& get_name() const;
    const sf::IpAddress& get_ip() const;
    unsigned short get_port() const;
    bool get_ready_status() const;

    bool compare(const sf::IpAddress& ip, unsigned short port) const;
};

#endif // PLAYER_HPP_INCLUDED
