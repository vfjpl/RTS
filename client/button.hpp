#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "SFML/Graphics.hpp"

class Button
{
public:
    //sort from largest to smallest!
    sf::Text m_text;//368
    sf::RectangleShape m_background;//344


    Button(const wchar_t* text, unsigned int x, unsigned int y);//variable width button
    Button(const wchar_t* text, unsigned int x, unsigned int y, unsigned int width);

    void mark();
    void unmark();

    void debug_show_size() const;
};

#endif // BUTTON_HPP_INCLUDED
