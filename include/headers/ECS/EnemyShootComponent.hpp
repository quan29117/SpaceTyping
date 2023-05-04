#pragma once

#include <headers/ECS/ECS.hpp>
#include <headers/Vector2D.hpp>

class EnemyShootComponent : public Component {
private:
    unsigned char* s_char_input;

public:
    EnemyShootComponent();
    virtual ~EnemyShootComponent();

    void init()   override {}
    void update() override;
    void render() override {}
};
