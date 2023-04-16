#pragma once

#include <queue>
#include <SDL2/SDL_video.h>

class State {
protected:
    bool close;
	bool pause;

	int m_mouseX, m_mouseY;
	
public:
	State();
	virtual ~State();

	bool isClosed();

	virtual void updateMousePos(SDL_Window* window);

	virtual void run(std::queue <State*>& states) = 0;
	virtual void pollEvent()    				  = 0;
	virtual void render()	  					  = 0;
};