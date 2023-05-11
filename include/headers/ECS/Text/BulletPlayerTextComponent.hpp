/*******************************************************************//*
 * Component class for Text in BulletPlayer
 * 
 * Include:
 *
 *********************************************************************/

#pragma once

#include <headers/ECS/Text/TextComponent.hpp>

class BulletPlayerTextComponent : public TextComponent {
private:
    
public:
    BulletPlayerTextComponent(const std::string& text);
    virtual ~BulletPlayerTextComponent();

    int  remainingSize() override;
    bool isFinished() override;

    void init() override;
    void update() override;
    void render() override;
};