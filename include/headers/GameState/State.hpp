#pragma once

#include <stack>
#include <SDL2/SDL_video.h>

enum StateName : short {
	menu,
	play,
	pause,
};

class State {
protected:
	short m_name;
    bool m_close;
	bool m_pause;
	
public:
	State();
	virtual ~State();

	bool isClosed();

	void checkCurrentState();

	virtual void run() 		 = 0;
	virtual void pollEvent() = 0;
	virtual void update()	 = 0;
	virtual void render()	 = 0;
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