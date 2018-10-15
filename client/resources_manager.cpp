#include "resources_manager.hpp"
#include <iostream>

void Resources_Manager::load_resources()
{
    m_font.loadFromFile("Fonts/font.ttf");
    m_textures.resize(10);//number of textures
    m_textures[0].loadFromFile("Textures/cb.bmp");
    //TODO: load rest of the files
}

const sf::Font& Resources_Manager::get_font() const
{
    return m_font;
}

const sf::Texture& Resources_Manager::get_texture(sf::Uint8 id) const
{
    return m_textures[id];
}

void Resources_Manager::debug_show_size() const
{
    //keep up to date!
    std::wcout << sizeof(m_font)<< L"\n"
               << sizeof(m_textures) << L"\n";
}
