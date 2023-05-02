#pragma once

#include <vector>
#include <SDL2/SDL_render.h>
#include <headers/GameState/State.hpp>
#include <headers/Mouse.hpp>
#include <headers/Button.hpp>

class MenuState : public State {
private:
enum ButtonNames {start, exit};
//Background
    SDL_Texture* 	m_bg_texture;
	SDL_FRect		m_bg_dest;

//Interaction
    Mouse m_mouse;
    Button* m_buttons [2];

//Functions
    void initBackground();
    void initButtons();

    void pollEvent(std::stack <State*>& states)	override;
    void update()                               override;
	void render()							    override;

public:
    MenuState();
    virtual ~MenuState();

    void run(std::stack <State*>& states)	override;
};