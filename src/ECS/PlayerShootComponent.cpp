#include <headers/ECS/PlayerShootComponent.hpp>

#include <headers/Global.hpp>
#include <headers/GameState/PlayState.hpp>
#include <headers/ECS/TransformComponent.hpp>
#include <headers/ECS/SpriteComponent.hpp>
#include <headers/ECS/TextComponent.hpp>

PlayerShootComponent::PlayerShootComponent(unsigned char* char_input) {
    s_char_input = char_input;
}

PlayerShootComponent::~PlayerShootComponent() {

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
	if (*s_char_input != '\0' && PlayState::getEntityManager()->getEntitesByGroup(GEnemy).size() > 0) {
		auto& x = PlayState::getEntityManager()->getEntitesByGroup(GEnemy)[0];
		if (*s_char_input == x->getComponent<TextComponent>().getCharNeedTyped()) {
			Vector2D dir = x->getComponent<TransformComponent>().getPosition();
			createBulletPlayer(GBulletPlayer_E, *s_char_input, dir);
			//TODO : shooting audio
			x->getComponent<TextComponent>().Typed();
			*s_char_input = '\0';
		}
	}
}

void PlayerShootComponent::shootBulletEnemy() {
	if (*s_char_input != '\0') {
		for (auto& x : PlayState::getEntityManager()->getEntitesByGroup(GBulletEnemy)) {
			if (*s_char_input == x->getComponent<TextComponent>().getCharNeedTyped()) {
				Vector2D dir = x->getComponent<TransformComponent>().getPosition();
				createBulletPlayer(GBulletPlayer_B, *s_char_input, dir);
				//TODO : shooting audio
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