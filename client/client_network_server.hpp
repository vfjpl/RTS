#ifndef CLIENT_NETWORK_SERVER_HPP_INCLUDED
#define CLIENT_NETWORK_SERVER_HPP_INCLUDED

#include <SFML/Network.hpp>

class Client_Network_Server
{
    //sort from largest to smallest!
    sf::Time m_network_timeout;//8
    sf::IpAddress m_ip;//8
    unsigned short m_port;//2

public:
    Client_Network_Server();
    Client_Network_Server(sf::IpAddress ip, unsigned short port);

    void set_network_timeout(sf::Time network_timeout);
    void set_ip_port(sf::IpAddress ip, unsigned short port);

    sf::Time get_network_timeout() const;
    sf::IpAddress get_ip() const;
    unsigned short get_port() const;

    void add_network_timeout(sf::Time network_timeout);
    bool compare(sf::IpAddress ip, unsigned short port) const;

    void debug_show_size() const;
};

#endif // CLIENT_NETWORK_SERVER_HPP_INCLUDED
