#pragma once

#include <stack>
#include <vector>
#include <SDL2/SDL_video.h>
#include <headers/Mouse.hpp>
#include <headers/Button.hpp>

enum StateName : short {
	menu,
	play,
	pause,
};

class State {
protected:
	StateName m_name;
    bool 	  m_close;
	bool 	  m_pause;

//Background
    SDL_Texture* m_bg_texture;
    SDL_FRect	 m_bg_dest;

//Interaction
	Mouse m_mouse;
	std::vector <Button*> m_buttons;

//Functions
	void initState(const StateName& stateName);
	virtual void initBackground() = 0;
	virtual void initButtons() 	  = 0;
	
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

class StateManager {
private:
	std::stack <State*> states;
	short currentState;

public:
	StateManager();
	virtual ~StateManager();

	bool isExit();
	short& getCurrentState();

	void run();
	void pushState(const short& stateEnum);
};