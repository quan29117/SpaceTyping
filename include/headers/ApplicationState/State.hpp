/*******************************************************************//*
 * Abstract ApplicationState class.
 * ApplicationState subclasses must override the pure virtual methods 
 * to satisfy the main game loop
 *
 *********************************************************************/

#pragma once

#include <vector>
#include <SDL2/SDL_render.h>
#include <headers/Mouse.hpp>
#include <headers/Button.hpp>

enum StateID : short {
	none_state = -1,
	menu_state,
	play_state,
	pause_state,
};

class State {
protected:
	StateID m_id;
    bool 	m_close;
	bool 	m_pause;

//Background
    SDL_Texture* m_bg_texture;
    SDL_FRect	 m_bg_dest;

//Interaction
	Mouse m_mouse;
	std::vector <Button*> m_buttons;

//Functions
	virtual void initBackground() = 0;
	virtual void initButtons() 	  = 0;

	void initState(const StateID& stateID);
	void updateInteraction();
	
public:
	State() {}
	virtual ~State() {}

	bool isClosed();

	void checkCurrentState();

	virtual void run() 		 	  = 0;
	virtual void pollEvent() 	  = 0;
	virtual void update()	 	  = 0;
	virtual void render()	 	  = 0;
};