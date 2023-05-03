#pragma once

#include <random>
#include <vector>
#include <string>
#include <SDL2/SDL_render.h>
#include <headers/GameState/State.hpp>
#include <headers/Button.hpp>

class PlayState : public State {
private:
//Background
	SDL_Texture* 	m_bg_texture;
	SDL_Rect 		m_camera;
	SDL_FRect		m_bg_dest;

//Buttons
	// Button* m_buttons [2];

//Progress
	unsigned int point;
    unsigned char char_input;

	//Display
	
//Time
	float start, end, spawnTime;

//Word list
	std::vector <std::string> m_word_list;

//RNG - random number generator
	std::random_device rd;
	std::mt19937 rng;

//Functions
	void initInheritance();
	void initBackground();
	void initTime();
	void initWordList();
	void initPlayer();

	void spawnEnemy();
	void enemyShoot();
	void shooting();
	void updateCollision();
	void scrollBackground();

	void pollEvent() override;
	void update()	 override;
	void render()	 override;
	void updateTime();

public:
    PlayState();
    virtual ~PlayState();

    void run()		 override;
};
