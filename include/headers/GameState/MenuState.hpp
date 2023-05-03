#pragma once

#include <SDL2/SDL_render.h>
#include <headers/GameState/State.hpp>
#include <headers/Mouse.hpp>
#include <headers/Button.hpp>

class MenuState : public State {
private:
//Background
    SDL_Texture* m_bg_texture;
	SDL_FRect	 m_bg_dest;

//Interaction
    Mouse   m_mouse;
    Button* m_buttons [2];
    enum ButtonNames {start, exit};

//Functions
    void initBackground();
    void initButtons();

    void pollEvent() override;
    void update()    override;
	void render()    override;

public:
    MenuState();
    virtual ~MenuState();

    void run()	     override;
};