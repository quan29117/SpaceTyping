/*******************************************************************//*
 * Text Component for Enemy and Bullet Enemy to "destroy" those.
 *
 *********************************************************************/

#pragma once

#include <headers/ECS/SpriteComponent.hpp>
#include <headers/ResourceManager.hpp>

class TextComponent : public Component {
private:
    SpriteComponent*    sprite;
    SDL_Texture*        m_texture;
    SDL_Rect            m_destRect;
    bool                m_render,
                        m_center;
    std::string         m_text_display,
                        m_text_ref;
    FontID              m_font_id;
    SDL_Color           m_color;

    void setText();
    void setPos();

public:
    TextComponent() = default;
    TextComponent(const FontID& id, const std::string& text, const bool& center = true, const bool& render = true, const SDL_Color& color = SDL_Color {255, 255, 255, 255});
    virtual ~TextComponent() {}

    char getFirstChar();
    char getCharNeedTyped();
    int  remainingSize();

    bool isFinished();

    void init() override;
    void update() override;
    void render() override;

    void Typed();
    void Shot();
    void setColor(const SDL_Color& color);
};