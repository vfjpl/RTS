#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include "button.hpp"
#include <deque>

class Menu
{
    //sort from largest to smallest!
    std::deque <Button> m_buttons;//80
    std::deque <sf::Text> m_texts;//80
    sf::Vector2u m_middle;//8
    sf::Uint8 m_state;//1

public:
    void setup();
    void clear();

    void mouse_click(const sf::Event& event);
    void text_entered(const sf::Event& event);
    void mouse_move(const sf::Event& event);

    void draw();

    void debug_show_size() const;

private:
    sf::Uint8 get_button_id_from_press(const sf::Event& event) const;

    void main_menu();
    void connect_menu();
    void options_menu();
    void authors_menu();
};

#endif // MENU_HPP_INCLUDED
