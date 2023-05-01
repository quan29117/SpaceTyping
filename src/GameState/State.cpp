#include <headers/GameState/State.hpp>

#include <SDL2/SDL_mouse.h>

State::State() 
	: close(0), pause (0)
{}

State::~State() {}

bool State::isClosed() {
	return close;
}