#include "menu.hpp"
#include "global_variables.hpp"
#include <iostream>

void Menu::clear()
{
    m_state = 0;
    m_texts.clear();
}

void Menu::main_menu()
{
    m_state = 1;
    m_texts.clear();
    m_texts.emplace_back(L"CONNECT", resources_manager.get_font());
    m_texts.emplace_back(L"AUTHORS", resources_manager.get_font());
    m_texts[1].move(0, 30);
    m_texts.emplace_back(L"QUIT", resources_manager.get_font());
    m_texts[2].move(0, 60);
}

void Menu::connect_menu()
{
    m_state = 2;
    m_texts.clear();
    //m_texts.emplace_back(server.get_ip().toString(), resources_manager.get_font());
    m_texts.emplace_back(L"CONNECT", resources_manager.get_font());
    m_texts[1].move(0, 30);
    m_texts.emplace_back(L"BACK", resources_manager.get_font());
    m_texts[2].move(0, 60);
}

void Menu::authors_menu()
{
    m_state = 3;
    m_texts.clear();
    m_texts.emplace_back(L"Kacper Piwiński", resources_manager.get_font());
    m_texts.emplace_back(L"BACK", resources_manager.get_font());
    m_texts[1].move(0, 30);
}

void Menu::draw(sf::RenderWindow& window)
{
    for(sf::Uint8 i = 0; i < m_texts.size(); ++i)
        window.draw(m_texts[i]);
}

sf::Uint8 Menu::get_text_id_from_mousepress(const sf::Event& event) const
{
    for(sf::Uint8 i = 0; i < m_texts.size(); ++i)
        if(m_texts[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
            return i;

    return m_texts.size();
}

void Menu::debug_show_size() const
{
    //keep up to date!
    std::wcout << sizeof(m_texts)<< L"\n"
               << sizeof(m_state) << L"\n";
}
