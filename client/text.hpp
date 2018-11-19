#ifndef TEXT_HPP_INCLUDED
#define TEXT_HPP_INCLUDED

#include "SFML/Graphics.hpp"

class Text
{
public:
    //sort from largest to smallest!
    sf::Text m_text;//368

    Text(unsigned int x, unsigned int y, unsigned int characterSize);
    Text(const wchar_t* text, unsigned int x, unsigned int y);
    Text(const std::wstring& text, unsigned int x, unsigned int y);

    void debug_show_size() const;
};

#endif // TEXT_HPP_INCLUDED
