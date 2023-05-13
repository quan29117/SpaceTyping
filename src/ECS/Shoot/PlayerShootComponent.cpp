/*******************************************************************//*
 * Implementation of the PlayerShootComponent class.
 *
 *********************************************************************/

#include <headers/ECS/Shoot/PlayerShootComponent.hpp>

#include <headers/Global.hpp>
#include <headers/ApplicationManager/ResourceMethodManager.hpp>
#include <headers/ECS/ProgressComponent.hpp>
#include <headers/ECS/HPP/BulletPlayerComponents.hpp>
#include <headers/ECS/Text/EnemyTextComponent.hpp>
#include <headers/ECS/Text/BulletEnemyTextComponent.hpp>

PlayerShootComponent::PlayerShootComponent(unsigned char* char_input) {
	m_lock_target = nullptr;
    s_char_input = char_input;
}

PlayerShootComponent::~PlayerShootComponent() {}

void PlayerShootComponent::init() {
	s_enemyGroup = &(entity->getManager().getEntitesByGroup(GEnemy));
	s_bulletEnemyGroup = &(entity->getManager().getEntitesByGroup(GBulletEnemy));
}

void PlayerShootComponent::update() {
//Lock_target
	if (m_lock_target == nullptr && s_enemyGroup->size() > 0)
        for (auto& enemy : *s_enemyGroup) 
            if (!enemy->getComponent<EnemyTextComponent>().isFinished()) {
                m_lock_target = enemy;
                m_lock_target->getComponent<EnemyTextComponent>().setColor(SDL_Color {0, 130, 255, 255});
                break;
            }

//Free lock_target
	if (m_lock_target != nullptr && m_lock_target->getComponent<EnemyTextComponent>().isFinished())
		m_lock_target = nullptr;
}

void PlayerShootComponent::render() {}

Entity& PlayerShootComponent::createBulletPlayer(const EntityGroup& EG, const CollisionID& id, const char& ch, const Vector2D& direction) {
	auto& p_bullet (entity->getManager().addEntity());

	p_bullet.addComponent<TransformComponent>(BULLET_PLAYER_START_POS,
											  true,
											  direction,
											  BULLET_SPEED);
	p_bullet.addComponent<SpriteComponent>(bullet_player, BULLET_SRC, BULLET_PLAYER_SIZE);

	std::string str; str += ch;
	p_bullet.addComponent<BulletPlayerTextComponent>(str);
	p_bullet.addComponent<BulletPlayerCollisionComponent>(BULLET_PLAYER_SIZE, id);

	p_bullet.addGroup(EG);

	return p_bullet;
}

void PlayerShootComponent::shootEnemy() {
	if (m_lock_target != nullptr)
		if (*s_char_input == m_lock_target->getComponent<EnemyTextComponent>().getCharNeedTyped()) {
			Vector2D dir = m_lock_target->getComponent<TransformComponent>().getPosition();
			createBulletPlayer(GBulletPlayer_E, BP_E_collision, *s_char_input, dir);

			AudioManager::playSound(SoundID::player_shoot);

			m_lock_target->getComponent<EnemyTextComponent>().Typed();
			entity->getComponent<ProgressComponent>().increaseScore(10);

			*s_char_input = '\0';
		}
}

void PlayerShootComponent::shootBulletEnemy() {
	if (*s_char_input >= 'A' && *s_char_input <= 'Z') {
		for (auto& bullet_enemy : *s_bulletEnemyGroup) {
			if (*s_char_input == bullet_enemy->getComponent<BulletEnemyTextComponent>().getCharNeedTyped()) {
				Vector2D dir = bullet_enemy->getComponent<TransformComponent>().getPosition();
				createBulletPlayer(GBulletPlayer_B, BP_B_collision, *s_char_input, dir);

				AudioManager::playSound(SoundID::player_shoot);

				bullet_enemy->getComponent<BulletEnemyTextComponent>().Typed();
				entity->getComponent<ProgressComponent>().increaseScore(20);

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