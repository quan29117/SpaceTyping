#pragma once

#include <SDL2/SDL_render.h>
#include <headers/GameState/State.hpp>
#include <headers/Mouse.hpp>
#include <headers/Button.hpp>

class PauseState : public State {
private:
//Background
    SDL_Texture* m_bg_texture;
    SDL_FRect	 m_bg_dest;

//Interaction
    Mouse   m_mouse;
    Button* m_buttons [2];
    enum ButtonNames {conti = 0, exit};

//Functions
    void initBackground();
    void initButtons();

    void pollEvent() override;
    void update()    override;
	void render()	 override;

public:
    PauseState();
    virtual ~PauseState();

    void run()       override;
};