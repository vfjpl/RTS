#include "unit.hpp"

Unit::Unit() {}

Unit::Unit(sf::Uint8 x, sf::Uint8 y)
{
    this->x = x;
    this->y = y;
}

void Unit::set_position(sf::Uint8 x, sf::Uint8 y)
{
    this->x = x;
    this->y = y;
}

sf::Uint8 Unit::get_x() const
{
    return x;
}

sf::Uint8 Unit::get_y() const
{
    return y;
}
