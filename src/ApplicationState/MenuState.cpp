/*******************************************************************//*
 * Implementation of the MenuState class.
 *
 *********************************************************************/

#include <headers/ApplicationState/MenuState.hpp>

#include <headers/Global.hpp>
#include <headers/Application.hpp>
#include <headers/Structs.hpp>

void MenuState::initBackground() {
    m_bg_texture = Application::getResourceManager()->getTexture(menu_bg);
    m_bg_dest = SDL_FRect {0, 0, WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT};

    m_title_texture = Application::getResourceManager()->getTexture(game_name);
    m_title_dest = TITLE_DEST;
}

void MenuState::initButtons() {
    m_buttons.push_back (new Button (SDL_Rect {80, 0, 240, 100},
                                     SDL_Rect {480, 0, 240, 100},
                                     SDL_FRect {650, 400, 240, 100}));
    m_buttons.push_back (new Button (SDL_Rect {100, 200, 200, 100},
                                     SDL_Rect {500, 200, 200, 100},
                                     SDL_FRect {660, 550, 200, 100}));
}

MenuState::MenuState() {
    initState(menu_state);
}

MenuState::~MenuState() {
    m_bg_texture = nullptr;
    for (auto& button : m_buttons) {
        delete button;
        button = nullptr;
    }
}

void MenuState::run() {
    pollEvent();
    update();
    render();
}

void MenuState::pollEvent() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				m_close = true;
                Application::closeApp();
				break;
                
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (m_buttons[start]->isHovered()) {
                        m_pause = true;
                        Application::getStateManager()->pushState(play_state);
                    }

                    if (m_buttons[exit]->isHovered())
                        m_close = true;
                }
                break;
		}
	}
}

void MenuState::update() {
    if (!m_pause) {
        updateInteraction();
        AudioManager::loopMusic();
    }
}

void MenuState::render() {
    SDL_RenderClear(Application::getRenderer());

    if (!m_pause) {
        TextureManager::render(m_bg_texture, nullptr, &m_bg_dest);
        TextureManager::render(m_title_texture, nullptr, &m_title_dest);
        for (auto& button : m_buttons) button->render();
        m_mouse.render();
    }

    SDL_RenderPresent(Application::getRenderer());
}