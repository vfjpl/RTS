#include "textbox.hpp"

#include "resources_manager.hpp"
#include "engine.hpp"

extern Resources_Manager resources_manager;

TextBox::TextBox(const sf::Vector2f& pos, const sf::String& text, const sf::Vector2f& size)
    : sf::RectangleShape(size),
      m_text(text, resources_manager.get_font(), 14U),
      marked(false)
{
    setFillColor(sf::Color::White);
    setOutlineColor(sf::Color::Black);
    setPosition(pos);

    const int TEXT_ORIGIN_X = 0;
    const int TEXT_ORIGIN_Y = m_text.getGlobalBounds().height / 2;
    const int TEXT_MARGIN_LEFT = 4;
    const int TEXT_POS_X = getPosition().x + TEXT_MARGIN_LEFT;
    const int TEXT_POS_Y = getPosition().y + getSize().y / 2;

    m_text.setFillColor(sf::Color::Black);
    m_text.setOrigin(TEXT_ORIGIN_X, TEXT_ORIGIN_Y);
    m_text.setPosition(TEXT_POS_X, TEXT_POS_Y);
}

void TextBox::display(sf::RenderWindow& window) const
{
    window.draw(*this);
    window.draw(m_text);
}

bool TextBox::is_mouse_on(const sf::RenderWindow& window) const
{
    return getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(window));
}

bool TextBox::is_pressed(const sf::RenderWindow& window) const
{
    const bool CLICKED = (is_mouse_on(window) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
    return CLICKED;
}

bool TextBox::is_marked()
{
    return marked;
}

void TextBox::mark()
{
    marked = true;
    set_string(m_text.getString());
}

void TextBox::unmark()
{
    marked = false;

    sf::String unmarked_string(m_text.getString());
    unmarked_string.erase(unmarked_string.getSize() - 1);

    set_string(unmarked_string);
}

void TextBox::set_string(sf::String string)
{
    m_text.setString(string + (marked ? "|" : ""));
}

void TextBox::enter_text(sf::Uint32 unicode)
{
    sf::String new_string(get_string());

    const sf::Uint32 BACKSPACE_CODE = 8;
    const sf::Uint32 FIRST_LETTER_OF_ALPHABET_CODE = 65;
    const sf::Uint32 LAST_LETTER_OF_ALPHABET_CODE  = 122;

    if(unicode == BACKSPACE_CODE)
    {
        if(new_string.getSize() > 0)
            new_string.erase(new_string.getSize() - 1);
    }
    else if(unicode >= FIRST_LETTER_OF_ALPHABET_CODE && unicode <= LAST_LETTER_OF_ALPHABET_CODE)
        new_string += unicode;

    set_string(new_string);
}

sf::String TextBox::get_string()
{
    sf::String string_without_marker(m_text.getString());
    string_without_marker.erase(string_without_marker.getSize() - 1);

    return string_without_marker;
}
