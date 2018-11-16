#include "inputbox.hpp"
#include "resources_manager.hpp"
#include <iostream>

extern Resources_Manager resources_manager;

InputBox::InputBox(unsigned int x, unsigned int y)
{
    m_text.setFont(resources_manager.get_font());
    m_text.setPosition(x, y);
    m_text.setFillColor(sf::Color::Black);

    m_background.setSize(sf::Vector2f(200, 30));
    m_background.setFillColor(sf::Color(255, 255, 255, 191));
    m_background.setPosition(x, y);
}

void InputBox::debug_show_size() const
{
    //keep up to date!
    std::wcout << sizeof(m_text) << L'\n'
               << sizeof(m_background)<< L'\n';
}
