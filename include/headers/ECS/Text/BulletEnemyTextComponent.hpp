/*******************************************************************//*
 * Component class for Text in BulletEnemy
 * 
 * Include: 
 *
 *********************************************************************/

#pragma once

#include <headers/ECS/Text/EnemyTextComponent.hpp>

class BulletEnemyTextComponent : public EnemyTextComponent {
private:
    void setPos() override;

public:
    BulletEnemyTextComponent(const std::string& text, const FontID& id);
    virtual ~BulletEnemyTextComponent();

    void init()   override;
    void update() override;
    void render() override;
};
