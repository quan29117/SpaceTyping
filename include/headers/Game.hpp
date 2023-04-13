#pragma once

#include <iostream>
#include <headers/Gameplay.hpp>
#include <headers/State.hpp>

class Game {
private:
//SDL
    SDL_Window*          m_window;
    static SDL_Renderer* m_renderer;
    
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

public:
    Game();
    virtual ~Game();

    static SDL_Renderer* getRenderer();

    void run();
    void clean();
};