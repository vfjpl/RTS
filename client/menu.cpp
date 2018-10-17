#include "menu.hpp"
#include "global_variables.hpp"
#include <iostream>

void Menu::clear()
{
    m_exit = false;
    m_start = false;
    m_state = MENUS_NONE;
    m_texts.clear();
}

void Menu::main_menu()
{
    m_state = MENUS_MAIN_MENU;
    m_texts.clear();
    m_texts.emplace_back(L"CONNECT", resources_manager.get_font());
    m_texts.emplace_back(L"AUTHORS", resources_manager.get_font());
    m_texts[1].move(0, 30);
    m_texts.emplace_back(L"QUIT", resources_manager.get_font());
    m_texts[2].move(0, 60);
}

void Menu::connect_menu()
{
    m_state = MENUS_CONNECT_MENU;
    m_texts.clear();
    //m_texts.emplace_back(server.get_ip().toString(), resources_manager.get_font());
    m_texts.emplace_back(L"CONNECT", resources_manager.get_font());
    m_texts.emplace_back(L"BACK", resources_manager.get_font());
    m_texts[1].move(0, 30);
}

void Menu::add_author_text(sf::String author_name)
{
    const int BUTTONS_NUMBER = 1;
    const int AUTHOR_ID = m_texts.size() - BUTTONS_NUMBER;

    m_texts.emplace_back(author_name, resources_manager.get_font());
    m_texts[m_texts.size() - BUTTONS_NUMBER].move(0, 30 * AUTHOR_ID);
}

void Menu::authors_menu()
{
    m_state = MENUS_AUTHORS_MENU;
    m_texts.clear();
    m_texts.emplace_back(L"BACK", resources_manager.get_font());

    add_author_text(L"Kacper Piwiński");
    add_author_text(L"Radosław Wojdak");

    //Button position
    m_texts[0].move(0, 30 * m_texts.size());
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

void Menu::click(const sf::Event& event)
{
    switch (static_cast<int>(m_state))
    {
        case MENUS_MAIN_MENU:
        {
            switch(get_text_id_from_mousepress(event))
            {
                case Main_Menu_Buttons::MAIN_CONNECT_BUTTON:
                {
                    connect_menu();
                    break;
                }
                case Main_Menu_Buttons::MAIN_AUTHORS_BUTTON:
                {
                    authors_menu();
                    break;
                }
                case Main_Menu_Buttons::MAIN_QUIT_BUTTON:
                {
                    m_exit = true;
                    break;
                }
            }
            break;
        }
        case MENUS_CONNECT_MENU:
        {
            switch(get_text_id_from_mousepress(event))
            {
                case Connect_Menu_Buttons::CONNECT_CONNECT_BUTTON:
                {
                    m_start = true;
                    break;
                }
                case Connect_Menu_Buttons::CONNECT_BACK_BUTTON:
                {
                    main_menu();
                    break;
                }
            }
            break;
        }
        case MENUS_AUTHORS_MENU:
        {
            switch(get_text_id_from_mousepress(event))
            {
                case Authors_Menu_Buttons::AUTHORS_BACK_BUTTON:
                {
                    main_menu();
                    break;
                }
            }
            break;
        }
    }
}

bool Menu::isExiting()
{
    return m_exit;
}

bool Menu::isStarting()
{
    return m_start;
}
