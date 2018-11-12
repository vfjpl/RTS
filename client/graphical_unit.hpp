#ifndef GRAPHICAL_UNIT_HPP_INCLUDED
#define GRAPHICAL_UNIT_HPP_INCLUDED

#include "SFML/Graphics.hpp"
#include "unit.hpp"

class GraphicalUnit : public Unit
{
    sf::Sprite m_sprite;
    float m_rotation;//rad

public:
    GraphicalUnit(const sf::Texture& texture, const sf::Vector2f& pos);
    GraphicalUnit(const sf::Texture& texture, float x, float y);

    virtual void shot() = 0;
    void move();

    sf::Vector2f get_target() const;
    void set_target(const sf::Vector2f& pos);
    const sf::Texture* get_texture() const;
    float get_rotation_rad() const;
    void set_rotation_rad(float angle);
    void set_rotation_deg(float angle);
    void display(sf::RenderWindow& window) const;

private:
    float deg_to_rad(float angle);
    float rad_to_deg(float angle);
};

#endif // GRAPHICAL_UNIT_HPP_INCLUDED