/*******************************************************************//*
 * Implementation of the BulletPlayerTextComponent class.
 *
 *********************************************************************/

#include <headers/ECS/Text/BulletPlayerTextComponent.hpp>

BulletPlayerTextComponent::BulletPlayerTextComponent(const std::string& text) {
    m_text_ref = text;
}

BulletPlayerTextComponent::~BulletPlayerTextComponent() {}

int BulletPlayerTextComponent::remainingSize() {
    return m_text_ref.size();
}

bool BulletPlayerTextComponent::isFinished() {
    return (m_text_ref.size() == 0);
}

void BulletPlayerTextComponent::init() {}

void BulletPlayerTextComponent::update() {
    if (m_text_ref.size() == 0) {
        entity->destroy();
    }
}

void BulletPlayerTextComponent::render() {}