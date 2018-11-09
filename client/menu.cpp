#include "menu.hpp"
#include "engine.hpp"
#include "resources_manager.hpp"
#include "network_data.hpp"
#include <iostream>

extern Client_Engine engine;
extern Resources_Manager resources_manager;
extern Network_Data server;

void Menu::init(const sf::RenderWindow& window)
{
    main_menu(window);
}

void Menu::clear()
{
    m_state = 0;
    m_texts.clear();
    m_buttons.clear();
}

void Menu::main_menu(const sf::RenderWindow& window)
{
    clear();
    m_state = 1;
    
    const int BUTTONS_POSITION_X = window.getSize().x / 2 - STANDARD_BUTTON_SIZE.x / 2;

    m_buttons.emplace_back(sf::Vector2f(BUTTONS_POSITION_X, 64.0f),  L"CONNECT");
    m_buttons.emplace_back(sf::Vector2f(BUTTONS_POSITION_X, 128.0f), L"OPTIONS");
    m_buttons.emplace_back(sf::Vector2f(BUTTONS_POSITION_X, 192.0f), L"AUTHORS");
    m_buttons.emplace_back(sf::Vector2f(BUTTONS_POSITION_X, 256.0f), L"QUIT");
}

void Menu::connect_menu(const sf::RenderWindow& window)
{
    clear();
    m_state = 2;
    
    const int BUTTONS_POSITION_X = window.getSize().x / 2 - STANDARD_BUTTON_SIZE.x / 2;

    m_buttons.emplace_back(sf::Vector2f(BUTTONS_POSITION_X, 64.0f),  server.get_ip().toString());
    m_buttons.emplace_back(sf::Vector2f(BUTTONS_POSITION_X, 128.0f), L"OPTIONS");
    m_buttons.emplace_back(sf::Vector2f(BUTTONS_POSITION_X, 192.0f), L"BACK");
}

void Menu::options_menu(const sf::RenderWindow& window)
{
    clear();
    m_state = 3;
    
    const int BUTTONS_POSITION_X = window.getSize().x / 2 - STANDARD_BUTTON_SIZE.x / 2;

    m_buttons.emplace_back(sf::Vector2f(BUTTONS_POSITION_X, 64.0f),  L"FULLSCREEN");
    m_buttons.emplace_back(sf::Vector2f(BUTTONS_POSITION_X, 128.0f), L"WINDOWED");
    m_buttons.emplace_back(sf::Vector2f(BUTTONS_POSITION_X, 192.0f), L"BACK");
}

void Menu::authors_menu(const sf::RenderWindow& window)
{
    clear();
    m_state = 4;

    m_texts.emplace_back(L"Kacper Piwiński", resources_manager.get_font());
    m_texts.emplace_back(L"Radosław Wojdak", resources_manager.get_font());
    m_texts[1].move(0, 30);
    
    const int BUTTONS_POSITION_X = window.getSize().x / 2 - STANDARD_BUTTON_SIZE.x / 2;

    m_buttons.emplace_back(sf::Vector2f(BUTTONS_POSITION_X, 192.0f), L"BACK");
}

void Menu::mouse_click(const sf::RenderWindow& window)
{
    sf::Uint8 button_id = get_button_id_from_press(window);
    switch(m_state)
    {
    case 1://main menu
    {
        switch(button_id)
        {
        case 0://connect
        {
            connect_menu(window);
            break;
        }
        case 1://options
        {
            options_menu(window);
            break;
        }
        case 2://authors
        {
            authors_menu(window);
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
        case 0://IpAddress
        {
            m_buttons[0].set_string(std::wstring());
            break;
        }
        case 1://connect
        {
            server.set_ip(sf::IpAddress(m_buttons[0].get_string()));
            engine.connect_to_lobby();
            break;
        }
        case 2://back
        {
            main_menu(window);
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
            break;
        }
        case 1://windowed
        {
            engine.setup_window(false);
            break;
        }
        case 2://back
        {
            main_menu(window);
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
            main_menu(window);
            break;
        }
        }//end switch
        break;
    }
    }//end switch
}

void Menu::mouse_move(const sf::RenderWindow& window)
{
    for(Button& button : m_buttons)
    {
        if (button.is_mouse_on(window))
            button.mark();
        else
            button.unmark();
    }
}

void Menu::text_entered(const sf::Event& event)
{
    if(m_state == 2)
    {
        std::wstring str(m_texts[0].getString());
        str.push_back(event.text.unicode);
        m_texts[0].setString(str);
    }
}

void Menu::draw(sf::RenderWindow& window)
{
    for(sf::Text& text : m_texts)
        window.draw(text);

    for(Button& button : m_buttons)
        button.display(window);
}

sf::Uint8 Menu::get_button_id_from_press(const sf::RenderWindow& window) const
{
    for(sf::Uint8 i = 0; i < m_buttons.size(); ++i)
        if(m_buttons[i].is_pressed(window))
            return i;

    return m_buttons.size();
}

void Menu::debug_show_size() const
{
    //keep up to date!
    std::wcout << sizeof(m_buttons) << L'\n'
               << sizeof(m_texts)   << L'\n'
               << sizeof(m_state)   << L'\n';
}
