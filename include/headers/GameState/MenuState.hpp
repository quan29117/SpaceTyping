#pragma once

#include <SDL2/SDL_render.h>
#include <headers/GameState/State.hpp>

class MenuState : public State {
private:
    enum ButtonNames {start, exit};

    SDL_Texture* m_title_texture;
    SDL_FRect m_title_dest;

//Functions
    void initBackground() override;
    void initButtons()    override;

    void pollEvent()      override;
    void update()         override;
	void render()         override;

public:
    MenuState();
    virtual ~MenuState();

    void run()	          override;
};