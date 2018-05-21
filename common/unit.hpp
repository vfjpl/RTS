#ifndef UNIT_HPP_INCLUDED
#define UNIT_HPP_INCLUDED

#include <SFML/Main.hpp>

class Unit
{
    sf::Uint8 x;
    sf::Uint8 y;

public:
    Unit();
    Unit(sf::Uint8 x, sf::Uint8 y);
    void set_position(sf::Uint8 x, sf::Uint8 y);
    sf::Uint8 get_x() const;
    sf::Uint8 get_y() const;
};

#endif // UNIT_HPP_INCLUDED
