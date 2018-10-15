#include "menu.hpp"
#include "global_variables.hpp"
#include <iostream>

void Menu::main_menu()
{
    m_state = 0;
    m_texts.emplace_back("CONNECT", resources_manager.get_font());
    m_texts.emplace_back("AUTHORS", resources_manager.get_font());
    m_texts[1].move(0, 30);
    m_texts.emplace_back("QUIT", resources_manager.get_font());
    m_texts[2].move(0, 60);
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
    std::cout << sizeof(m_texts)<< "\n"
              << sizeof(m_state) << "\n";
}
