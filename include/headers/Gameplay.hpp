#pragma once

#include <random>
#include <SDL2/SDL_image.h>
#include <headers/State.hpp>

class GamePlay : public State {
private:
//SDL

//Progress
    unsigned int stage;
	unsigned int point;
    unsigned char char_input;

	//Display
	

//RNG - random number generator
	std::random_device rd;
	std::mt19937 rng;

//Ptr
	
    // Player* player;
	// EnemySystem* enemy_system;
	// PauseMenu* pause_menu;

//Functions
	void initPtr();
	void initProgress();

	void pollEvent();
	void updateGame();
	void render();

public:
    GamePlay();
    virtual ~GamePlay();

    void run(std::queue <State*>& states);
};
