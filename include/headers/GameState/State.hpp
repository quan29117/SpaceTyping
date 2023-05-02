#pragma once

#include <stack>
#include <SDL2/SDL_video.h>

class State {
protected:
    bool close;
	bool pause;
	
public:
	State();
	virtual ~State();

	bool isClosed();

	virtual void run(std::stack <State*>& states) 		= 0;
	virtual void pollEvent(std::stack <State*>& states) = 0;
	virtual void update()						  		= 0;
	virtual void render()	  					  		= 0;
};