#include <headers/Application.hpp>

#include <SDL2/SDL_image.h>
#include <headers/Global.hpp>
#include <headers/GameState/MenuState.hpp>
#include <headers/GameState/PlayState.hpp>

SDL_Renderer* Application::m_renderer = nullptr;
ResourceManager* Application::m_resMan = new ResourceManager;

void Application::initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        std::cout << "SDL could not be initialized: " << SDL_GetError();
    else std::cout << "SDL system is ready to go\n";

    initWindow();
    initRenderer();
    initLib();
}

void Application::initWindow() {
    m_window = SDL_CreateWindow("SpaceType Shooting",
                                0, 0,
                                WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT,
                                SDL_WINDOW_MAXIMIZED);

    if (m_window == nullptr)
        std::cout << "SDL window created failed\n";
}

void Application::initRenderer() {
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (m_renderer == nullptr)
        std::cout << "SDL renderer created failed\n";

    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void Application::initLib() {
// Setup and initialize the SDL2_Image library
    int flags = IMG_INIT_PNG;
    int initStatus = IMG_Init(flags);
    if ((initStatus & flags) != flags)
        std::cout << "SDL2_Image format not available\n";

// Setup and initialize the SDL2_TTF library
    if (TTF_Init() == -1) 
        std::cout <<"SDL2_TTF format not available\n";
}

void Application::initResMan() {
//Add Textures
    m_resMan->addTexture(mouse, "Mouse.png");
    m_resMan->addTexture(button, "Button.png");
    m_resMan->addTexture(player, "Player.png");
    m_resMan->addTexture(enemy, "Enemy.png");
    m_resMan->addTexture(bullet_player, "Bullet_Player.png");
    m_resMan->addTexture(bullet_enemy, "Bullet_Enemy.png");
    m_resMan->addTexture(menu_bg, "Menu_Background.png");
    m_resMan->addTexture(play_bg, "Play_Background.png");
    
//Add Fonts
    m_resMan->addFont(yoster, "yoster.ttf", 30);
    m_resMan->addFont(mariana, "mariana.ttf", 30);
}

void Application::initSpec() {
    isRunning = true;
    frameDelay = 1000 / FRAME_PER_SECOND;
    states.push(new MenuState());
}

void Application::customApp() {
    SDL_ShowCursor(SDL_DISABLE);
}

Application::Application() {
    initSDL();
    initResMan();
    initSpec();
    customApp();
}

Application::~Application() {}

ResourceManager* Application::getResourceManager() {
    return m_resMan;
}

SDL_Renderer* Application::getRenderer() {
    return m_renderer;
}

void Application::run() {
    while (isRunning) {
        frameStart = SDL_GetTicks();

        if (!states.empty()) {
			states.top()->run(states);
			if (states.top()->isClosed()) {
				delete states.top();
				states.pop();
			}
		}
        else break;

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }
}

void Application::clean() {
    m_resMan->clear();
    
    SDL_DestroyRenderer(m_renderer);
    m_renderer = nullptr;
    SDL_DestroyWindow(m_window);
    m_window = nullptr;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}