/*******************************************************************//*
 * Component class for Text in Enemy
 * 
 * Include: 
 *
 *********************************************************************/

#pragma once

#include <headers/ECS/Text/TextComponent.hpp>

class EnemyTextComponent : public TextComponent {
protected:
    SpriteComponent*    sprite;
    SDL_Texture*        m_texture;
    SDL_Rect            m_destRect;
    std::string         m_text_display;
    FontID              m_font_id;
    SDL_Color           m_color;

    void setText();
    virtual void setPos();

public:
    EnemyTextComponent();
    EnemyTextComponent(const std::string& text, const FontID& id);
    virtual ~EnemyTextComponent();

    char getCharNeedTyped();

    int  remainingSize() override;
    bool isFinished() override;

    void init()       override;
    void update()     override;
    void render()     override;

    void Typed();
    void setColor(const SDL_Color& color);
};