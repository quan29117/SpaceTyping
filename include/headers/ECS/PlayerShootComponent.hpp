#pragma once

#include <headers/ECS/ECS.hpp>
#include <headers/Vector2D.hpp>

class PlayerShootComponent : public Component {
private:
    unsigned char* s_char_input;

//Functions
    void shootEnemy();
    void shootBulletEnemy();

public: 
    PlayerShootComponent(unsigned char* char_input);
    virtual ~PlayerShootComponent();

    void init()   override {}
    void update() override {}
    void render() override {}

    void shoot();
};