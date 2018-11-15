#include "resources_manager.hpp"
#include <iostream>

void Resources_Manager::load_resources()
{
    m_font.loadFromFile("fonts/font.ttf");
    m_textures.resize(12);//number of textures
    m_textures[0].loadFromFile("textures/cb.bmp");
    m_textures[1].loadFromFile("textures/czolg_left.png");
    m_textures[2].loadFromFile("textures/czolg_right.png");
    m_textures[3].loadFromFile("textures/drzewko1.png");
    m_textures[4].loadFromFile("textures/drzewko2.png");
    m_textures[5].loadFromFile("textures/grunt1.png");
    m_textures[6].loadFromFile("textures/grunt2.png");
    m_textures[7].loadFromFile("textures/menu_background.png");
    m_textures[8].loadFromFile("textures/test.png");
    m_textures[9].loadFromFile("textures/trawa1.png");
    m_textures[10].loadFromFile("textures/trawa2.png");
    m_textures[11].loadFromFile("textures/trawa3.png");
    m_background.setTexture(m_textures[7]);
}

const sf::Sprite& Resources_Manager::get_background() const
{
    return m_background;
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
    std::wcout << sizeof(m_background)<< L'\n'
               << sizeof(m_font)<< L'\n'
               << sizeof(m_textures) << L'\n';
}
