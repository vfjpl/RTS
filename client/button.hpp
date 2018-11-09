#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "SFML/Graphics.hpp"

#define STANDARD_BUTTON_SIZE sf::Vector2f(192.0f, 48.0f)

class Button : protected sf::RectangleShape
{
    sf::Text m_text;

public:
    Button(const sf::Vector2f& pos, const sf::String& text, const sf::Vector2f& size = STANDARD_BUTTON_SIZE);
    // Button(const sf::Vector2f& pos, const sf::String& text, float size_x = STANDARD_BUTTON_SIZE.x, float size_y = STANDARD_BUTTON_SIZE.y);
    // Button(float pos_x, float pos_y, const sf::String& text, const sf::Vector2f& size = STANDARD_BUTTON_SIZE);
    // Button(float pos_x, float pos_y, const sf::String& text, float size_x = STANDARD_BUTTON_SIZE.x, float size_y = STANDARD_BUTTON_SIZE.y);

    void display(sf::RenderWindow& window) const;

    bool is_mouse_on(const sf::RenderWindow& window) const;
    bool is_pressed(const sf::RenderWindow& window) const;

    void mark();
    void unmark();
    void set_string(sf::String string);
    sf::String get_string();
};

#endif // BUTTON_HPP_INCLUDED
