#pragma once

#include <random>
#include <SDL2/SDL_image.h>
#include <headers/State.hpp>
#include <headers/ECS/Components.hpp>

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
	EntityManager manager;
	Entity& m_player = manager.addEntity();
    // Player* player;
	// EnemySystem* enemy_system;
	// PauseMenu* pause_menu;

//Functions
	void initPtr();
	void initProgress();

public:
    GamePlay();
    virtual ~GamePlay();

    void run(std::queue <State*>& states);
	void pollEvent();
	void updateGame();
	void render();

	void spawnEnemies();
};
