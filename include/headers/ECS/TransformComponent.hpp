/*******************************************************************//*
 * Transform Component for Position and Movement.
 *
 *********************************************************************/

#pragma once

#include <headers/ECS/ECS.hpp>
#include <headers/Vector2D.hpp>

class TransformComponent : public Component {
private:
    Vector2D m_direction, m_velocity, m_position;
    bool     m_movable;
    float    m_speed;
    
public:
    TransformComponent(const Vector2D& start_pos, const bool& move = false, const Vector2D& dir = Vector2D {0, 0}, const float& speed = 0);
    virtual ~TransformComponent();

    Vector2D getPosition();

    void init()   override {}
    void update() override;
    void render() override {}
    
};