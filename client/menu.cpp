#include "menu.hpp"
#include "resources_manager.hpp"
#include "engine.hpp"
#include "network_data.hpp"
#include <iostream>

#define TEXT_GAP 37

extern sf::RenderWindow window;
extern Resources_Manager resources_manager;
extern Client_Engine engine;
extern Network_Data server;

void Menu::setup()
{
    m_middle = window.getSize();
    m_middle.x /= 2;
    m_middle.y /= 2;
    main_menu();
}

void Menu::clear()
{
    m_state = 0;
    m_middle.x = 0;
    m_middle.y = 0;
    m_buttons.clear();
    m_texts.clear();
}

void Menu::main_menu()
{
    m_state = 1;
    m_buttons.clear();
    m_texts.clear();

    //buttons
    m_buttons.emplace_back(L"CONNECT", m_middle.x, m_middle.y + TEXT_GAP);
    m_buttons.emplace_back(L"OPTIONS", m_middle.x, m_middle.y + (TEXT_GAP*2));
    m_buttons.emplace_back(L"AUTHORS", m_middle.x, m_middle.y + (TEXT_GAP*3));
    m_buttons.emplace_back(L"QUIT", m_middle.x, m_middle.y + (TEXT_GAP*4));

    //texts
    m_texts.emplace_back(L"kelajno", resources_manager.get_font());
    m_texts.back().setPosition(m_middle.x, m_middle.y);
}

void Menu::connect_menu()
{
    m_state = 2;
    m_buttons.clear();
    m_texts.clear();

    //buttons
    m_buttons.emplace_back(L"CONNECT", m_middle.x, m_middle.y + TEXT_GAP);
    m_buttons.emplace_back(L"BACK", m_middle.x, m_middle.y + (TEXT_GAP*2));

    //texts
    m_texts.emplace_back(server.get_ip().toString(), resources_manager.get_font());
    m_texts.back().setPosition(m_middle.x, m_middle.y);
}

void Menu::options_menu()
{
    m_state = 3;
    m_buttons.clear();
    m_texts.clear();

    //buttons
    m_buttons.emplace_back(L"FULLSCREEN", m_middle.x, m_middle.y);
    m_buttons.emplace_back(L"WINDOWED", m_middle.x, m_middle.y + TEXT_GAP);
    m_buttons.emplace_back(L"BACK", m_middle.x, m_middle.y + (TEXT_GAP*2));
}

void Menu::authors_menu()
{
    m_state = 4;
    m_buttons.clear();
    m_texts.clear();

    //buttons
    m_buttons.emplace_back(L"BACK", m_middle.x, m_middle.y + (TEXT_GAP*3));

    //texts
    m_texts.emplace_back(L"Kacper Piwiński", resources_manager.get_font());
    m_texts.back().setPosition(m_middle.x, m_middle.y);
    m_texts.emplace_back(L"Radosław Wojdak", resources_manager.get_font());
    m_texts.back().setPosition(m_middle.x, m_middle.y + TEXT_GAP);
    m_texts.emplace_back(L"Robert Kamiński", resources_manager.get_font());
    m_texts.back().setPosition(m_middle.x, m_middle.y + (TEXT_GAP*2));
}

void Menu::mouse_click(const sf::Event& event)
{
    sf::Uint8 button_id = get_button_id_from_press(event);
    switch(m_state)
    {
    case 1://main menu
    {
        switch(button_id)
        {
        case 0://connect
        {
            connect_menu();
            break;
        }
        case 1://options
        {
            options_menu();
            break;
        }
        case 2://authors
        {
            authors_menu();
            break;
        }
        case 3://quit
        {
            engine.quit_engine();
            break;
        }
        }//end switch
        break;
    }
    case 2://connect menu
    {
        switch(button_id)
        {
        case 0://connect
        {
            server.set_ip(sf::IpAddress(m_texts[0].getString()));
            engine.setup_lobby();
            break;
        }
        case 1://back
        {
            main_menu();
            break;
        }
        }//end switch
        break;
    }
    case 3://options
    {
        switch(button_id)
        {
        case 0://fullscreen
        {
            engine.setup_window(true);
            setup();
            break;
        }
        case 1://windowed
        {
            engine.setup_window(false);
            setup();
            break;
        }
        case 2://back
        {
            main_menu();
            break;
        }
        }//end switch
        break;
    }
    case 4://authors menu
    {
        switch(button_id)
        {
        case 0://back
        {
            main_menu();
            break;
        }
        }//end switch
        break;
    }
    }//end switch
}

void Menu::text_entered(const sf::Event& event)
{
    if(m_state != 2)//not in connecting state
        return;

    std::wstring str(m_texts[0].getString());
    switch(event.text.unicode)
    {
    case L'\b'://BackSpace (8)
    {
        if(!str.empty())
            str.pop_back();
        break;
    }
    case L'\r'://Enter (13)
    {
        server.set_ip(sf::IpAddress(m_texts[0].getString()));
        engine.setup_lobby();
        break;
    }
    default:
    {
        str.push_back(event.text.unicode);
        break;
    }
    }//end switch
    m_texts[0].setString(str);
}

void Menu::mouse_move(const sf::Event& event)
{
    for(sf::Uint8 i = 0; i < m_buttons.size(); ++i)
        if(m_buttons[i].m_background.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
            m_buttons[i].mark();
        else
            m_buttons[i].unmark();
}

void Menu::logic()
{
    sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
    for(sf::Uint8 i = 0; i < m_buttons.size(); ++i)
        if(m_buttons[i].m_background.getGlobalBounds().contains(mouse_position.x, mouse_position.y))
            m_buttons[i].mark();
        else
            m_buttons[i].unmark();
}

void Menu::draw()
{
    for(sf::Uint8 i = 0; i < m_buttons.size(); ++i)
    {
        window.draw(m_buttons[i].m_background);
        window.draw(m_buttons[i].m_text);
    }
    for(sf::Uint8 i = 0; i < m_texts.size(); ++i)
        window.draw(m_texts[i]);
}

sf::Uint8 Menu::get_button_id_from_press(const sf::Event& event) const
{
    for(sf::Uint8 i = 0; i < m_buttons.size(); ++i)
        if(m_buttons[i].m_background.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
            return i;

    return m_buttons.size();
}

void Menu::debug_show_size() const
{
    //keep up to date!
    std::wcout << sizeof(m_buttons)<< L'\n'
               << sizeof(m_texts)<< L'\n'
               << sizeof(m_middle)<< L'\n'
               << sizeof(m_state) << L'\n';
}
