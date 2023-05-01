#pragma once

#include <headers/ECS/ECS.hpp>

class LockEnemyComponent : public Component {
private:
    Entity*         m_lock_enemy;
    std::string*    m_text;

public:
    LockEnemyComponent();
    virtual ~LockEnemyComponent();

    bool isFree();
    char getCharNeedTyped();

    void init() override;
    void update() override;
    void render() override;

    void changeColorText();
    void lock(Entity* enemy);
    void freeLock();
};