#include "network_data.hpp"
#include <iostream>

Network_Data::Network_Data() {}

Network_Data::Network_Data(sf::IpAddress ip, unsigned short port)
{
    m_ip = ip;
    m_port = port;
}

void Network_Data::set_nickname(const std::wstring& nickname)
{
    m_nickname = nickname;
}

void Network_Data::set_ip_port(sf::IpAddress ip, unsigned short port)
{
    m_ip = ip;
    m_port = port;
}

void Network_Data::set_ip(sf::IpAddress ip)
{
    m_ip = ip;
}

void Network_Data::set_port(unsigned short port)
{
    m_port = port;
}

void Network_Data::set_team(sf::Uint8 team)
{
    m_team = team;
}

void Network_Data::set_ready_status(bool ready_status)
{
    m_ready_status = ready_status;
}

const std::wstring& Network_Data::get_nickname() const
{
    return m_nickname;
}

sf::Time Network_Data::get_network_timeout() const
{
    return m_network_timeout;
}

sf::IpAddress Network_Data::get_ip() const
{
    return m_ip;
}

unsigned short Network_Data::get_port() const
{
    return m_port;
}

sf::Uint8 Network_Data::get_team() const
{
    return m_team;
}

bool Network_Data::get_ready_status() const
{
    return m_ready_status;
}

void Network_Data::reset_network_timeout()
{
    m_network_timeout = sf::Time::Zero;
}

void Network_Data::add_network_timeout(sf::Time network_timeout)
{
    m_network_timeout += network_timeout;
}

bool Network_Data::compare(sf::IpAddress ip, unsigned short port) const
{
    if(m_port == port)
        if(m_ip == ip)
            return true;

    return false;
}

void Network_Data::debug_show_size() const
{
    //keep up to date!
    std::wcout << sizeof(m_nickname) << L'\n'
               << sizeof(m_network_timeout) << L'\n'
               << sizeof(m_ip) << L'\n'
               << sizeof(m_port) << L'\n'
               << sizeof(m_team) << L'\n'
               << sizeof(m_ready_status) << L'\n';
}
