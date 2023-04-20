#pragma once

#include <headers/ECS/SpriteComponent.hpp>
#include <headers/ResourceManager.hpp>

class TextComponent : public Component {
protected:
    SpriteComponent* m_sprite;
    FontID m_id;
    std::string m_text_display, m_text_ref;
    bool m_render;
    SDL_Color m_color;
    SDL_Texture* m_texture;
    SDL_Rect m_destRect;

    void setText();
    virtual void setPos();

public:
    TextComponent() = default;
    TextComponent(const FontID& id, const std::string& text, const bool& render = true, const SDL_Color& color = SDL_Color {255, 255, 255, 255});
    virtual ~TextComponent();

    char getFirstChar();
    char getCharNeedTyped();

    void init() override;
    void update() override;
    void render() override;

    void eraseFirstChar();
};

class TextEnemyComponent : public TextComponent {
private:
    
public:
    TextEnemyComponent(const FontID& id, const std::string& text);
    virtual ~TextEnemyComponent();

    void setPos() override;
    void getShot();
};
