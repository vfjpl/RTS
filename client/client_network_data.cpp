#include "client_network_data.hpp"
#include <iostream>

Client_Network_Data::Client_Network_Data() {}

Client_Network_Data::Client_Network_Data(sf::IpAddress ip, unsigned short port)
{
    m_ip = ip;
    m_port = port;
}

void Client_Network_Data::set_network_timeout(sf::Time network_timeout)
{
    m_network_timeout = network_timeout;
}

void Client_Network_Data::set_ip_port(sf::IpAddress ip, unsigned short port)
{
    m_ip = ip;
    m_port = port;
}

sf::Time Client_Network_Data::get_network_timeout() const
{
    return m_network_timeout;
}

sf::IpAddress Client_Network_Data::get_ip() const
{
    return m_ip;
}

unsigned short Client_Network_Data::get_port() const
{
    return m_port;
}

void Client_Network_Data::add_network_timeout(sf::Time network_timeout)
{
    m_network_timeout += network_timeout;
}

bool Client_Network_Data::compare(sf::IpAddress ip, unsigned short port) const
{
    if(m_port == port)
        if(m_ip == ip)
            return true;

    return false;
}

void Client_Network_Data::debug_show_size() const
{
    //keep up to date!
    std::cout << sizeof(m_network_timeout) << "\n"
              << sizeof(m_ip) << "\n"
              << sizeof(m_port) << "\n";
}
