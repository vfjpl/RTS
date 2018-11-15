#include "button.hpp"
#include "resources_manager.hpp"
#include <iostream>

extern Resources_Manager resources_manager;

Button::Button(const wchar_t* text, float x, float y)
{
    m_text.setString(text);
    m_text.setFont(resources_manager.get_font());
    m_text.setCharacterSize(24);
    m_text.setPosition(x, y);
    m_text.setFillColor(sf::Color::Black);

    sf::FloatRect rect = m_text.getGlobalBounds();
    m_background.setSize(sf::Vector2f(rect.width+2, rect.height+2));
    m_background.setPosition(rect.left-1, rect.top-1);
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
