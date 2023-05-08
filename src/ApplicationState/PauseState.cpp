/*******************************************************************//*
 * Implementation of the PauseState class.
 *
 *********************************************************************/

#include <headers/ApplicationState/PauseState.hpp>

#include <headers/Global.hpp>
#include <headers/Application.hpp>
#include <headers/Structs.hpp>

void PauseState::initBackground() {
    m_bg_texture = Application::getResourceManager()->getTexture(pause_bg);
    m_bg_dest = BACKGROUND_DEST;

    m_title_texture = Application::getResourceManager()->getTexture(pause_title);
    m_title_dest = TITLE_DEST;
}

void PauseState::initButtons() {
    m_buttons.push_back (new Button (SDL_Rect {0, 100, 400, 100},
                                     SDL_Rect {400, 100, 400, 100},
                                     SDL_FRect {580, 400, 400, 100}));
    m_buttons.push_back (new Button (SDL_Rect {100, 200, 200, 100},
                                     SDL_Rect {500, 200, 200, 100},
                                     SDL_FRect {660, 550, 200, 100}));
}

PauseState::PauseState() {
    initState(pause_state);
}

PauseState::~PauseState() {
    m_bg_texture = nullptr;
    for (auto& button : m_buttons) {
        delete button;
        button = nullptr;
    }
}

void PauseState::run() {
    pollEvent();
    update();
    render();
}

void PauseState::pollEvent() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				m_close = true;
                Application::closeApp();
				break;
                
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (m_buttons[conti]->isHovered()) {
                        m_close = true;
                        AudioManager::setVolume(100);
                        Application::getStateManager()->changeCurrentState(play_state);
                    }

                    if (m_buttons[exit]->isHovered()) {
                        m_close = true;
                        AudioManager::setVolume(100);
                        AudioManager::playMusic(menu_bgm);
                        Application::getStateManager()->changeCurrentState(menu_state);
                    }
                }
                break;
		}
	}
}

void PauseState::update() {
    if (!m_pause)
        updateInteraction();
}

void PauseState::render() {
    SDL_RenderClear(Application::getRenderer());

    if (!m_pause) {
        TextureManager::render(m_bg_texture, nullptr, &m_bg_dest);
        TextureManager::render(m_title_texture, nullptr, &m_title_dest);
        for (auto& button : m_buttons) button->render();
        m_mouse.render();
    }

    SDL_RenderPresent(Application::getRenderer());
}