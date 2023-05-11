/*******************************************************************//*
 * Implementation of the EnemyShootComponent class.
 *
 *********************************************************************/

#include <headers/ECS/Shoot/EnemyShootComponent.hpp>

#include <headers/Global.hpp>
#include <headers/ApplicationManager/ResourceMethodManager.hpp>
#include <headers/ECS/Text/BulletEnemyTextComponent.hpp>
#include <headers/ECS/Collision/BulletEnemyCollisionComponent.hpp>

EnemyShootComponent::EnemyShootComponent(std::mt19937* rng) {
    s_rng = rng;
    m_has_shot = false;
}

EnemyShootComponent::~EnemyShootComponent() {}

void EnemyShootComponent::init() {}

void EnemyShootComponent::update() {}

void EnemyShootComponent::render() {}

Entity& EnemyShootComponent::createBulletEnemy(const char& ch, const Vector2D& start_pos, const Vector2D& direction) {
	auto& p_bullet (entity->getManager().addEntity());

	p_bullet.addComponent<TransformComponent>(start_pos,
                                              true,
                                              direction,
                                              BULLET_SPEED);
	p_bullet.addComponent<SpriteComponent>(bullet_enemy, BULLET_SRC, BULLET_ENEMY_SIZE);

	std::string str;	str += ch;
	p_bullet.addComponent<BulletEnemyTextComponent>(str, yoster);
    p_bullet.addComponent<BulletEnemyCollisionComponent>(BULLET_ENEMY_SIZE);

	p_bullet.addGroup(GBulletEnemy);

	return p_bullet;
}

void EnemyShootComponent::shoot() {
    if (!m_has_shot) {
        std::uniform_int_distribution<int> uni(0, MAX_RANDOM_NUMBER);
        if (uni(*s_rng) % ENEMY_FIRE_CHANCE == 0) {
            char ch = char(uni(*s_rng) % 26 + 65);

            Vector2D rec = this->entity->getComponent<TransformComponent>().getPosition();
            createBulletEnemy(ch, rec, PLAYER_POS);

            AudioManager::playSound(SoundID::enemy_shoot);

            m_has_shot = true;
        }
    }
}