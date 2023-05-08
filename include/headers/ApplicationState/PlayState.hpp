/*******************************************************************//*
 * ApplicationState class for the game.
 * This state is entered after clicking the "Start" button
 * from the menu state
 *
 *********************************************************************/

#pragma once

#include <random>
#include <vector>
#include <string>
#include <headers/ApplicationState/State.hpp>
#include <headers/ECS/Components.hpp>

class PlayState : public State {
private:
//Background camera
	SDL_Rect m_camera;

//Board score
	SDL_Texture* m_board_texture;
	SDL_FRect	 m_board_dest;
	
//Time
	float start, end, spawnTime, spawnCoolDown;

//Word list
	std::vector <std::string> m_word_list;

//RNG - random number generator
	std::random_device m_rd;
	std::mt19937 m_rng;

//Gameplay																
    unsigned char m_char_input;
	static EntityManager* s_entityMan;

//Functions
	void initBackground() override;
	void initButtons()	  override;
	void initBoard();
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