/*******************************************************************//*
 * Class is used to manage Enemy-spawning for gameplay
 *
 *********************************************************************/

#pragma once

#include <random>
#include <chrono>
#include <headers/ECS/ECS.hpp>

using TimePoint = std::chrono::system_clock::time_point;
using TimeDuration = std::chrono::duration<double>;

class SpawnManager {
private:
//RNG - random number generator
	std::random_device m_rd;
	std::mt19937 m_rng;

//Word list
	std::vector <std::string> m_word_list;

//Timer
    unsigned short m_spawn_CD;
    TimePoint m_last_spawn;
    TimeDuration m_elapsed_seconds;

//Funtions
    void initWordList();
    bool canSpawn();
    std::string generatedWords();
    Entity& createEnemy();

public:
    SpawnManager();
    virtual ~SpawnManager();

    void update();
};
