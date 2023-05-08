/*******************************************************************//*
 * Implementation of the Application class.
 *
 *********************************************************************/

#include <headers/Application.hpp>

#include <SDL2/SDL_image.h>
#include <headers/Global.hpp>
#include <headers/Structs.hpp>
#include <headers/ApplicationState/MenuState.hpp>
#include <headers/ApplicationState/PlayState.hpp>

//Define static members
bool             Application::s_isRunning = true;
SDL_Renderer*    Application::s_renderer  = nullptr;
ResourceManager* Application::s_resMan    = new ResourceManager;
StateManager*    Application::s_stateMan  = new StateManager;

void Application::initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        std::cout << "SDL could not be initialized: " << SDL_GetError();
    else std::cout << "SDL system is ready to go\n";

    initWindow();
    initRenderer();
    initLib();
}

void Application::initWindow() {
    m_window = SDL_CreateWindow("SpaceTyping",
                                0, 0,
                                WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT,
                                SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (m_window == nullptr)
        std::cout << "SDL window created failed\n";
}

void Application::initRenderer() {
    s_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (s_renderer == nullptr)
        std::cout << "SDL renderer created failed\n";

    SDL_SetRenderDrawColor(s_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void Application::initLib() {
// Setup and initialize the SDL2_Image library
    int flag_IMG = IMG_INIT_PNG;
    int IMG_Status = IMG_Init(flag_IMG);
    if ((IMG_Status & flag_IMG) != flag_IMG)
        std::cout << "SDL2_Image format is not available\n";

// Setup and initialize the SDL2_TTF library
    if (TTF_Init() == -1)
        std::cout <<"SDL2_TTF format is not available\n";

// Setup and initialize the SDL2_Mixer library + Open Audio
    int flag_MIX = MIX_INIT_OGG;
    int MIX_Status = Mix_Init(flag_MIX);
    if ((MIX_Status & flag_MIX) != flag_MIX)
        std::cout <<"SDL2_Mixer format is not available\n";
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
}

void Application::initResMan() {
//Add Textures
    s_resMan->addTexture(mouse, "Mouse.png");
    s_resMan->addTexture(button, "Button.png");
    s_resMan->addTexture(player, "Player.png");
    s_resMan->addTexture(enemy, "Enemy.png");
    s_resMan->addTexture(bullet_player, "Bullet_Player.png");
    s_resMan->addTexture(bullet_enemy, "Bullet_Enemy.png");
    s_resMan->addTexture(menu_bg, "Menu_Background.png");
    s_resMan->addTexture(play_bg, "Play_Background.png");
    s_resMan->addTexture(pause_bg, "Pause_Background.png");
    s_resMan->addTexture(game_name, "Game_Name.png");
    s_resMan->addTexture(pause_title, "Pause_Title.png");
    s_resMan->addTexture(board, "Board.png");
    
//Add Fonts
    s_resMan->addFont(yoster, "yoster.ttf", 30);
    s_resMan->addFont(mariana, "mariana.ttf", 30);

//Add Musics
    s_resMan->addMusic(menu_bgm, "Menu_BGM.ogg");
    s_resMan->addMusic(play_bgm, "Play_BGM.ogg");

//Add Sounds
    s_resMan->addSound(player_shoot, "Player_Shoot.ogg");
    s_resMan->addSound(enemy_shoot, "Enemy_Shoot.ogg");
    s_resMan->addSound(button_hover, "Button_Hover.ogg");
}

void Application::initStateMan() {
    s_stateMan->pushState(menu_state);
}

void Application::initParam() {
    frameDelay = 1000 / FRAME_PER_SECOND;
    frameTime = frameStart = 0;
}

void Application::customApp() {
    SDL_ShowCursor(SDL_DISABLE);
}

Application::Application() {
    initSDL();
    initResMan();
    initStateMan();
    initParam();
    customApp();
}

Application::~Application() {}

void Application::closeApp() {
    s_isRunning = false;
}

SDL_Renderer* Application::getRenderer() {
    return s_renderer;
}

ResourceManager* Application::getResourceManager() {
    return s_resMan;
}

StateManager* Application::getStateManager() {
    return s_stateMan;
}

void Application::run() {
    while (s_isRunning) {
        frameStart = SDL_GetTicks();

        if (!s_stateMan->isExit())
			s_stateMan->run();
        else break;

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }
}

void Application::clear() {
    s_resMan->clear();
    delete s_resMan;

    delete s_stateMan;

    SDL_DestroyRenderer(s_renderer);
    s_renderer = nullptr;

    SDL_DestroyWindow(m_window);
    m_window = nullptr;

    Mix_CloseAudio();

    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}