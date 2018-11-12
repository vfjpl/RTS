#include "graphical_unit.hpp"
#include <math.h>

GraphicalUnit::GraphicalUnit(const sf::Texture& texture, const sf::Vector2f& pos)
{
    m_sprite.setTexture(texture);
    m_sprite.setOrigin(
        m_sprite.getGlobalBounds().width / 2,
        m_sprite.getGlobalBounds().height / 2
    );
    m_sprite.setPosition(pos);
    set_rotation_rad(0.0f);
}
GraphicalUnit::GraphicalUnit(const sf::Texture& texture, float x, float y)
    : GraphicalUnit(texture, sf::Vector2f(x, y)) {}

void GraphicalUnit::move()
{
    if (has_target())
    {
        const sf::Vector2f POSITION = m_sprite.getPosition();

        //ROTATION
        const float DISTANCE_X = get_target_x() - m_sprite.getPosition().x;
        const float DISTANCE_Y = get_target_y() - m_sprite.getPosition().y;
        const float UNIT_TARGET_RADIANS = atan2(DISTANCE_Y, DISTANCE_X);
        set_rotation_rad(UNIT_TARGET_RADIANS);

        //MOVE
        const float GAME_SPEED = 10;//1sec in life == ? secs in game
        const float METER_TO_PX = 3;//1meter == ? pixels
        const float PX_PER_SEC = ((get_speed() * (1000 * METER_TO_PX)) / 3600.0f) * GAME_SPEED;
        const float FRAMERATE = 60.0f;
        const float PX_PER_FRAME = PX_PER_SEC / FRAMERATE;

        const sf::Vector2f TARGET_POS = get_target();
        const sf::Vector2f MOVE(
            cos(get_rotation_rad()) * PX_PER_FRAME,
            sin(get_rotation_rad()) * PX_PER_FRAME
        );

        m_sprite.move(MOVE);

        //TODO: UNSET TARGET IF REACHED HIS DESTINATION
    }
}

sf::Vector2f GraphicalUnit::get_target() const
{
    return sf::Vector2f(get_target_x(), get_target_y());
}

void GraphicalUnit::set_target(const sf::Vector2f& pos)
{
    Unit::set_target(pos.x, pos.y);
}

const sf::Texture* GraphicalUnit::get_texture() const
{
    return m_sprite.getTexture();
}

float GraphicalUnit::get_rotation_rad() const
{
    return m_rotation;
}

void GraphicalUnit::set_rotation_rad(float angle)
{
    m_rotation = angle;
    m_sprite.setRotation(rad_to_deg(angle));
}

void GraphicalUnit::set_rotation_deg(float angle)
{
    m_rotation = deg_to_rad(angle);
    m_sprite.setRotation(angle);
}

float GraphicalUnit::deg_to_rad(float angle)
{
    return angle * (M_PI / 180.0f);
}

float GraphicalUnit::rad_to_deg(float angle)
{
    return angle * (180.0f / M_PI);
}

void GraphicalUnit::display(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
}
