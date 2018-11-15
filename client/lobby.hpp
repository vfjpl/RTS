#ifndef LOBBY_HPP_INCLUDED
#define LOBBY_HPP_INCLUDED

#include "button.hpp"
#include "../common/network_player.hpp"
#include <deque>

class Lobby
{
    //sort from largest to smallest!
    std::deque <Button> m_buttons;//80
    std::deque <sf::Text> m_players;//80

public:
    void setup();
    void clear();

    void mouse_click(const sf::Event& event);
    void mouse_move(const sf::Event& event);
    void text_entered(const sf::Event& event);

    void add_player(sf::Uint8 id);
    void remove_player(sf::Uint8 id);
    void refresh_player(sf::Uint8 id, const Network_Player& player);
    void draw();

    void debug_show_size() const;

private:
    sf::Uint8 get_button_id_from_press(const sf::Event& event) const;
};

#endif // LOBBY_HPP_INCLUDED
