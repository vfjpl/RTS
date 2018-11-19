#include "lobby.hpp"
#include "resources_manager.hpp"
#include "engine.hpp"
#include "../common/network_data.hpp"
#include <iostream>

#define TEXT_SIZE 15
#define TEXT_GAP 15
#define MARGIN 40

extern sf::RenderWindow window;
extern Resources_Manager resources_manager;
extern Client_Engine engine;
extern Network_Data server;

void Lobby::setup()
{
    m_middle = window.getSize();
    m_buttons.emplace_back(L"DISCONNECT", TEXT_GAP, m_middle.y - MARGIN - TEXT_GAP);
    m_buttons.emplace_back(L"READY",
                           m_buttons.back().m_background.getLocalBounds().width + TEXT_GAP*2,
                           m_middle.y - MARGIN - TEXT_GAP);
    m_middle.x /= 2;
    m_inputboxes.emplace_back(m_middle.x, m_middle.y - MARGIN - TEXT_GAP, m_middle.x - TEXT_GAP);
    m_middle.y /= 2;

    //setup players after game
    add_player(engine.get_number_of_players());
}

void Lobby::clear()
{
    m_middle.x = 0;
    m_middle.y = 0;
    m_buttons.clear();
    m_inputboxes.clear();
    m_players.clear();
    m_chat.clear();
}

void Lobby::mouse_click(const sf::Event& event)
{
    //mark pressed inputbox
    for(sf::Uint8 i = 0; i < m_inputboxes.size(); ++i)
        if(m_inputboxes[i].m_background.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
            m_inputboxes[i].mark();
        else
            m_inputboxes[i].unmark();

    sf::Uint8 button_id = get_button_id_from_press(event);
    if(button_id == m_buttons.size())
        return;//none button is pressed

    switch(button_id)
    {
    case 0://disconnect
    {
        engine.setup_menu();
        break;
    }
    case 1://ready
    {
        engine.send_ready_status(!server.get_ready_status());
        break;
    }
    }//end switch
}

void Lobby::text_entered(const sf::Event& event)
{
    sf::Uint8 marked_inputbox = get_marked_inputbox_id();
    if(marked_inputbox == m_inputboxes.size())
        return;//none inputbox is marked

    switch(event.text.unicode)
    {
    case L'\b'://BackSpace (8)
    {
        std::wstring str(m_inputboxes[marked_inputbox].m_text.getString());
        str.pop_back();
        if(!str.empty())
            str.pop_back();
        str.push_back(L'|');
        m_inputboxes[marked_inputbox].m_text.setString(str);
        break;
    }
    case L'\r'://Enter (13)
    {
        std::wstring str(m_inputboxes[marked_inputbox].m_text.getString());
        str.pop_back();
        engine.send_message(str);
        str.clear();
        str.push_back(L'|');
        m_inputboxes[marked_inputbox].m_text.setString(str);
        break;
    }
    default:
    {
        std::wstring str(m_inputboxes[marked_inputbox].m_text.getString());
        str.pop_back();
        str.push_back(event.text.unicode);
        str.push_back(L'|');
        m_inputboxes[marked_inputbox].m_text.setString(str);
        break;
    }
    }//end switch
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
        m_players.emplace_back(std::to_wstring(i) + L": " + engine.get_player_informations(i).get_nickname(),
                               0,
                               TEXT_GAP*i,
                               TEXT_SIZE);
}

void Lobby::remove_player(sf::Uint8 id)
{
    m_players.erase(m_players.begin() + id);
    for(sf::Uint8 i = id; i < m_players.size(); ++i)
    {
        m_players[i].m_text.setString(std::to_wstring(i) + L": " + engine.get_player_informations(i).get_nickname());
        m_players[i].m_text.setPosition(0, TEXT_GAP*i);
    }
}

void Lobby::refresh_player(sf::Uint8 id)
{
    m_players[id].m_text.setString(std::to_wstring(id) + L": " + engine.get_player_informations(id).get_nickname());
}

void Lobby::add_chat_message(sf::Uint8 id, const std::wstring& message)
{
    if(TEXT_GAP*m_chat.size() > m_middle.y)
    {
        m_chat.pop_front();
        for(sf::Uint8 i = 0; i < m_chat.size(); ++i)
            m_chat[i].m_text.setPosition(m_middle.x, TEXT_GAP*i);
    }
    m_chat.emplace_back(m_players[id].m_text.getString() + L": " + message,
                        m_middle.x,
                        TEXT_GAP*m_chat.size(),
                        TEXT_SIZE);
}

void Lobby::draw()
{
    for(sf::Uint8 i = 0; i < m_buttons.size(); ++i)
    {
        window.draw(m_buttons[i].m_background);
        window.draw(m_buttons[i].m_text);
    }
    for(sf::Uint8 i = 0; i < m_inputboxes.size(); ++i)
    {
        window.draw(m_inputboxes[i].m_background);
        window.draw(m_inputboxes[i].m_text);
    }
    for(sf::Uint8 i = 0; i < m_players.size(); ++i)
        window.draw(m_players[i].m_text);
    for(sf::Uint8 i = 0; i < m_chat.size(); ++i)
        window.draw(m_chat[i].m_text);
}

sf::Uint8 Lobby::get_button_id_from_press(const sf::Event& event) const
{
    for(sf::Uint8 i = 0; i < m_buttons.size(); ++i)
        if(m_buttons[i].m_background.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
            return i;

    return m_buttons.size();
}

sf::Uint8 Lobby::get_marked_inputbox_id() const
{
    for(sf::Uint8 i = 0; i < m_inputboxes.size(); ++i)
        if(m_inputboxes[i].is_marked())
            return i;

    return m_inputboxes.size();
}

void Lobby::debug_show_size() const
{
    //keep up to date!
    std::wcout << sizeof(m_buttons) << L'\n'
               << sizeof(m_players) << L'\n'
               << sizeof(m_chat) << L'\n'
               << sizeof(m_middle) << L'\n';
}
