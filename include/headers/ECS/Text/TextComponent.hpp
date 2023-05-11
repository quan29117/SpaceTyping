/*******************************************************************//*
 * Abstract class for TextComponent to make game logic
 * This class has subclasses used in Enemy & Bullet (Player & Enemy)
 *
 * Include:     text_reference to check Destroy condition
 * 
 * TextComponent subclasses must override the pure virtual methods 
 * to satisfy the main game loop
 * 
 *********************************************************************/

#pragma once

#include <headers/ECS/SpriteComponent.hpp>

class TextComponent : public Component {
protected:
    std::string m_text_ref;

public:
    TextComponent();
    virtual ~TextComponent();

    char getFirstChar();
    
    virtual int  remainingSize() = 0;
    virtual bool isFinished()    = 0;

    void init()   override;
    void update() override;
    void render() override;

    void Shot();
};