#include <headers/Gameplay.hpp>

#include <headers/Game.hpp>
#include <headers/Global.hpp>
#include <headers/ECS/Components.hpp>
#include <headers/Structs.hpp>

EntityManager manager;
Entity& m_player = manager.addEntity();
// Entity& m_enemy = manager.addEntity();

enum EntityGroup : std::size_t {
	GEnemy,
	GBulletPlayer_B,	//BulletPlayer to defeat BulletEnemy
	GBulletPlayer_E,	//BulletPlayer to defeat Enemy
	GBulletEnemy,
};

void GamePlay::initPtr() {
	// m_player = new Player(renderer);
	// enemy_system = new EnemySystem;
	// pause_menu = new PauseMenu(i_res);
}

void GamePlay::initProgress() {
	stage = 1;
	point = 0;
	char_input = '\0';
}

GamePlay::GamePlay()
	: rng(rd())
{
	initPtr();
	initProgress();
	
	m_player.addComponent<TransformComponent>(PLAYER_START_POS_X, PLAYER_START_POS_Y);
	m_player.addComponent<SpriteComponent>(player, PLAYER_WIDTH, PLAYER_HEIGHT);
	// m_player.addComponent<ColliderComponent>("player");

}

GamePlay::~GamePlay() {
	// delete player;
	// delete enemy_system;
	// delete pause_menu;
}

void GamePlay::run(std::queue <State*>& states)
{
	pollEvent();
	if (!pause)	updateGame();
	render();
}

void GamePlay::pollEvent() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				close = true;
				break;

			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					if (!close) pause = !pause;
				break;
			
			case SDL_TEXTINPUT:
				if (!pause)
					char_input = event.text.text[0];
				break;
			
		}
	}
}

Entity& creatEnemy(const int& a, const int& b) {
	auto& e_enemy (manager.addEntity());

	e_enemy.addComponent<TransformComponent>(a, b, false, 10, 410, 10);
	e_enemy.addComponent<SpriteComponent>(enemy, ENEMY_WIDTH, ENEMY_HEIGHT);
	e_enemy.addComponent<TextComponent>(yoster, "abc");

	e_enemy.addGroup(GEnemy);

	return e_enemy;
}

void GamePlay::updateGame() {
	manager.update();
	manager.refresh();
	
	if (char_input == 'm') {
		creatEnemy(10, 410);
		char_input = '\0';
		std::cout << "mcreate\n";
	}
	
	if (char_input == 'n') {
		creatEnemy(1000, 410);
		char_input = '\0';
		std::cout << "ncreate\n";
	}
}
void GamePlay::render() {
	SDL_RenderClear(Game::getRenderer());

	if (!pause) {
		manager.render();
	}

	SDL_RenderPresent(Game::getRenderer());
}