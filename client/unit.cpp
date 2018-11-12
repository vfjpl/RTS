#include "unit.hpp"

float Unit::get_strength(UnitType against) const
{
    return m_strength_against.at(against);
}

void Unit::set_strength(UnitType against, float strength)
{
    m_strength_against.at(against) = strength;
    if(m_strength_against.at(against) < 0.0f)
        m_strength_against.at(against) = 0.0f;
}

float Unit::get_hp() const
{
    return m_actual_hp;
}

void Unit::set_hp(float hp)
{
    m_actual_hp = hp;
    if(m_actual_hp < 0.0f)
        m_actual_hp = 0.0f;
}

void Unit::add_hp(float hp)
{
    m_actual_hp += hp;
    if(m_actual_hp > m_base_hp)
        m_actual_hp = m_base_hp;
}

void Unit::subtract_hp(float hp)
{
    m_actual_hp -= hp;
    if(m_actual_hp < 0.0f)
        m_actual_hp = 0.0f;
}

float Unit::get_max_hp() const
{
    return m_base_hp;
}

void Unit::set_max_hp(float hp)
{
    m_base_hp = hp;
    if(m_base_hp < 0.0f)
        m_base_hp = 0.0f;
}

float Unit::get_armor() const
{
    return m_armor;
}

void Unit::set_armor(float armor)
{
    m_armor = armor;
    if(m_armor < 0.0f)
        m_armor = 0.0f;
    else if(m_armor > 1.0f)
        m_armor = 1.0f;
}

float Unit::get_speed() const
{
    return m_actual_speed;
}

void Unit::set_speed(float speed)
{
    m_actual_speed = speed;
    if(m_actual_speed > m_base_speed)
        m_actual_speed = m_base_speed;
}

void Unit::set_max_speed(float speed)
{
    m_base_speed = speed;
    if(m_base_speed < 0.0f)
        m_base_speed = 0.0f;
}

void Unit::restore_speed()
{
    m_actual_speed = m_base_speed;
}

uint Unit::get_abilities() const
{
    return m_abilities;
}

void Unit::set_abilities(uint abilities)
{
    m_abilities = abilities;
}

void Unit::clear_abilities()
{
    m_abilities = 0;
}

void Unit::add_abilitiy(const Ability& ability)
{
    m_abilities |= ability;
}

uint Unit::get_price() const
{
    return m_price;
}

void Unit::set_price(uint price)
{
    m_price = price;
}

ushort Unit::get_team() const
{
    return m_team;
}

void Unit::set_team(ushort team)
{
    m_team = team;
}
