#include <headers/ECS/TransformComponent.hpp>

TransformComponent::TransformComponent(const float& pos_x, const float& pos_y, const bool& move, const float& dir_x, const float& dir_y, const float& spd) {
    position.x = pos_x;
    position.y = pos_y;

    movable = move;
    speed = spd;

    direction.x = dir_x;
    direction.y = dir_y;

    velocity = (direction - position).unitVector();
}

void TransformComponent::update() {
    if (movable) {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
}


