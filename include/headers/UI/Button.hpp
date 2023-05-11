/*******************************************************************//*
 * Button class for interaction
 *
 *********************************************************************/

#pragma once

#include <headers/UI/Mouse.hpp>

class Button {
private:
    enum ButtonStatus {idle = 0, hover};

    SDL_Texture*    m_texture;
    SDL_FRect       m_dest;
    SDL_Rect        m_src_idle, m_src_hover;
    ButtonStatus    m_status;
    
public:
    Button(const SDL_Rect& src_idle, const SDL_Rect& src_hover, const SDL_FRect& dest);
    virtual ~Button();

    bool isHovered();

    void update(Mouse& mouse);
    void render();
};