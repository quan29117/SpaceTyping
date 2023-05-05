#include <headers/ECS/EnemyShootComponent.hpp>

#include <headers/Global.hpp>
#include <headers/GameState/PlayState.hpp>
#include <headers/ECS/TransformComponent.hpp>
#include <headers/ECS/SpriteComponent.hpp>
#include <headers/ECS/TextComponent.hpp>

EnemyShootComponent::EnemyShootComponent(std::mt19937* rng) {
    s_rng = rng;
}

EnemyShootComponent::~EnemyShootComponent() {

}

Entity& createBulletEnemy(const char& ch, const Vector2D& pos, const Vector2D& dir) {
	auto& p_bullet (PlayState::getEntityManager()->addEntity());

	p_bullet.addComponent<TransformComponent>(pos, true, dir, BULLET_ENEMY_SPEED);
	p_bullet.addComponent<SpriteComponent>(bullet_enemy, BULLET_ENEMY_SIZE, BULLET_ENEMY_SIZE);

	std::string str;	str += ch;
	p_bullet.addComponent<TextComponent>(yoster, str, true, true, SDL_Color {255, 0, 0, 255});

	p_bullet.addGroup(GBulletEnemy);

	return p_bullet;
}

void EnemyShootComponent::shoot() {
    Vector2D rec = this->entity->getComponent<TransformComponent>().getPosition();
    if (rec.x > WINDOW_SIZE_WIDTH / 2.0f) {
        std::uniform_int_distribution<int> uni(0, ENEMY_FIRE_CHANCE);
        if (uni(*s_rng) == 0) {
            char ch = char(uni(*s_rng) % 26 + 65);
            createBulletEnemy(ch, rec, PLAYER_CENTER);
        }
    }
}