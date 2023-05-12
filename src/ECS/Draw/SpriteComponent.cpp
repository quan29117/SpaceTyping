/*******************************************************************//*
 * Implementation of the SpriteComponent class.
 *
 *********************************************************************/

#include <headers/ECS/Draw/SpriteComponent.hpp>

#include <headers/Application.hpp>
#include <headers/ApplicationManager/ResourceMethodManager.hpp>

SpriteComponent::SpriteComponent(const TextureID& id, const SDL_Rect& src, const Vector2D& destSize, const bool& animated) {
    m_texture = Application::getResourceManager()->getTexture(id);

    m_src = src;
    m_dest.w = destSize.x;
    m_dest.h = destSize.y;
    
    m_animated = animated;
}

SpriteComponent::~SpriteComponent() {}

SDL_FRect SpriteComponent::getRect() {
    return m_dest;
}

bool SpriteComponent::isEndAnimation() {
    return (m_src.x == m_src.w * (m_frames - 1));
}

void SpriteComponent::init() {
    if (entity->hasComponent<TransformComponent>()) {
        transform = &entity->getComponent<TransformComponent>();
        m_dest.x = transform->getPosition().x;
        m_dest.y = transform->getPosition().y;
    }
    else std::cout << "No TransformComponent\n";
}

void SpriteComponent::update() {
    if (m_animated) {
        m_src.y = m_dest.h * m_anim_index;
        m_src.x = m_src.w * static_cast<int> ((SDL_GetTicks() / m_speed) % m_frames);
    }

    m_dest.x = transform->getPosition().x;
    m_dest.y = transform->getPosition().y;
}

void SpriteComponent::render() {
    if (m_texture != nullptr)
        TextureManager::render(m_texture, &m_src, &m_dest);
}

void SpriteComponent::addAnimation(const std::string& name, const unsigned int& i, const unsigned int& f, const unsigned int& s) {
    Animation anim = Animation (i,f,s);
    animations.emplace(name, anim);
}

void SpriteComponent::playAnimation(const std::string& name) {
    m_anim_index = animations[name].getIndex();
    m_frames     = animations[name].getFrames();
    m_speed      = animations[name].getSpeed();
}