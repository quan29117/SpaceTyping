#pragma once

#include <headers/Mouse.hpp>

class Button {
private:
    SDL_Texture*    m_texture;
    SDL_FRect       m_dest;
    SDL_Rect        m_src_idle, m_src_hover;
    bool            selected;
    
public:
    Button(const SDL_Rect& src_idle, const SDL_Rect& src_hover, const SDL_FRect& dest);
    virtual ~Button();

    bool isSelected();

    void update(Mouse& mouse);
    void render();
};