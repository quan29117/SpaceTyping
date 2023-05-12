/*******************************************************************//*
 * Component for running Animation once only. <used for Explosion>
 *
 *********************************************************************/

#pragma once

#include <headers/ECS/Draw/SpriteComponent.hpp>

class DeadAnimationComponent : public Component {
private:
    SpriteComponent* sprite;

public:
    DeadAnimationComponent();
    virtual ~DeadAnimationComponent();

    void init()   override;
    void update() override;
    void render() override;
};