#ifndef RESOURCES_MANAGER_HPP_INCLUDED
#define RESOURCES_MANAGER_HPP_INCLUDED

#include "SFML/Graphics.hpp"

class Resources_Manager
{
    //sort from largest to smallest!
    sf::Font m_font;//144
    std::vector <sf::Texture> textures;//24

public:
    void load_resources();

    const sf::Font& get_font() const;
    const sf::Texture& get_texture(sf::Uint8 id) const;

    void debug_show_size() const;
};

#endif // RESOURCES_MANAGER_HPP_INCLUDED
