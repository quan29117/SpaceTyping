#pragma once

#include <headers/ECS/ECS.hpp>
#include <headers/Vector2D.hpp>

class TransformComponent : public Component {
private:
    Vector2D direction, velocity;
    bool movable;
    float speed;
    
public:
    Vector2D position;

    TransformComponent(const float& pos_x, const float& pos_y, const bool& move = false, const float& dir_x = 0, const float& dir_y = 0, const float& spd = 0);
    virtual ~TransformComponent() {}

    void init()   override {}
    void update() override;
    void render() override {}
    
};