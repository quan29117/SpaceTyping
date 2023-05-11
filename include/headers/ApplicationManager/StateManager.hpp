/*******************************************************************//*
 * This class encapsulates all state code.
 * Responsibilities include switching states, handling state transitions,
 * and delegating game loop methods to respective states.
 *
 *********************************************************************/

#pragma once

#include <stack>
#include <headers/ApplicationState/State.hpp>

class StateManager {
private:
	std::stack <State*> m_states;
	StateID m_currentState;

public:
	StateManager();
	virtual ~StateManager();

	bool isExit();
	StateID getCurrentState();

	void run();
	void pushState(const StateID& stateID);
	void changeCurrentState(const StateID& stateID);
};