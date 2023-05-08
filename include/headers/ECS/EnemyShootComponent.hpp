/*******************************************************************//*
 * Component for Enemy Shooting to make gameplay a bit more difficult.
 *
 *********************************************************************/

#pragma once

#include <random>
#include <headers/ECS/ECS.hpp>
#include <headers/Vector2D.hpp>

class EnemyShootComponent : public Component {
private:
    std::mt19937* s_rng;
    bool m_has_shot;

public:
    EnemyShootComponent(std::mt19937* rng);
    virtual ~EnemyShootComponent();

    void init()   override {}
    void update() override {}
    void render() override {}

    void shoot();
};
