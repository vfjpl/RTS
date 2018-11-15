#include "lobby.hpp"
#include "resources_manager.hpp"
#include "engine.hpp"
#include <iostream>

extern sf::RenderWindow window;
extern Resources_Manager resources_manager;
extern Client_Engine engine;

void Lobby::setup()
{
    m_middle = window.getSize();
    m_buttons.emplace_back(L"DISCONNECT", 15, m_middle.y - 45);
    m_buttons.emplace_back(L"READY", m_buttons.back().m_text.getLocalBounds().width + 30, m_middle.y - 45);
    m_middle.x /= 2;
    m_middle.y /= 2;
}

void Lobby::clear()
{
    m_middle.x = 0;
    m_middle.y = 0;
    m_buttons.clear();
    m_players.clear();
    m_chat.clear();
}

void Lobby::mouse_click(const sf::Event& event)
{
    sf::Uint8 button_id = get_button_id_from_press(event);
    switch(button_id)
    {
    case 0://disconnect
    {
        engine.setup_menu();
        break;
    }
    case 1://ready
    {
        engine.send_ready_status(true);
        break;
    }
    }//end switch
}

void Lobby::text_entered(const sf::Event& event)
{

}

void Lobby::mouse_move(const sf::Event& event)
{
    for(sf::Uint8 i = 0; i < m_buttons.size(); ++i)
        if(m_buttons[i].m_background.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
            m_buttons[i].mark();
        else
            m_buttons[i].unmark();
}

void Lobby::add_player(sf::Uint8 id)
{
    for(sf::Uint8 i = m_players.size(); i < id; ++i)
    {
        m_players.emplace_back(std::to_wstring(i), resources_manager.get_font());
        m_players[i].setPosition(0, i*30);
    }
}

void Lobby::remove_player(sf::Uint8 id)
{
    m_players.erase(m_players.begin() + id);
    for(sf::Uint8 i = id; i < m_players.size(); ++i)
    {
        m_players[i].setString(std::to_wstring(i));
        m_players[i].setPosition(0, i*30);
    }
}

void Lobby::refresh_player(sf::Uint8 id, const Network_Player& player)
{
    std::wstring str(std::to_wstring(id));
    str.append(L" ");
    str.append(player.get_nickname());
    str.append(L" ");
    if(player.get_ready_status())
        str.append(L"READY");
    else
        str.append(L"NOT READY");
    m_players[id].setString(str);
}

void Lobby::add_chat_message(const std::wstring& message)
{
    m_chat.emplace_back(message, resources_manager.get_font());
    m_chat.back().setPosition(m_middle.x, m_chat.size()*30);
}

void Lobby::draw()
{
    for(sf::Uint8 i = 0; i < m_buttons.size(); ++i)
    {
        window.draw(m_buttons[i].m_background);
        window.draw(m_buttons[i].m_text);
    }
    for(sf::Uint8 i = 0; i < m_players.size(); ++i)
        window.draw(m_players[i]);
    for(sf::Uint8 i = 0; i < m_chat.size(); ++i)
        window.draw(m_chat[i]);
}

sf::Uint8 Lobby::get_button_id_from_press(const sf::Event& event) const
{
    for(sf::Uint8 i = 0; i < m_buttons.size(); ++i)
        if(m_buttons[i].m_background.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
            return i;

    return m_buttons.size();
}

void Lobby::debug_show_size() const
{
    //keep up to date!
    std::wcout << sizeof(m_buttons)<< L'\n'
               << sizeof(m_players)<< L'\n'
               << sizeof(m_chat)<< L'\n'
               << sizeof(m_middle)<< L'\n';
}
