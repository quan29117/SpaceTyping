#include <headers/Gameplay.hpp>

#include <fstream>
#include <headers/Game.hpp>
#include <headers/Global.hpp>
#include <headers/ECS/Components.hpp>
#include <headers/Structs.hpp>

EntityManager manager;
Entity& m_player = manager.addEntity();

enum EntityGroup : std::size_t {
	GEnemy,
	GBulletPlayer_B,	//BulletPlayer to defeat BulletEnemy
	GBulletPlayer_E,	//BulletPlayer to defeat Enemy
	GBulletEnemy,
};

void GamePlay::initPtr() {
	// pause_menu = new PauseMenu(i_res);
}

void GamePlay::initProgress() {
	stage = 1;
	point = 0;
	char_input = '\0';
}

void GamePlay::initTime() {
	start = end = elapsedS = 0;
}

void GamePlay::initWordList() {
	std::ifstream file(PATH_BEGIN + "words.txt");
	std::string word;
	if (file.is_open())
		while (file >> word)
			word_list.push_back(word);
	file.close();
}

GamePlay::GamePlay()
	: rng(rd())
{
	initProgress();
	initTime();
	initWordList();
	
	m_player.addComponent<TransformComponent>(PLAYER_START_POS_X, PLAYER_START_POS_Y);
	m_player.addComponent<SpriteComponent>(player, PLAYER_WIDTH, PLAYER_HEIGHT);
	// m_player.addComponent<ColliderComponent>("player");

}

GamePlay::~GamePlay() {
	// delete pause_menu;
}

void GamePlay::run(std::queue <State*>& states)
{
	pollEvent();
	if (!pause) updateGame();
	render();

//Update time
	end = SDL_GetTicks() / 1000.f;
	elapsedS = (end - start);
	std::cout << start << " " << end << "\n";
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

void GamePlay::updateGame() {
	manager.update();
	manager.refresh();

	spawnEnemy();
}

Entity& createEnemy(const int& pos_x, const int& pos_y, const std::string& text) {
	auto& e_enemy (manager.addEntity());

	e_enemy.addComponent<TransformComponent>(pos_x, pos_y, true, 10, 410, 10);
	e_enemy.addComponent<SpriteComponent>(enemy, ENEMY_WIDTH, ENEMY_HEIGHT);
	e_enemy.addComponent<TextComponent>(yoster, text);

	e_enemy.addGroup(GEnemy);

	return e_enemy;
}

void GamePlay::spawnEnemy() {
	if (elapsedS >= 5) {
		std::uniform_int_distribution<int> uni(0, WINDOW_SIZE_HEIGHT);

		std::string text = "";
		for (int i = 0; i <= uni(rng) % 2; i++)  
			text += word_list[uni(rng) % word_list.size()] + " ";
		text.erase(text.size() - 1, 1);
		
		createEnemy(WINDOW_SIZE_WIDTH, uni(rng), text);

	//reset the time
		elapsedS = 0;
		start = end;
	}
}

void GamePlay::render() {
	SDL_RenderClear(Game::getRenderer());

	if (!pause) {
		manager.render();
	}

	SDL_RenderPresent(Game::getRenderer());
}