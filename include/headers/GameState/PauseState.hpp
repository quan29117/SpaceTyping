#pragma once

#include <SDL2/SDL_render.h>
#include <headers/GameState/State.hpp>
#include <headers/Mouse.hpp>
#include <headers/Button.hpp>

class PauseState : public State {
private:
    enum ButtonNames {conti = 0, exit};

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