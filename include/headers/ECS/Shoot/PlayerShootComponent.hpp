/*******************************************************************//*
 * Component for Player Shooting when typing correctly
 *
 *********************************************************************/

#pragma once

#include <headers/ECS/ECS.hpp>
#include <headers/Math/Vector2D.hpp>
#include <headers/ECS/Collision/CollisionComponent.hpp>

class PlayerShootComponent : public Component {
private:
    Entity*                m_lock_target;
    unsigned char*         s_char_input;
    std::vector <Entity*>* s_enemyGroup;
    std::vector <Entity*>* s_bulletEnemyGroup;

//Functions
    Entity& createBulletPlayer(const EntityGroup& EG, const CollisionID& id, const char& ch, const Vector2D& direction);
    void shootEnemy();
    void shootBulletEnemy();

public: 
    PlayerShootComponent(unsigned char* char_input);
    virtual ~PlayerShootComponent();

    void init()   override;
    void update() override;
    void render() override;

    void shoot();
};