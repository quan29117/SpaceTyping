/*******************************************************************//*
 * Default implementation of virtual methods in State class.
 *
 *********************************************************************/

#include <headers/ApplicationState/State.hpp>

#include <SDL2/SDL_mouse.h>
#include <headers/Application.hpp>

State::State() {}

State::~State() {}

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
	else m_close = m_pause = true;
}