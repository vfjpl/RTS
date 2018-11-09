#include "button.hpp"

#include "resources_manager.hpp"
#include "engine.hpp"

extern Resources_Manager resources_manager;

Button::Button(const sf::Vector2f& pos, const sf::String& text, const sf::Vector2f& size) 
    : sf::RectangleShape(size),
      m_text(text, resources_manager.get_font(), 24U)
{
    setFillColor(sf::Color::White);
    setOutlineColor(sf::Color::Black);
    setPosition(pos);
    
    const int TEXT_ORIGIN_X = m_text.getGlobalBounds().width  / 2;
    const int TEXT_ORIGIN_Y = m_text.getGlobalBounds().height / 2;
    const int TEXT_POS_X = getPosition().x + getSize().x / 2;
    const int TEXT_POS_Y = getPosition().y + getSize().y / 2;
    
    m_text.setFillColor(sf::Color::Black);
    m_text.setOrigin(TEXT_ORIGIN_X, TEXT_ORIGIN_Y);
    m_text.setPosition(TEXT_POS_X, TEXT_POS_Y);
}
// Button::Button(const sf::Vector2f& pos, const sf::String& text, float size_x, float size_y) 
//     : Button(pos, text, sf::Vector2f(size_x, size_y)) {}
// Button::Button(float pos_x, float pos_y, const sf::String& text, const sf::Vector2f& size) 
//     : Button(sf::Vector2f(pos_x, pos_y), text, size) {}
// Button::Button(float pos_x, float pos_y, const sf::String& text, float size_x, float size_y)
//     : Button(sf::Vector2f(pos_x, pos_y), text, sf::Vector2f(size_x, size_y)) {}


void Button::display(sf::RenderWindow& window) const
{
    window.draw(*this);
    window.draw(m_text);
}

void Button::mark()
{
    m_text.setFillColor(sf::Color::Green);
}

void Button::unmark()
{
    m_text.setFillColor(sf::Color::Black);
}

bool Button::is_mouse_on(const sf::RenderWindow& window) const
{
    return getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(window));
}

bool Button::is_pressed(const sf::RenderWindow& window) const
{
    const bool CLICKED = (is_mouse_on(window) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
    return CLICKED;
}

void Button::set_string(sf::String string)
{
    m_text.setString(string);
}

sf::String Button::get_string()
{
    return m_text.getString();
}
    