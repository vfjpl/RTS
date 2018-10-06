#include "client_resources_manager.hpp"
#include <iostream>

Resources_Manager::Resources_Manager() {}

void Resources_Manager::load_resources()
{
    m_font.loadFromFile("Fonts/font.ttf");
    textures.resize(10);//number of textures
    textures[0].loadFromFile("Textures/cb.bmp");
    //TODO: load rest of the files
}

const sf::Font& Resources_Manager::get_font() const
{
    return m_font;
}

const sf::Texture& Resources_Manager::get_texture(sf::Uint8 id) const
{
    return textures[id];
}

void Resources_Manager::debug_show_size() const
{
    //keep up to date!
    std::cout << sizeof(m_font)<< "\n"
              << sizeof(textures) << "\n";
}
