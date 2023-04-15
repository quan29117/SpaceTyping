#include <headers/Gameplay.hpp>

EntityManager manager;
Entity& m_player = manager.addEntity();
Entity& m_enemy = manager.addEntity();

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
	m_player.addComponent<ColliderComponent>("player");

	m_enemy.addComponent<TransformComponent>(1000, 100, true, 10, 410, 10);
	m_enemy.addComponent<SpriteComponent>(enemy, ENEMY_WIDTH, ENEMY_HEIGHT);
	m_enemy.addComponent<ColliderComponent>("enemy");
}

GamePlay::~GamePlay() {
	// delete player;
	// delete enemy_system;
	// delete pause_menu;
}

void GamePlay::run(std::queue <State*>& states)
{
	pollEvent();
	updateGame();
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
				char_input = event.text.text[0];
				std::cout << char_input;
				break;
			
		}
	}
}

void GamePlay::updateGame() {
	manager.refresh();
	manager.update();

	if (Collision::AABB(m_player.getComponent<SpriteComponent>().getHitBox(),
						m_enemy.getComponent<SpriteComponent>().getHitBox()))
	{
		m_player.destroy();
		m_enemy.destroy();
	}
}

void GamePlay::render() {
	SDL_RenderClear(Game::getRenderer());

	if (!pause) {
		manager.render();
	}

	SDL_RenderPresent(Game::getRenderer());
}

void GamePlay::spawnEnemies() {
	
}