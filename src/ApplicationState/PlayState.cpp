/*******************************************************************//*
 * Implementation of the PlayState class.
 *
 *********************************************************************/

#include <headers/ApplicationState/PlayState.hpp>

#include <headers/Global.hpp>
#include <headers/Application.hpp>
#include <headers/ECS/Components.hpp>
#include <headers/ApplicationManager/ResourceMethodManager.hpp>

//Define static members
bool		   PlayState::s_is_won    = false; 	
EntityManager* PlayState::s_entityMan = new EntityManager;

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
	m_spawnMan = new SpawnManager;
}

PlayState::PlayState()
	: m_char_input ('\0')
{
	initState(play_state);
	initBoard();
	initPlayer();
	initCollsionManager();
}

PlayState::~PlayState() {
	s_entityMan->clear();
}

bool PlayState::getWinning() {
	return s_is_won;
}

EntityManager* PlayState::getEntityManager() {
	return s_entityMan;
}

void PlayState::run()
{
	pollEvent();
	update();
	render();
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

		updateManager();
		shooting();
		scrollBackground();
		loadProgress();
		loadWinning();
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

void PlayState::updateManager() {
	m_collisionMan->update();
	m_spawnMan->update();
	s_entityMan->update();
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

void PlayState::loadProgress() {
	std::size_t sc = m_player->getComponent<ProgressComponent>().getScore();
	std::size_t wt = m_player->getComponent<ProgressComponent>().getWrongCount();

	Application::setProgress(sc, wt);

	if (Application::getScore() >= 10000 && s_entityMan->getEntitesByGroup(GEnemy).size() == 0
			&& s_entityMan->getEntitesByGroup(GExplosion).size() == 0)
		s_is_won = true;
}

void PlayState::loadWinning() {
	if (s_is_won) {
		Application::getStateManager()->pushState(result_state);
		s_is_won = false;
	}
}

void PlayState::resetCharInput() {
	if (m_char_input != '\0') {
		m_player->getComponent<ProgressComponent>().increaseWT(1);
		m_char_input = '\0';
	}
}