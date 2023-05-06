#include <headers/GameState/State.hpp>

#include <SDL2/SDL_mouse.h>
#include <headers/Structs.hpp>
#include <headers/Application.hpp>
#include <headers/GameState/MenuState.hpp>
#include <headers/GameState/PlayState.hpp>
#include <headers/GameState/PauseState.hpp>

//--------------------------------------------State--------------------------------------------
void State::initState(const StateID& stateID) {
	m_id = stateID;
	m_close = m_pause = false;
	initBackground();
	initButtons();
}

void State::updateInteraction() {
	m_mouse.update();
	for (auto& button : m_buttons) button->update(m_mouse);
}

bool State::isClosed() {
	return m_close;
}

void State::checkCurrentState() {
	if (m_id == Application::getStateManager()->getCurrentState())
		m_close = m_pause = false;
	else m_close = true;
}

//----------------------------------------StateManager-----------------------------------------
StateManager::StateManager() {
	m_currentState = none_state;
}

StateManager::~StateManager() {
	while (m_states.size() > 0) {
		delete m_states.top();
		m_states.pop();
	}
}

bool StateManager::isExit() {
	return m_states.size() == 0;
}

StateID StateManager::getCurrentState() {
	return m_currentState;
}

void StateManager::changeCurrentState(const StateID& stateID) {
	m_currentState = stateID;
}

void StateManager::run() {
	m_states.top()->checkCurrentState();
	m_states.top()->run();
	if (m_states.top()->isClosed()) {
		delete m_states.top();
		m_states.pop();
	}
}

void StateManager::pushState(const StateID& stateID) {
	if (m_currentState != stateID) {
		switch (stateID) {
			case menu_state:
				m_states.push(new MenuState());
				AudioManager::playMusic(menu_bgm);
				break;

			case play_state:
				m_states.push(new PlayState());
				AudioManager::playMusic(play_bgm);
				break;

			case pause_state:
				m_states.push(new PauseState());
				AudioManager::setVolume(70);
				break;
		}
		m_currentState = stateID;
	}
}