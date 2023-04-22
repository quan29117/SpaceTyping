#pragma once

#include <random>
#include <vector>
#include <string>
#include <SDL2/SDL_image.h>
#include <headers/State.hpp>

class GamePlay : public State {
private:
//SDL
	SDL_Texture* m_bg_texture;
	SDL_Rect camera;

//Progress
    unsigned int stage;
	unsigned int point;
    unsigned char char_input;

	//Display
	
//Time
	float start, end, elapsedS;

//Word list
	std::vector <std::string> word_list;

//RNG - random number generator
	std::random_device rd;
	std::mt19937 rng;

//Ptr
	// PauseMenu* pause_menu;

//Functions
	void initBackground();
	void initPtr();
	void initProgress();
	void initTime();
	void initWordList();

	void pollEvent();
	void updateGame();
	void render();

	void spawnEnemy();
	void playerShoot();
	void enemyShoot();

	void scrollBackground();

public:
    GamePlay();
    virtual ~GamePlay();

    void run(std::queue <State*>& states);
};
