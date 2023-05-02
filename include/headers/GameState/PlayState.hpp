#pragma once

#include <random>
#include <vector>
#include <string>
#include <SDL2/SDL_render.h>
#include <headers/GameState/State.hpp>

class PlayState : public State {
private:
//SDL
	SDL_Texture* 	m_bg_texture;
	SDL_Rect 		camera;
	SDL_FRect		bg_dest;

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

//Functions
	void initBackground();
	void initTime();
	void initWordList();
	void initPlayer();

	void spawnEnemy();
	void enemyShoot();
	void playerShoot_t();
	void shooting();
	void updateCollision();
	void scrollBackground();

	void pollEvent(std::stack <State*>& states)	override;
	void update()								override;
	void render()								override;
	void updateTime();

public:
    PlayState();
    virtual ~PlayState();

    void run(std::stack <State*>& states)	override;
};
