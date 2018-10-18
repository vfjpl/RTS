#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include "SFML/Graphics.hpp"
#include <deque>

class Menu
{
    //sort from largest to smallest!
    std::deque <sf::Text> m_texts;//80
    sf::Uint8 m_state;//1

public:
    void init();
    void clear();

    void mouse_click(const sf::Event& event);
    void mouse_move(const sf::Event& event);
    void logic();
    void draw(sf::RenderWindow& window);

    void debug_show_size() const;

private:
    sf::Uint8 get_text_id_from_press(const sf::Event& event) const;
    sf::Uint8 get_text_id_from_move(const sf::Event& event) const;

    void main_menu();
    void connect_menu();
    void authors_menu();
};

#endif // MENU_HPP_INCLUDED
