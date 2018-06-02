#include "unit.hpp"
#include <iostream>

Unit::Unit() {}

Unit::Unit(sf::Uint8 x, sf::Uint8 y)
{
    m_x = x;
    m_y = y;
}

Unit::Unit(sf::Uint8 hp)
{
    m_hp = hp;
}

void Unit::set_position(sf::Uint8 x, sf::Uint8 y)
{
    m_x = x;
    m_y = y;
}

void Unit::set_hp(sf::Uint8 hp)
{
    m_hp = hp;
}

sf::Uint8 Unit::get_x() const
{
    return m_x;
}

sf::Uint8 Unit::get_y() const
{
    return m_y;
}

sf::Uint8 Unit::get_hp() const
{
    return m_hp;
}

void Unit::debug_show_size() const
{
    std::cout << sizeof(m_x) << "\n"
              << sizeof(m_y) << "\n"
              << sizeof(m_hp) << "\n";
}
