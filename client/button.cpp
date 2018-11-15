#include "button.hpp"
#include "resources_manager.hpp"
#include <iostream>

extern Resources_Manager resources_manager;

Button::Button(const wchar_t* text, unsigned int x, unsigned int y)
{
    m_text.setString(text);
    m_text.setFont(resources_manager.get_font());
    m_text.setPosition(x, y);
    m_text.setFillColor(sf::Color::Black);

    sf::FloatRect rect = m_text.getGlobalBounds();
    m_background.setSize(sf::Vector2f(rect.width+6, rect.height+6));
    m_background.setPosition(rect.left-3, rect.top-3);
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
