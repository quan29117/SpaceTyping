#include <headers/Gameplay.hpp>

EntityManager manager;
Entity& player = manager.addEntity();
Entity& enemy = manager.addEntity();

void GamePlay::initPtr() {
	// player = new Player(renderer);
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

	player.addComponent<TransformComponent>(PLAYER_START_POS_X, PLAYER_START_POS_Y);
	player.addComponent<SpriteComponent>("Player.png", PLAYER_WIDTH, PLAYER_HEIGHT);

	enemy.addComponent<TransformComponent>(1000, 100, true, 10, 410, 10);
	enemy.addComponent<SpriteComponent>("Enemy.png", ENEMY_WIDTH, ENEMY_HEIGHT);
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
	manager.update();
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