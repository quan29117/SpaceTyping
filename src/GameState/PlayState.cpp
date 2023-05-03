#include <headers/GameState/PlayState.hpp>

#include <fstream>
#include <headers/Application.hpp>
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

void PlayState::initInheritance() {
	m_name = StateName::play;
	m_close = m_pause = false;
}

void PlayState::initBackground() {
	m_bg_texture = Application::getResourceManager()->getTexture(play_bg);

	m_camera.x = 0;
    m_camera.y = 0;
    m_camera.w = WINDOW_SIZE_WIDTH;
    m_camera.h = WINDOW_SIZE_HEIGHT;

	m_bg_dest.x = 0;
    m_bg_dest.y = 0;
    m_bg_dest.w = 1920;
    m_bg_dest.h = 1080;
}

void PlayState::initTime() {
	start = end = spawnTime = 0;
}

void PlayState::initWordList() {
	std::ifstream file(PATH_BEGIN + "words.txt");
	std::string word;
	if (file.is_open())
		while (file >> word)
			m_word_list.push_back(word);
	file.close();
}

void PlayState::initPlayer() {
	m_player.addComponent<TransformComponent>(PLAYER_POS_X, PLAYER_POS_Y);
	m_player.addComponent<SpriteComponent>(player, PLAYER_WIDTH, PLAYER_HEIGHT);
	// m_player.addComponent<ColliderComponent>("player");
	// m_player.addComponent<LockEnemyComponent>();
}

PlayState::PlayState()
	: rng(rd()), point (0), char_input ('\0')
{
	initInheritance();
	initBackground();
	initTime();
	initWordList();
	initPlayer();
}

PlayState::~PlayState() {
	
}

void PlayState::run()
{
	pollEvent();
	if (!m_pause) update();
	render();

	updateTime();
}

void PlayState::pollEvent() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				m_close = true;
				break;

			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					if (!m_close) {
						m_pause = true;
						Application::getStateManager()->pushState(StateName::pause);
					}
				break;
			
			case SDL_TEXTINPUT:
				if (!m_pause)
					char_input = event.text.text[0];
				break;
		}
	}
}

void PlayState::update() {
	manager.update();
	manager.refresh();

	spawnEnemy();
	shooting();
	updateCollision();
	scrollBackground();
	
	char_input = '\0';
}

void PlayState::render() {
	SDL_RenderClear(Application::getRenderer());

	if (!m_pause) {
		TextureManager::render(m_bg_texture, &m_bg_dest, &m_camera);
		manager.render();
	}

	SDL_RenderPresent(Application::getRenderer());
}

void PlayState::updateTime() {
	end = SDL_GetTicks() / 1000.f;
	spawnTime = end - start;
}

Entity& createBulletPlayer(const EntityGroup& EG, const char& ch, const Vector2D& dir) {
	auto& p_bullet (manager.addEntity());

	p_bullet.addComponent<TransformComponent>(BULLET_PLAYER_START_POS_X, BULLET_PLAYER_START_POS_Y, true, dir.x, dir.y, BULLET_PLAYER_SPEED);
	p_bullet.addComponent<SpriteComponent>(bullet_player, BULLET_PLAYER_SIZE, BULLET_PLAYER_SIZE);

	std::string str; str += ch;
	p_bullet.addComponent<TextComponent>(yoster, str, false, false);

	p_bullet.addGroup(EG);

	return p_bullet;
}

void playerShoot(unsigned char& char_input, const EntityGroup& bulletGroup, const EntityGroup& enemyGroup) {
	if (char_input != '\0') {
		for (auto& x : manager.getEntitesByGroup(enemyGroup)) {
			if (char_input == x->getComponent<TextComponent>().getCharNeedTyped()) {
				Vector2D dir = x->getComponent<TransformComponent>().position;
				createBulletPlayer(bulletGroup, char_input, dir);
				//TODO : shooting audio
				x->getComponent<TextComponent>().Typed();
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
	e_enemy.addComponent<TextComponent>(yoster, text, false);

	e_enemy.addGroup(GEnemy);

	return e_enemy;
}

void PlayState::spawnEnemy() {
	if (spawnTime >= 5 && manager.getEntitesByGroup(GEnemy).size() < 7) {
		std::uniform_int_distribution<int> uni(0, WINDOW_SIZE_HEIGHT);

		std::string text = "";
		for (int i = 0; i <= uni(rng) % 2; i++)  
			text += m_word_list[uni(rng) % m_word_list.size()] + " ";
		text.erase(text.size() - 1, 1);
		
		createEnemy(WINDOW_SIZE_WIDTH, uni(rng), text);

	//reset the time
		spawnTime = 0;
		start = end;
	}
}

Entity& createBulletEnemy(const char& ch, const Vector2D& pos, const Vector2D& dir) {
	auto& p_bullet (manager.addEntity());

	p_bullet.addComponent<TransformComponent>(pos.x, pos.y, true, dir.x, dir.y, BULLET_ENEMY_SPEED);
	p_bullet.addComponent<SpriteComponent>(bullet_enemy, BULLET_ENEMY_SIZE, BULLET_ENEMY_SIZE);

	std::string str;	str += ch;
	p_bullet.addComponent<TextComponent>(yoster, str, true, true, SDL_Color {255, 0, 0, 255});

	p_bullet.addGroup(GBulletEnemy);

	return p_bullet;
}

void PlayState::enemyShoot() {
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

void PlayState::shooting() {
	playerShoot(char_input, GBulletPlayer_E, GEnemy);
	playerShoot(char_input, GBulletPlayer_B, GBulletEnemy);
	enemyShoot();
}

void collisionPlayer(const EntityGroup& group) {
	/**
		Collision between Player and Enemy & BulletEnemy
	  */

	for (auto& x : manager.getEntitesByGroup(group)) {
		if (Collision::AABB(m_player, *x)) {
			// m_player.destroy();
			x->destroy();
		}
	}
}

void collisionBulletPlayer(const EntityGroup& bulletGroup, const EntityGroup& enemyGroup) {
	/**
		Collision between BulletPlayer and Enemy / BulletEnemy
	  */

	for (auto& bullet : manager.getEntitesByGroup(bulletGroup)) {
		for (auto& x : manager.getEntitesByGroup(enemyGroup)) {
			if (bullet->getComponent<TextComponent>().getFirstChar() == x->getComponent<TextComponent>().getFirstChar()
				&& Collision::AABB(*bullet, *x))
			{
				bullet->destroy();
				x->getComponent<TextComponent>().Shot();
			}
		}
	}
}

void PlayState::updateCollision() {
	collisionPlayer(GEnemy);
	collisionPlayer(GBulletEnemy);
	collisionBulletPlayer(GBulletPlayer_E, GEnemy);
	collisionBulletPlayer(GBulletPlayer_B, GBulletEnemy);
}

void PlayState::scrollBackground() {
	if (!m_pause) {
		m_camera.x++;
        if (m_camera.x >= PLAYSTATE_BACKGROUND_WIDTH)
            m_camera.x = 1;
	}
}

