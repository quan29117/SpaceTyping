/*******************************************************************//*
 * Implementation of the PlayState class.
 *
 *********************************************************************/

#include <headers/ApplicationState/PlayState.hpp>

#include <fstream>
#include <headers/Application.hpp>
#include <headers/Global.hpp>
#include <headers/ECS/Components.hpp>
#include <headers/ApplicationManager/ResourceMethodManager.hpp>

//Define static members
EntityManager* 	  PlayState::s_entityMan    = new EntityManager;

void PlayState::initBackground() {
	m_bg_texture = Application::getResourceManager()->getTexture(play_bg);

	m_camera  = CAMERA_RECT;
	m_bg_dest = BACKGROUND_DEST;
}

void PlayState::initButtons() {}

void PlayState::initBoard() {
	m_board_texture = Application::getResourceManager()->getTexture(board);
	m_board_dest	= BOARD_DEST;
}

void PlayState::initTime() {
	start = SDL_GetTicks() / 1000.f;
	spawnTime = 0;
	spawnCoolDown = 3;
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
	m_player = &s_entityMan->addEntity();
	m_player->addComponent<TransformComponent>(PLAYER_POS);
	m_player->addComponent<SpriteComponent>(player, PLAYER_SRC, PLAYER_SIZE, true);
	m_player->addComponent<PlayerShootComponent>(&m_char_input);
	m_player->addComponent<ProgressComponent>();
	m_player->addComponent<PlayerCollisionComponent>(PLAYER_SIZE);

	m_player->getComponent<SpriteComponent>().addAnimation("Idle", 0, 5, 60);
	m_player->getComponent<SpriteComponent>().playAnimation("Idle");
}

void PlayState::initCollsionManager() {
	m_collisionMan = new CollisionManager(m_player);
}

PlayState::PlayState()
	: m_rng(m_rd()), m_char_input ('\0')
{
	initState(play_state);
	initBoard();
	initTime();
	initWordList();
	initPlayer();
	initCollsionManager();
}

PlayState::~PlayState() {
	s_entityMan->clear();
}

EntityManager* PlayState::getEntityManager() {
	return s_entityMan;
}

void PlayState::run()
{
	pollEvent();
	update();
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
			
			case SDL_TEXTINPUT:
				if (!m_pause)
					m_char_input = event.text.text[0];
				break;
			
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					if (!m_close) {
						m_pause = true;
						Application::getStateManager()->pushState(pause_state);
					}
		}
	}
}

void PlayState::update() {
	if (!m_pause) {
		updateInteraction();
		
		m_collisionMan->update();
		s_entityMan->update();
		
		spawnEnemy();
		shooting();
		scrollBackground();
		resetCharInput();
		
		AudioManager::loopMusic();
	}
}

void PlayState::render() {
	SDL_RenderClear(Application::getRenderer());

	if (!m_pause) {
		TextureManager::render(m_bg_texture, &m_camera, &m_bg_dest);
		TextureManager::render(m_board_texture, nullptr, &m_board_dest);
		s_entityMan->render();
		m_mouse.render();
	}

	SDL_RenderPresent(Application::getRenderer());
}

void PlayState::updateTime() {
	end = SDL_GetTicks() / 1000.f;

	if (!m_pause)
		spawnTime = end - start;
	else start = end - spawnTime;
}

Entity& createEnemy(std::mt19937& m_rng, const std::string& text) {
	std::uniform_int_distribution<int> uni(0, MAX_RANDOM_NUMBER);
	float start_pos_y = uni(m_rng) % WINDOW_SIZE_HEIGHT;

	auto& e_enemy (PlayState::getEntityManager()->addEntity());

	e_enemy.addComponent<TransformComponent>(Vector2D {ENEMY_START_POS_X, start_pos_y},
											 true,
											 PLAYER_POS,
											 ENEMY_SPEED);
	e_enemy.addComponent<SpriteComponent>(enemy, ENEMY_SRC, ENEMY_SIZE);
	e_enemy.addComponent<EnemyTextComponent>(text, yoster);
	e_enemy.addComponent<EnemyShootComponent>(&m_rng);
	e_enemy.addComponent<EnemyCollisionComponent>(ENEMY_SIZE);
	e_enemy.addComponent<ExplosionComponent>();

	e_enemy.addGroup(GEnemy);

	return e_enemy;
}

std::string PlayState::generatedWords() {
	std::uniform_int_distribution<int> uni(0, MAX_RANDOM_NUMBER);

	int countWord = uni(m_rng) % 2 + 1;
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
		text += m_word_list[uni(m_rng) % m_word_list.size()] + " ";
	text.erase(text.size() - 1, 1);

	return text;
}

void PlayState::spawnEnemy() {
	if (spawnTime >= spawnCoolDown && PlayState::getEntityManager()->getEntitesByGroup(GEnemy).size() < 7) {
		std::string text = generatedWords();
		createEnemy(m_rng, text);

	//reset the time
		spawnTime = 0;
		start = end;
	}
}

void PlayState::shooting() {
	m_player->getComponent<PlayerShootComponent>().shoot();
	for (auto& enemy : PlayState::getEntityManager()->getEntitesByGroup(GEnemy))
		enemy->getComponent<EnemyShootComponent>().shoot();
}

void PlayState::scrollBackground() {
	if (!m_pause) {
		m_camera.x++;
        if (m_camera.x >= PLAYSTATE_BACKGROUND_WIDTH)
            m_camera.x = 1;
	}
}

void PlayState::resetCharInput() {
	if (m_char_input != '\0') {
		m_player->getComponent<ProgressComponent>().increaseWT(1);
		m_char_input = '\0';
	}
}