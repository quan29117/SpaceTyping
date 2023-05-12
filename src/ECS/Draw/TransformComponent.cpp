/*******************************************************************//*
 * Implementation of the TransformComponent class.
 *
 *********************************************************************/

#include <headers/ECS/Draw/TransformComponent.hpp>

TransformComponent::TransformComponent(const Vector2D& start_pos, const bool& move, const Vector2D& dir, const float& speed) {
    m_position  = start_pos;
    m_movable   = move;
    m_direction = dir;
    m_speed     = speed;
    m_velocity  = (m_direction - m_position).unitVector();
}

TransformComponent::~TransformComponent() {}

Vector2D TransformComponent::getPosition() {
    return m_position;
}

void TransformComponent::init() {}

void TransformComponent::update() {
    if (m_movable) {
        m_position.x += m_velocity.x * m_speed;
        m_position.y += m_velocity.y * m_speed;
    }
}

void TransformComponent::render() {}