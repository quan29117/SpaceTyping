/*******************************************************************//*
 * Implementation of the StateManager class.
 *
 *********************************************************************/

#include <headers/ApplicationManager/StateManager.hpp>

#include <headers/ApplicationManager/ResourceMethodManager.hpp>
#include <headers/ApplicationState/MenuState.hpp>
#include <headers/ApplicationState/PlayState.hpp>
#include <headers/ApplicationState/PauseState.hpp>

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
				AudioManager::setVolume(50);
				break;

			default:
				break;
		}
		m_currentState = stateID;
	}
}