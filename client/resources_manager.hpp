#ifndef RESOURCES_MANAGER_HPP_INCLUDED
#define RESOURCES_MANAGER_HPP_INCLUDED

#include "SFML/Graphics.hpp"
#include <deque>

class Resources_Manager
{
    //sort from largest to smallest!
    sf::Sprite m_background;//288
    sf::Font m_font;//144
    std::deque <sf::Texture> m_textures;//80

public:
    void load_resources();

    const sf::Sprite& get_background() const;
    const sf::Font& get_font() const;
    const sf::Texture& get_texture(sf::Uint8 id) const;

    void debug_show_size() const;
};

#endif // RESOURCES_MANAGER_HPP_INCLUDED
