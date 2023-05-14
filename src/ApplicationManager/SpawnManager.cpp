/*******************************************************************//*
 * Implementation of the SpawnManager class.
 *
 *********************************************************************/

#include <headers/ApplicationManager/SpawnManager.hpp>

#include <fstream>
#include <headers/Global.hpp>
#include <headers/Application.hpp>
#include <headers/ApplicationState/PlayState.hpp>
#include <headers/ECS/HPP/EnemyComponents.hpp>
#include <headers/ECS/Collision/EnemyCollisionComponent.hpp>

SpawnManager::SpawnManager()
    : m_rng(m_rd()), m_spawn_CD(2)
{
    initWordList();
    m_last_spawn = std::chrono::system_clock::now();
}

SpawnManager::~SpawnManager() {}

void SpawnManager::initWordList() {
	std::ifstream file(PATH_BEGIN + "words.txt");
	std::string word;
	if (file.is_open())
		while (file >> word)
			m_word_list.push_back(word);
	file.close();
}

bool SpawnManager::canSpawn() {
	if (Application::getScore() >= 10000)
		return false;

    TimePoint curTime = std::chrono::system_clock::now();
    m_elapsed_seconds += curTime - m_last_spawn;
	m_last_spawn = curTime;
    if (m_elapsed_seconds.count() < m_spawn_CD)
        return false;
	
	if (PlayState::getEntityManager()->getEntitesByGroup(GEnemy).size() >= 7) 
		return false;
	
    m_elapsed_seconds = std::chrono::duration<double>(0);
	return true;
}

std::string SpawnManager::generatedWords() {
    std::uniform_int_distribution<int> uni(0, MAX_RANDOM_NUMBER);

	int countWord = uni(m_rng) % 2 + 1;
	switch (countWord) {
		case 1:
			m_spawn_CD = 2;
			break;

		case 2:
			m_spawn_CD = 3;
			break;
	}

	std::string text = "";
	for (int i = 1; i <= countWord; i++)
		text += m_word_list[uni(m_rng) % m_word_list.size()] + " ";
	text.erase(text.size() - 1, 1);

	return text;
}

Entity& SpawnManager::createEnemy() {
    auto& e_enemy (PlayState::getEntityManager()->addEntity());

    std::uniform_int_distribution<int> uni(0, MAX_RANDOM_NUMBER);
	float start_pos_y = uni(m_rng) % WINDOW_SIZE_HEIGHT;

	e_enemy.addComponent<TransformComponent>(Vector2D {ENEMY_START_POS_X, start_pos_y},
											 true,
											 PLAYER_POS,
											 ENEMY_SPEED);
	e_enemy.addComponent<SpriteComponent>(enemy, ENEMY_SRC, ENEMY_SIZE);
	e_enemy.addComponent<EnemyTextComponent>(generatedWords(), pixel_30);
	e_enemy.addComponent<EnemyShootComponent>(&m_rng);
	e_enemy.addComponent<EnemyCollisionComponent>(ENEMY_SIZE);
	e_enemy.addComponent<ExplosionComponent>();

	e_enemy.addGroup(GEnemy);

	return e_enemy;
}

void SpawnManager::update() {
    if (canSpawn()) 
        createEnemy();
}
