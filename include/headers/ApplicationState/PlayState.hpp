/*******************************************************************//*
 * ApplicationState class for the game.
 * This state is entered after clicking the "Start" button
 * from the menu state
 *
 *********************************************************************/

#pragma once

#include <headers/ApplicationState/State.hpp>
#include <headers/ECS/ECS.hpp>
#include <headers/ApplicationManager/CollisionManager.hpp>
#include <headers/ApplicationManager/SpawnManager.hpp>

class PlayState : public State {
private:
//Background camera
	SDL_Rect m_camera;

//Board score
	SDL_Texture* m_board_texture;
	SDL_FRect	 m_board_dest;

//Gameplay																
    unsigned char 		  m_char_input;
	static EntityManager* s_entityMan;
	CollisionManager* 	  m_collisionMan;
	SpawnManager*		  m_spawnMan;
	Entity* 			  m_player;

//Functions
	void initBackground() override;
	void initButtons()	  override;
	void initBoard();
	void initPlayer();
	void initCollsionManager();

	void pollEvent() override;
	void update()	 override;
	void render()	 override;

	void updateManager();
	void shooting();
	void scrollBackground();
	void resetCharInput();
	
public:			
    PlayState();
    virtual ~PlayState();

	static EntityManager* 	 getEntityManager();

    void run()		 override;
};
