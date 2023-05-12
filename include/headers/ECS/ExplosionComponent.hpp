/*******************************************************************//*
 * Component for runing ExplosionAnimation when dead.
 *
 *********************************************************************/

#pragma once

#include <headers/ECS/TransformComponent.hpp>

class ExplosionComponent : public Component {
private:
    TransformComponent* transform;

public:
    ExplosionComponent();
    virtual ~ExplosionComponent();

    void init()   override;
    void update() override;
    void render() override;
};