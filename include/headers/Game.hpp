#pragma once

#include <iostream>
#include <headers/Gameplay.hpp>
#include <headers/ResourceManager.hpp>

class Game {
private:
//SDL
    SDL_Window*          m_window;
    static SDL_Renderer* m_renderer;
    static ResourceManager* m_resMan;
    
//Spec
    bool isRunning;
    int frameDelay, frameTime, frameStart;
    std::queue <State*> states;

//Funtions
    void initSDL();
    void initWindow();
    void initRenderer();
    void initLib();
    void initSpec();
    void initResMan();

public:
    Game();
    virtual ~Game();

    static ResourceManager* getResourceManager();
    static SDL_Renderer* getRenderer();

    void run();
    void clean();
};