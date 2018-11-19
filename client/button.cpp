#include "button.hpp"
#include "resources_manager.hpp"
#include <iostream>

extern Resources_Manager resources_manager;

Button::Button(const wchar_t* text, unsigned int x, unsigned int y)
{
    m_text.setString(text);
    m_text.setFont(resources_manager.get_font());
    m_text.setFillColor(sf::Color::Black);
    m_text.setPosition(x+1, y);

    sf::FloatRect rect = m_text.getLocalBounds();
    m_background.setSize(sf::Vector2f(rect.width+4, 40));// 4/3
    m_background.setPosition(x, y);
}

Button::Button(const wchar_t* text, unsigned int x, unsigned int y, unsigned int width)
{
    m_text.setString(text);
    m_text.setFont(resources_manager.get_font());
    m_text.setFillColor(sf::Color::Black);
    m_text.setPosition(x+1, y);

    m_background.setSize(sf::Vector2f(width, 40));// 4/3
    m_background.setPosition(x, y);
}

void Button::mark()
{
    m_text.setFillColor(sf::Color::Green);
}

void Button::unmark()
{
    m_text.setFillColor(sf::Color::Black);
}

void Button::debug_show_size() const
{
    //keep up to date!
    std::wcout << sizeof(m_text) << L'\n'
               << sizeof(m_background)<< L'\n';
}
