/*******************************************************************//*
 * Implementation of the ExplosionManager struct.
 *
 *********************************************************************/

#include <headers/ApplicationManager/ExplosionManager.hpp>

#include <headers/Global.hpp>
#include <headers/ApplicationState/PlayState.hpp>
#include <headers/ECS/DeadAnimationComponent.hpp>
#include <headers/ApplicationManager/ResourceMethodManager.hpp>

Entity& ExplosionManager::createExplosion(const Vector2D& pos) {
    auto& e_explosion (PlayState::getEntityManager()->addEntity());

    e_explosion.addComponent<TransformComponent>(pos);
	e_explosion.addComponent<SpriteComponent>(explosion, EXPLOSION_SRC, EXPLOSION_SIZE, true);
    e_explosion.addComponent<DeadAnimationComponent>();

    e_explosion.getComponent<SpriteComponent>().addAnimation("explosion", 0, 8, 60);
    e_explosion.getComponent<SpriteComponent>().playAnimation("explosion");

    e_explosion.addGroup(GExplosion);

    AudioManager::playSound(explosion_sound);

    return e_explosion;
}