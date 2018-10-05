#include "client_resources_manager.hpp"
#include <iostream>

Resources_Manager::Resources_Manager() {}

void Resources_Manager::load_resources()
{
    m_font.loadFromFile("Fonts/font.ttf");
    //TODO: load rest of the files
}

const sf::Font& Resources_Manager::get_font() const
{
    return m_font;
}

void Resources_Manager::debug_show_size() const
{
    //keep up to date!
    std::cout << sizeof(m_font)<< "\n"
              << sizeof(m_czolg) << "\n"
              << sizeof(m_drzewko) << "\n"
              << sizeof(m_drzewko2) << "\n"
              << sizeof(m_grunt) << "\n"
              << sizeof(m_grunt2) << "\n"
              << sizeof(m_test) << "\n"
              << sizeof(m_trawa1) << "\n"
              << sizeof(m_trawa2) << "\n"
              << sizeof(m_trawa3) << "\n";
}
