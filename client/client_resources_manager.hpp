#ifndef CLIENT_RESOURCES_MANAGER_HPP_INCLUDED
#define CLIENT_RESOURCES_MANAGER_HPP_INCLUDED

#include "SFML/Graphics.hpp"

class Resources_Manager
{
    //sort from largest to smallest!
    sf::Font m_font;//144
    sf::Texture m_czolg;//40
    sf::Texture m_drzewko;//40
    sf::Texture m_drzewko2;//40
    sf::Texture m_grunt;//40
    sf::Texture m_grunt2;//40
    sf::Texture m_test;//40
    sf::Texture m_trawa1;//40
    sf::Texture m_trawa2;//40
    sf::Texture m_trawa3;//40

public:
    Resources_Manager();

    const sf::Font& get_font() const;

    void debug_show_size() const;
};

#endif // CLIENT_RESOURCES_MANAGER_HPP_INCLUDED
