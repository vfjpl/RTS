#include "text.hpp"
#include "resources_manager.hpp"
#include <iostream>

extern Resources_Manager resources_manager;

Text::Text(const wchar_t* text, unsigned int x, unsigned int y)
{
    m_text.setString(text);
    m_text.setFont(resources_manager.get_font());
    m_text.setPosition(x, y);
}

Text::Text(const std::wstring& text, unsigned int x, unsigned int y)
{
    m_text.setString(text);
    m_text.setFont(resources_manager.get_font());
    m_text.setPosition(x, y);
}

void Text::debug_show_size() const
{
    //keep up to date!
    std::wcout << sizeof(m_text) << L'\n';
}
