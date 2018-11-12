#ifndef UNIT_HPP_INCLUDED
#define UNIT_HPP_INCLUDED

#include <map>

enum Nationality
{
    NATIONALITY_ALL = 0,
    NATIONALITY_A,
    NATIONALITY_B
};

enum UnitType
{
    UNIT_INFANTRY = 0,
    UNIT_TANK
};

enum Ability
{
    ABILITY_SHOOTING = 1,
    CAPTURE_BUILDING = 2,
    CAPTURE_UNITS = 4,
    CRUSHING_UNITS = 8,
    DEFENSE_AGAINST_CRUSHING = 16,
    HARVESTING = 32
};

class Unit
{
    std::map<UnitType, float> m_strength_against;
    Nationality m_nationality;//Which nationality can recruit it
    UnitType m_unit_type;
    float m_base_hp;
    float m_actual_hp;
    float m_armor;//0.00 - 1.00 (how much damage absorbs)
    float m_base_speed;;
    float m_actual_speed;
    uint m_abilities;
    uint m_price;
    ushort m_team;

public:

    float get_strength(UnitType against) const;
    Nationality get_nationality() const;
    UnitType get_unit_type() const;
    float get_hp() const;
    void add_hp(float hp);
    void subtract_hp(float hp);
    float get_max_hp() const;
    float get_armor() const;
    float get_speed() const;
    void set_speed(float speed);
    void restore_speed();
    uint get_abilities() const;
    uint get_price() const;
    ushort get_team() const;
    void set_team(ushort team);

protected:

    void set_strength(const UnitType& against, float strength);
    void set_nationality(const Nationality& nationality);
    void set_unit_type(const UnitType& unit_type);
    void set_hp(float hp);
    void set_max_hp(float hp);
    void set_armor(float armor);
    void set_max_speed(float speed);
    void set_abilities(uint abilities);
    void clear_abilities();
    void add_abilitiy(const Ability& ability);
    void set_price(uint price);
};

#endif // TANK_HPP_INCLUDED