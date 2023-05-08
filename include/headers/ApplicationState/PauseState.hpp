/*******************************************************************//*
 * ApplicationState class for the pause screen.
 * This state is entered after pressing ESC key at the PlayState.
 * 
 *********************************************************************/

#pragma once

#include <SDL2/SDL_render.h>
#include <headers/ApplicationState/State.hpp>
#include <headers/Mouse.hpp>
#include <headers/Button.hpp>

class PauseState : public State {
private:
    enum ButtonNames {conti = 0, exit};

    SDL_Texture* m_title_texture;
    SDL_FRect    m_title_dest;

//Functions
    void initBackground() override;
    void initButtons()    override;

    void pollEvent()      override;
    void update()         override;
	void render()         override;

public:
    PauseState();
    virtual ~PauseState();

    void run()            override;
};