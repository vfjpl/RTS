#include "unit.hpp"
#include <iostream>

Unit::Unit() {}

Unit::Unit(sf::Uint8 x, sf::Uint8 y)
{
    m_x = x;
    m_y = y;
}

void Unit::set_position(sf::Uint8 x, sf::Uint8 y)
{
    m_x = x;
    m_y = y;
}

sf::Uint8 Unit::get_x() const
{
    return m_x;
}

sf::Uint8 Unit::get_y() const
{
    return m_y;
}

void Unit::debug_show_size() const
{
    std::cout << sizeof(m_x) << "\n"
              << sizeof(m_y) << "\n";
}
