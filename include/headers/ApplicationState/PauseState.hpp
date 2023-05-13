/*******************************************************************//*
 * ApplicationState class for the pause screen.
 * This state is entered after pressing ESC key at the PlayState.
 * 
 *********************************************************************/

#pragma once

#include <headers/ApplicationState/State.hpp>

class PauseState : public State {
private:
    enum ButtonNames {conti = 0, menu_back, music, sound};

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