#ifndef TEXTBOX_HPP_INCLUDED
#define TEXTBOX_HPP_INCLUDED

#include "SFML/Graphics.hpp"

#define STANDARD_TEXTBOX_SIZE sf::Vector2f(192.0f, 24.0f)

class TextBox : protected sf::RectangleShape
{
    sf::Text m_text;
    bool marked;

public:
    TextBox(const sf::Vector2f& pos, const sf::String& text, const sf::Vector2f& size = STANDARD_TEXTBOX_SIZE);

    void display(sf::RenderWindow& window) const;

    bool is_mouse_on(const sf::RenderWindow& window) const;
    bool is_pressed(const sf::RenderWindow& window) const;
    bool is_marked();

    void mark();
    void unmark();
    void set_string(sf::String string);
    void enter_text(sf::Uint32 unicode);
    sf::String get_string();
};

#endif // TEXTBOX_HPP_INCLUDED
