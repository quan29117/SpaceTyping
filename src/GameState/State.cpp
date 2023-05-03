#include <headers/GameState/State.hpp>

#include <SDL2/SDL_mouse.h>
#include <headers/Application.hpp>
#include <headers/GameState/MenuState.hpp>
#include <headers/GameState/PlayState.hpp>
#include <headers/GameState/PauseState.hpp>

//----------------------------------------State----------------------------------------
State::State() 
	: m_close(0), m_pause (0)
{}

State::~State() {}

bool State::isClosed() {
	return m_close;
}

void State::checkCurrentState() {
	if (m_name == Application::getStateManager()->getCurrentState())
		m_close = m_pause = false;
	else m_close = true;
}

//------------------------------------StateManager-------------------------------------
StateManager::StateManager() {
	currentState = -1;
}

StateManager::~StateManager() {
	while (states.size() > 0) {
		delete states.top();
		states.pop();
	}
}

bool StateManager::isExit() {
	return states.size() == 0;
}

short& StateManager::getCurrentState() {
	return currentState;
}

void StateManager::run() {
	states.top()->checkCurrentState();
	states.top()->run();
	if (states.top()->isClosed()) {
		delete states.top();
		states.pop();
	}
}

void StateManager::pushState(const short& stateEnum) {
	if (currentState != stateEnum) {
		switch (stateEnum) {
			case menu:
				states.push(new MenuState());
				break;

			case play:
				states.push(new PlayState());
				break;

			case pause:
				states.push(new PauseState());
				break;
		}
		currentState = stateEnum;
	}
}