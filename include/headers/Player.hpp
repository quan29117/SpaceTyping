#pragma once 

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <headers/Global.hpp>

class Player {
private:
//SDL
    SDL_Texture* m_texture;
    SDL_FRect       m_pos;

//Game logic
    bool            m_destroyed;
    unsigned int    m_wrong_type;
    //Enemy*        lock_enemy;

//Bullets
	// std::vector <Bullet_Player*> bullet_BE;	//bullet to shoot enemies
	// std::vector <Bullet_Player*> bullet_BB; //bullet to shoot bullet enemy

//Functions
    void initSpec();
    void initImage(SDL_Renderer* renderer);

public:
    Player(SDL_Renderer* renderer);
    virtual ~Player();

    bool							getStatus();
	unsigned int					getWrongType();
    // std::vector <Bullet_Player*>&	getBE();
	// std::vector <Bullet_Player*>&	getBB();

    void dead();
    void update();
    void render(SDL_Renderer* renderer);
};