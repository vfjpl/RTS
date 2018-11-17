#include "inputbox.hpp"
#include "resources_manager.hpp"
#include <iostream>

extern Resources_Manager resources_manager;

InputBox::InputBox(unsigned int x, unsigned int y, unsigned int width)
{
    m_text.setFont(resources_manager.get_font());
    m_text.setCharacterSize(14);
    m_text.setFillColor(sf::Color::Black);
    m_text.setPosition(x, y);

    m_background.setFillColor(sf::Color(255, 255, 255, 191));
    m_background.setSize(sf::Vector2f(width, 20));
    m_background.setPosition(x, y);
}

void InputBox::mark()
{
    if(!m_marked)
    {
        m_marked = true;
        std::wstring str(m_text.getString());
        str.push_back(L'|');
        m_text.setString(str);
    }
}

void InputBox::unmark()
{
    if(m_marked)
    {
        m_marked = false;
        std::wstring str(m_text.getString());
        str.pop_back();
        m_text.setString(str);
    }
}

void InputBox::debug_show_size() const
{
    //keep up to date!
    std::wcout << sizeof(m_text) << L'\n'
               << sizeof(m_background) << L'\n'
               << sizeof(m_marked) << L'\n';
}
