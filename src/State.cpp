#include <headers/State.hpp>


State::State() 
	: close(0), pause (0)
{}

State::~State() {}

bool State::isClosed() {
	return close;
}

void State::updateMousePos(SDL_Window* window) {
    Uint32 mouse;
	mouse = SDL_GetMouseState(&m_mouseX, &m_mouseY);
}