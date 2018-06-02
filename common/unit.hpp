#ifndef UNIT_HPP_INCLUDED
#define UNIT_HPP_INCLUDED

#include <SFML/Main.hpp>

class Unit
{
    //sort from largest to smallest!
    sf::Uint8 m_x;//1
    sf::Uint8 m_y;//1
    sf::Uint8 m_hp;//1

public:
    Unit();
    Unit(sf::Uint8 x, sf::Uint8 y);
    Unit(sf::Uint8 hp);

    void set_position(sf::Uint8 x, sf::Uint8 y);
    void set_hp(sf::Uint8 hp);

    sf::Uint8 get_x() const;
    sf::Uint8 get_y() const;
    sf::Uint8 get_hp() const;

    void debug_show_size() const;
};

#endif // UNIT_HPP_INCLUDED
