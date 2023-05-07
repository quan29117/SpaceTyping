#pragma once

#include <random>
#include <vector>
#include <string>
#include <SDL2/SDL_render.h>
#include <headers/GameState/State.hpp>
#include <headers/Button.hpp>

#include <headers/ECS/Components.hpp>

class PlayState : public State {
private:
//Background camera
	SDL_Rect m_camera;
	
//Time
	float start, end, spawnTime, spawnCoolDown;

//Word list
	std::vector <std::string> m_word_list;

//RNG - random number generator
	std::random_device m_rd;
	std::mt19937 m_rng;

//Progress																
	
    unsigned char m_char_input;
	static EntityManager* s_manager;
	//Display

//Functions
	void initBackground() override;
	void initButtons()	  override;
	void initTime();
	void initWordList();
	void initPlayer();

	std::string generatedWords();
	void spawnEnemy();
	void shooting();
	void updateCollision();
	void scrollBackground();
	void resetCharInput();

	void pollEvent() override;
	void update()	 override;
	void render()	 override;
	void updateTime();
	
public:			
    PlayState();
    virtual ~PlayState();

	static EntityManager* getEntityManager();

    void run()		 override;
};
