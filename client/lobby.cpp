#include "lobby.hpp"
#include "engine.hpp"
#include "resources_manager.hpp"
#include <iostream>

extern Client_Engine engine;
extern Resources_Manager resources_manager;

void Lobby::init(const sf::RenderWindow& window)
{
    background.setTexture(resources_manager.get_texture(10));
    create_gui(window);

    const int TEMPORARY_EXAMPLE_PLAYER_ID = 42;
    const sf::String TEMPORARY_EXAMPLE_PLAYER_NAME = L"Me";
    join_player(TEMPORARY_EXAMPLE_PLAYER_ID, TEMPORARY_EXAMPLE_PLAYER_NAME);
}

void Lobby::clear()
{
    m_buttons.clear();
    m_players.clear();
    m_players_id.clear();
    m_texts.clear();
}

void Lobby::create_gui(const sf::RenderWindow& window)
{
    clear();

    const int CHAT_WINDOW_MARGIN = 32;
    const int BUTTONS_WINDOW_MARGIN = 32;
    const int SPACE_BETWEEN_CHAT_AND_TEXTBOX = 16;
    const int SPACE_BETWEEN_CHAT_AND_BUTTONS = 32;

    //CHAT
    const sf::Vector2i CHAT_SIZE(
        window.getSize().x - SPACE_BETWEEN_CHAT_AND_BUTTONS - STANDARD_BUTTON_SIZE.x - CHAT_WINDOW_MARGIN - BUTTONS_WINDOW_MARGIN,
        window.getSize().y - CHAT_WINDOW_MARGIN * 2 - SPACE_BETWEEN_CHAT_AND_TEXTBOX - STANDARD_TEXTBOX_SIZE.y
    );
    const sf::Vector2f CHAT_POSITION(window.getSize().x - CHAT_SIZE.x - CHAT_WINDOW_MARGIN, CHAT_WINDOW_MARGIN);

    m_chat_rect.setSize(sf::Vector2f(CHAT_SIZE));
    m_chat_rect.setPosition(CHAT_POSITION);
    m_chat_rect.setFillColor(sf::Color(255, 255, 255, 191));

    m_textbox = TextBox(
        sf::Vector2f(CHAT_POSITION.x, CHAT_POSITION.y + CHAT_SIZE.y + SPACE_BETWEEN_CHAT_AND_TEXTBOX), 
        sf::Vector2f(CHAT_SIZE.x, STANDARD_TEXTBOX_SIZE.y)
    );
    m_textbox.set_fill_color(sf::Color(255, 255, 255, 191));

    //BUTTONS
    const sf::Vector2f BACK_BUTTON_POSITION(
        BUTTONS_WINDOW_MARGIN,
        window.getSize().y - STANDARD_BUTTON_SIZE.y - BUTTONS_WINDOW_MARGIN
    );

    m_buttons.emplace_back(BACK_BUTTON_POSITION, L"DISCONNECT");
}

void Lobby::mouse_click(const sf::RenderWindow& window)
{
    if(m_textbox.is_pressed(window))
        m_textbox.mark();
    else
        m_textbox.unmark();

    sf::Uint8 button_id = get_button_id_from_press(window);
    switch(button_id)
    {
    case 0://disconnect
    {
        engine.return_to_menu();
        break;
    }
    }
}

void Lobby::mouse_move(const sf::RenderWindow& window)
{
    for(Button& button : m_buttons)
    {
        if (button.is_mouse_on(window))
            button.mark();
        else
            button.unmark();
    }
}

void Lobby::add_lobby_message(const sf::String& message, sf::Color message_color)
{
    const int TEXT_CHAT_MARGIN = 4;
    const int SPACE_FOR_MESSAGE = 18;

    m_texts.emplace_back(message, resources_manager.get_font());
    sf::Text* text_ptr = &m_texts[m_texts.size() - 1];

    text_ptr->setFillColor(message_color);
    text_ptr->setCharacterSize(14U);

    text_ptr->setPosition(m_chat_rect.getPosition());
    text_ptr->move(
        TEXT_CHAT_MARGIN,
        TEXT_CHAT_MARGIN + (m_texts.size() - 1) * SPACE_FOR_MESSAGE
    );
}

void Lobby::send_message(const sf::String& message)
{
    /*
    The service for sending messages should be added here
    */
}

void Lobby::text_entered(const sf::Event& event)
{
    const int RETURN_CODE = 13;

    if(m_textbox.is_marked() && event.text.unicode == RETURN_CODE && m_textbox.get_string().getSize() > 0)
    {
        sf::String message = m_textbox.get_string();

        send_message(message);
        add_lobby_message("Me: " + message);
        m_textbox.set_string("");
    }
    else if(m_textbox.is_marked())
        m_textbox.enter_text(event.text.unicode);
}

void Lobby::refresh_players()
{
    const int SPACE_FOR_PLAYER = 40;
    const int PLAYER_WINDOW_MARGIN = 32;
    int position = 0;
    for (std::map<uint, sf::Text>::iterator player = m_players.begin(); player != m_players.end(); ++player, ++position)
        player->second.setPosition(PLAYER_WINDOW_MARGIN, PLAYER_WINDOW_MARGIN + position * SPACE_FOR_PLAYER);
}

void Lobby::join_player(uint id, const sf::String& player_name)
{
    add_lobby_message(player_name + " has joined the lobby", sf::Color(64, 160, 64));

    m_players_id.emplace_back(id);

    sf::Text player_text_name(player_name, resources_manager.get_font());
    player_text_name.setCharacterSize(22U);
    m_players.emplace(id, player_text_name);

    refresh_players();
}

void Lobby::disconnect_player(uint id)
{
    add_lobby_message(m_players.at(id).getString() + " has left the lobby", sf::Color(160, 64, 64));

    for(sf::Uint8 i = 0; i < m_players_id.size(); ++i)
    {
        if (m_players_id[i] == id)
        {
            m_players_id.erase(m_players_id.begin() + i);
            break;
        }
    }

    m_players.erase(id);
    refresh_players();
}

void Lobby::draw(sf::RenderWindow& window)
{
    window.draw(background);;

    window.draw(m_chat_rect);

    for(sf::Text& text: m_texts)
        window.draw(text);

    m_textbox.display(window);

    for(Button& button: m_buttons)
        button.display(window);

    for(std::map<uint, sf::Text>::iterator player = m_players.begin(); player != m_players.end(); ++player)
        window.draw(player->second);
}

sf::Uint8 Lobby::get_button_id_from_press(const sf::RenderWindow& window) const
{
    for(sf::Uint8 i = 0; i < m_buttons.size(); ++i)
        if(m_buttons[i].is_pressed(window))
            return i;

    return m_buttons.size();
}

void Lobby::debug_show_size() const
{
    //keep up to date!
    std::wcout << sizeof(m_buttons)    << L'\n'
               << sizeof(m_texts)      << L'\n'
               << sizeof(m_players)    << L'\n'
               << sizeof(m_players_id) << L'\n';
}
