#include <headers/Game.hpp>

SDL_Renderer* Game::m_renderer = nullptr;

void Game::initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        std::cout << "SDL could not be initialized: " << SDL_GetError();
    else std::cout << "SDL system is ready to go\n";

    initWindow();
    initRenderer();
    initLib();
}

void Game::initWindow() {
    m_window = SDL_CreateWindow("SpaceType Shooting",
                                0, 0,
                                WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT,
                                SDL_WINDOW_MAXIMIZED);

    if (m_window == nullptr)
        std::cout << "SDL window created failed\n";
}

void Game::initRenderer() {
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (m_renderer == nullptr)
        std::cout << "SDL renderer created failed\n";

    // SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void Game::initLib() {
// Setup and initialize the SDL2_Image library
    int flags = IMG_INIT_PNG;
    int initStatus = IMG_Init(flags);
    if ((initStatus & flags) != flags)
        std::cout << "SDL2_Image format not available\n";
}

void Game::initSpec() {
    isRunning = true;
    frameDelay = 1000 / FRAME_PER_SECOND;
    states.push(new GamePlay());  //TODO : edit to new MainMenu
}

Game::Game() {
    initSDL();
    initSpec();
}

Game::~Game() {}

SDL_Renderer* Game::getRenderer() {
    return m_renderer;
}

void Game::run() {
    while (isRunning) {
        frameStart = SDL_GetTicks();

        if (!states.empty()) {
			//Run a function
			states.front()->run(states);
			if (states.front()->isClosed()) {
				delete states.front();
				states.pop();
			}
		}
        else break;

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }

    clean();
}

void Game::clean() {
    IMG_Quit();

    SDL_DestroyRenderer(m_renderer);
    m_renderer = nullptr;
    SDL_DestroyWindow(m_window);
    m_window = nullptr;

    SDL_Quit();
}