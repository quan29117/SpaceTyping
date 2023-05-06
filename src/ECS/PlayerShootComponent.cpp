#include <headers/ECS/PlayerShootComponent.hpp>

#include <headers/Global.hpp>
#include <headers/Structs.hpp>
#include <headers/GameState/PlayState.hpp>
#include <headers/ECS/TransformComponent.hpp>
#include <headers/ECS/SpriteComponent.hpp>
#include <headers/ECS/TextComponent.hpp>

PlayerShootComponent::PlayerShootComponent(unsigned char* char_input) {
	m_lock_enemy = nullptr;
    s_char_input = char_input;
	s_enemyGroup = &PlayState::getEntityManager()->getEntitesByGroup(GEnemy);
	s_bulletEnemyGroup = &PlayState::getEntityManager()->getEntitesByGroup(GBulletEnemy);
}

PlayerShootComponent::~PlayerShootComponent() {

}

void PlayerShootComponent::update() {
	if (m_lock_enemy == nullptr && s_enemyGroup->size() > 0)
        for (auto& x : *s_enemyGroup) {
            if (!x->getComponent<TextComponent>().isFinished()) {
                m_lock_enemy = x;
                m_lock_enemy->getComponent<TextComponent>().setColor(SDL_Color {0, 130, 255, 255});
                break;
            }
        }

	if (m_lock_enemy != nullptr && m_lock_enemy->getComponent<TextComponent>().isFinished())
		m_lock_enemy = nullptr;
}

Entity& createBulletPlayer(const EntityGroup& EG, const char& ch, const Vector2D& direction) {
	auto& p_bullet (PlayState::getEntityManager()->addEntity());

	p_bullet.addComponent<TransformComponent>(BULLET_PLAYER_START_POS,
											  true,
											  direction,
											  BULLET_PLAYER_SPEED);
	p_bullet.addComponent<SpriteComponent>(bullet_player, BULLET_PLAYER_SIZE, BULLET_PLAYER_SIZE);

	std::string str; str += ch;
	p_bullet.addComponent<TextComponent>(yoster, str, false, false);

	p_bullet.addGroup(EG);

	return p_bullet;
}

void PlayerShootComponent::shootEnemy() {
	if (m_lock_enemy != nullptr)
		if (*s_char_input == m_lock_enemy->getComponent<TextComponent>().getCharNeedTyped()) {
			Vector2D dir = m_lock_enemy->getComponent<TransformComponent>().getPosition();
			createBulletPlayer(GBulletPlayer_E, *s_char_input, dir);
			AudioManager::playSound(SoundID::player_shoot);
			m_lock_enemy->getComponent<TextComponent>().Typed();
			*s_char_input = '\0';
		}
}

void PlayerShootComponent::shootBulletEnemy() {
	if (*s_char_input != '\0') {
		for (auto& x : *s_bulletEnemyGroup) {
			if (*s_char_input == x->getComponent<TextComponent>().getCharNeedTyped()) {
				Vector2D dir = x->getComponent<TransformComponent>().getPosition();
				createBulletPlayer(GBulletPlayer_B, *s_char_input, dir);
				AudioManager::playSound(SoundID::player_shoot);
				x->getComponent<TextComponent>().Typed();
				*s_char_input = '\0';
				break;
			}
		}
	}
}

void PlayerShootComponent::shoot() {
	shootBulletEnemy();
	shootEnemy();
}