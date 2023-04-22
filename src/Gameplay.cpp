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

void GamePlay::initBackground() {
	m_bg_texture = Game::getResourceManager()->getTexture(gameplay_bg);
	camera.x = 0;
    camera.y = 0;
    camera.w = WINDOW_SIZE_WIDTH;
    camera.h = WINDOW_SIZE_HEIGHT;
}

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
	initBackground();
	initProgress();
	initTime();
	initWordList();
	
	m_player.addComponent<TransformComponent>(PLAYER_POS_X, PLAYER_POS_Y);
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
	elapsedS = end - start;
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
	playerShoot();
	enemyShoot();
	scrollBackground();
	char_input = '\0';
}

void GamePlay::render() {
	SDL_RenderClear(Game::getRenderer());

	SDL_FRect dest;
    dest.x = 0;
    dest.y = 0;
    dest.w = 1920;
    dest.h = 1080;

	if (!pause) {
		TextureManager::render(m_bg_texture, &dest, &camera);
		manager.render();
	}

	SDL_RenderPresent(Game::getRenderer());
}

Entity& createBulletPlayer(const EntityGroup& EG, const char& ch, const Vector2D& dir) {
	auto& p_bullet (manager.addEntity());

	p_bullet.addComponent<TransformComponent>(BULLET_PLAYER_START_POS_X, BULLET_PLAYER_START_POS_Y, true, dir.x, dir.y, BULLET_PLAYER_SPEED);
	p_bullet.addComponent<SpriteComponent>(bullet_player, BULLET_PLAYER_SIZE, BULLET_PLAYER_SIZE);

	std::stringstream ss;
	ss << ch;
	p_bullet.addComponent<TextComponent>(yoster, ss.str(), false);

	p_bullet.addGroup(EG);

	return p_bullet;
}

void GamePlay::playerShoot() {
	if (char_input != '\0') {
		for (auto& bullet : manager.getEntitesByGroup(GBulletEnemy)) {
			if (char_input == bullet->getComponent<TextComponent>().getCharNeedTyped()) {
				Vector2D dir = bullet->getComponent<TransformComponent>().position;
				createBulletPlayer(GBulletPlayer_B, char_input, dir);
				//TODO : shooting audio
				bullet->getComponent<TextComponent>().eraseFirstChar();
				char_input = '\0';
				break;
			}
		}
	}

	if (char_input != '\0') {
		for (auto& enemy : manager.getEntitesByGroup(GEnemy)) {
			if (char_input == enemy->getComponent<TextEnemyComponent>().getCharNeedTyped()) {
				Vector2D dir = enemy->getComponent<TransformComponent>().position;
				createBulletPlayer(GBulletPlayer_E, char_input, dir);
				//TODO : shooting audio
				enemy->getComponent<TextEnemyComponent>().eraseFirstChar();
				char_input = '\0';
				break;
			}
		}
	}
}

Entity& createEnemy(const int& pos_x, const int& pos_y, const std::string& text) {
	auto& e_enemy (manager.addEntity());

	e_enemy.addComponent<TransformComponent>(pos_x, pos_y, true, 10, 410, ENEMY_SPEED);
	e_enemy.addComponent<SpriteComponent>(enemy, ENEMY_WIDTH, ENEMY_HEIGHT);
	e_enemy.addComponent<TextEnemyComponent>(yoster, text);

	e_enemy.addGroup(GEnemy);

	return e_enemy;
}

void GamePlay::spawnEnemy() {
	if (elapsedS >= 5 && manager.getEntitesByGroup(GEnemy).size() < 7) {
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

Entity& createBulletEnemy(const char& ch, const Vector2D& pos, const Vector2D& dir) {
	auto& p_bullet (manager.addEntity());

	p_bullet.addComponent<TransformComponent>(pos.x, pos.y, true, dir.x, dir.y, BULLET_ENEMY_SPEED);
	p_bullet.addComponent<SpriteComponent>(bullet_enemy, BULLET_ENEMY_SIZE, BULLET_ENEMY_SIZE);

	std::string str;	str += ch;
	p_bullet.addComponent<TextComponent>(yoster, str, true, SDL_Color {255, 0, 0, 255});

	p_bullet.addGroup(GBulletEnemy);

	return p_bullet;
}

void GamePlay::enemyShoot() {
	for (auto& enemy : manager.getEntitesByGroup(GEnemy)) {
		auto& rec = enemy->getComponent<TransformComponent>().position;
		if (rec.x > WINDOW_SIZE_WIDTH / 2.0f) {
			std::uniform_int_distribution<int> uni(0, ENEMY_FIRE_CHANCE);
			if (uni(rng) == 0) {
				char ch = char(uni(rng) % 26 + 65);
				createBulletEnemy(ch, rec, Vector2D(PLAYER_POS_X, PLAYER_POS_Y));
			}
		}
	}
}

void GamePlay::scrollBackground() {
	if (!pause) {
		camera.x++;
        if (camera.x >= GAMEPLAY_BACKGROUND_WIDTH) {
            camera.x = 1;
        }
	}
}