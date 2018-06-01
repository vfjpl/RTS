#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <SFML/Network.hpp>

class Player
{
    //sort from largest to smallest!
    std::wstring m_nickname;//32
    sf::IpAddress m_ip;//8
    unsigned short m_port;//2
    bool m_ready_status = false;//1

public:
    Player();
    Player(sf::IpAddress ip, unsigned short port);
    void set_ip_port(sf::IpAddress ip, unsigned short port);
    void set_nickname(const std::wstring& nickname);
    void set_ready_status(bool ready_status);

    const std::wstring& get_nickname() const;
    sf::IpAddress get_ip() const;
    unsigned short get_port() const;
    bool get_ready_status() const;

    bool compare(sf::IpAddress ip, unsigned short port) const;

    void debug_show_size() const;
};

#endif // PLAYER_HPP_INCLUDED
