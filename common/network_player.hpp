#ifndef NETWORK_PLAYER_HPP_INCLUDED
#define NETWORK_PLAYER_HPP_INCLUDED

#include <SFML/Network.hpp>

class Network_Player
{
    //sort from largest to smallest!
    std::wstring m_nickname;//32
    sf::Time m_network_timeout;//8
    sf::IpAddress m_ip;//8
    unsigned short m_port;//2
    sf::Uint8 m_team;//1
    bool m_ready_status = false;//1

public:
    Network_Player();
    Network_Player(sf::IpAddress ip, unsigned short port);
    Network_Player(bool ready_status);

    void set_network_timeout(sf::Time network_timeout);
    void set_ip_port(sf::IpAddress ip, unsigned short port);
    void set_nickname(const std::wstring& nickname);
    void set_ready_status(bool ready_status);
    void set_team(sf::Uint8 team);

    sf::Time get_network_timeout() const;
    sf::IpAddress get_ip() const;
    unsigned short get_port() const;
    const std::wstring& get_nickname() const;
    bool get_ready_status() const;
    sf::Uint8 get_team() const;

    void add_network_timeout(sf::Time network_timeout);
    bool compare(sf::IpAddress ip, unsigned short port) const;

    void debug_show_size() const;
};

#endif // NETWORK_PLAYER_HPP_INCLUDED
