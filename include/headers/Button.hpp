#pragma once

#include <headers/Mouse.hpp>

class Button {
private:
    SDL_Texture*    m_texture;
    SDL_FRect       m_dest;
    SDL_Rect        m_src;
    bool            selected;

public:
    Button(const float& src_y, const float& dest_x, const float& dest_y);
    virtual ~Button();

    bool isSelected();

    void update(Mouse& mouse);
    void render();
};