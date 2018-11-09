#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include "SFML/Graphics.hpp"
#include <deque>
#include "button.hpp"
#include "textbox.hpp"

class Menu
{
    //sort from largest to smallest!
    std::deque <Button> m_buttons;
    std::deque <TextBox> m_textboxes;
    std::deque <sf::RectangleShape> m_rectangles;
    sf::Sprite background;
    std::deque <sf::Text> m_texts;//80
    sf::Uint8 m_state;//1

public:
    void init(const sf::RenderWindow& window);
    void clear();

    void mouse_click(const sf::RenderWindow& window);
    void mouse_move(const sf::RenderWindow& window);
    void text_entered(const sf::Event& event);
    void draw(sf::RenderWindow& window);

    void debug_show_size() const;

private:
    sf::Uint8 get_button_id_from_press(const sf::RenderWindow& window) const;

    void main_menu(const sf::RenderWindow& window);
    void connect_menu(const sf::RenderWindow& window);
    void options_menu(const sf::RenderWindow& window);
    void authors_menu(const sf::RenderWindow& window);
    void lobby_menu(const sf::RenderWindow& window);

    void add_author(const sf::RenderWindow& window, const sf::String& author);
    void add_lobby_message(const sf::String& message, sf::Color message_color = sf::Color::Black);
    void send_message(const sf::String& message);
};

#endif // MENU_HPP_INCLUDED
