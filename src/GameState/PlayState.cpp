#include <headers/GameState/PlayState.hpp>

#include <fstream>
#include <headers/Application.hpp>
#include <headers/Global.hpp>
#include <headers/ECS/Components.hpp>
#include <headers/Structs.hpp>

// EntityManager manager;
EntityManager* PlayState::s_manager = new EntityManager;
Entity& m_player = PlayState::getEntityManager()->addEntity();

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

void PlayState::initButtons() {

}

void PlayState::initTime() {
	start = end = spawnTime = 0;
	spawnCoolDown = 5;
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
	m_player.addComponent<TransformComponent>(PLAYER_POS);
	m_player.addComponent<SpriteComponent>(player, PLAYER_WIDTH, PLAYER_HEIGHT);
	// m_player.addComponent<ColliderComponent>("player");
	m_player.addComponent<PlayerShootComponent>(&s_char_input);
}

PlayState::PlayState()
	: rng(rd()), m_score(0), s_char_input ('\0')
{
	initState(StateName::play);
	initTime();
	initWordList();
	initPlayer();
}

PlayState::~PlayState() {
	
}

unsigned char& PlayState::getCharInput() {
	return s_char_input;
}

EntityManager* PlayState::getEntityManager() {
	return s_manager;
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
				Application::closeApp();
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
					s_char_input = event.text.text[0];
				break;
		}
	}
}

void PlayState::update() {
	PlayState::getEntityManager()->update();
	PlayState::getEntityManager()->refresh();

	spawnEnemy();
	shooting();
	updateCollision();
	scrollBackground();
	
	s_char_input = '\0';
}

void PlayState::render() {
	SDL_RenderClear(Application::getRenderer());

	if (!m_pause) {
		TextureManager::render(m_bg_texture, &m_bg_dest, &m_camera);
		PlayState::getEntityManager()->render();
	}

	SDL_RenderPresent(Application::getRenderer());
}

void PlayState::updateTime() {
	end = SDL_GetTicks() / 1000.f;
	spawnTime = end - start;
}

Entity& createEnemy(const int& start_pos_y, const std::string& text) {
	auto& e_enemy (PlayState::getEntityManager()->addEntity());

	e_enemy.addComponent<TransformComponent>(Vector2D {ENEMY_START_POS_X, start_pos_y},
											 true,
											 PLAYER_CENTER,
											 ENEMY_SPEED);
	e_enemy.addComponent<SpriteComponent>(enemy, ENEMY_WIDTH, ENEMY_HEIGHT);
	e_enemy.addComponent<TextComponent>(yoster, text, false);
	// e_enemy.addComponent<EnemyShootComponent>();	//TODO  : add reference of rng

	e_enemy.addGroup(GEnemy);

	return e_enemy;
}

void PlayState::spawnEnemy() {
	if (spawnTime >= spawnCoolDown && PlayState::getEntityManager()->getEntitesByGroup(GEnemy).size() < 7) {
		std::uniform_int_distribution<int> uni(0, WINDOW_SIZE_HEIGHT);

		int countWord = uni(rng) % 2 + 1;
		switch (countWord) {
			case 1:
				spawnCoolDown = 2;
				break;

			case 2:
				spawnCoolDown = 3;
				break;
		}

		std::string text = "";
		for (int i = 1; i <= countWord; i++)  
			text += m_word_list[uni(rng) % m_word_list.size()] + " ";
		text.erase(text.size() - 1, 1);
		
		createEnemy(uni(rng), text);

	//reset the time
		spawnTime = 0;
		start = end;
	}
}

void PlayState::shooting() {
	m_player.getComponent<PlayerShootComponent>().shoot();
	for (auto& enemy : PlayState::getEntityManager()->getEntitesByGroup(GEnemy)) {
		// enemy->getComponent<EnemyShootComponent>().shoot();
	}
}

void collisionPlayer(const EntityGroup& group) {
	/**
		Collision between Player and Enemy & BulletEnemy
	  */

	for (auto& x : PlayState::getEntityManager()->getEntitesByGroup(group)) {
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

	for (auto& bullet : PlayState::getEntityManager()->getEntitesByGroup(bulletGroup)) {
		for (auto& x : PlayState::getEntityManager()->getEntitesByGroup(enemyGroup)) {
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

