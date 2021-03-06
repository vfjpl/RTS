#ifndef LOBBY_HPP_INCLUDED
#define LOBBY_HPP_INCLUDED

#include "button.hpp"
#include "inputbox.hpp"
#include "text.hpp"
#include <deque>

class Lobby
{
    //sort from largest to smallest!
    std::deque <Button> m_buttons;//80
    std::deque <InputBox> m_inputboxes;//80
    std::deque <Text> m_players;//80
    std::deque <Text> m_chat;//80
    sf::Vector2u m_middle;//8

public:
    void setup();
    void clear();

    void mouse_click(const sf::Event& event);
    void text_entered(const sf::Event& event);
    void mouse_move(const sf::Event& event);

    void add_player(sf::Uint8 id);
    void remove_player(sf::Uint8 id);
    void refresh_player(sf::Uint8 id);
    void add_chat_message(sf::Uint8 id, const std::wstring& message);

    void draw();

    void debug_show_size() const;

private:
    sf::Uint8 get_button_id_from_press(const sf::Event& event) const;
    sf::Uint8 get_marked_inputbox_id() const;
};

#endif // LOBBY_HPP_INCLUDED
