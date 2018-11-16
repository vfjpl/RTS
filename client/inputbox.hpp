#ifndef INPUTBOX_HPP_INCLUDED
#define INPUTBOX_HPP_INCLUDED

#include "SFML/Graphics.hpp"

class InputBox
{
public:
    //sort from largest to smallest!
    sf::Text m_text;//368
    sf::RectangleShape m_background;//344
    bool m_marked = false;//1


    InputBox(unsigned int x, unsigned int y, unsigned int width);

    void mark();
    void unmark();

    void debug_show_size() const;
};

#endif // INPUTBOX_HPP_INCLUDED
