#include <headers/GameState/MenuState.hpp>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <headers/Global.hpp>
#include <headers/Application.hpp>
#include <headers/Structs.hpp>
#include <headers/GameState/PlayState.hpp>

void MenuState::initBackground() {
    m_bg_texture = Application::getResourceManager()->getTexture(menu_bg);
    m_bg_dest.x  = m_bg_dest.y = 0;
    m_bg_dest.w  = BACKGROUND_WIDTH;
    m_bg_dest.h  = BACKGROUND_HEIGHT;

    m_title_texture = Application::getResourceManager()->getTexture(title);
    m_title_dest.x  = 100;
    m_title_dest.y  = 150;
    m_title_dest.w  = TITLE_WIDTH;
    m_title_dest.h  = TITLE_HEIGHT;
}

void MenuState::initButtons() {
    m_buttons.push_back (new Button (SDL_Rect {80, 0, 240, 100},
                                     SDL_Rect {480, 0, 240, 100},
                                     SDL_FRect {150, 400, 240, 100}));
    m_buttons.push_back (new Button (SDL_Rect {100, 200, 200, 100},
                                     SDL_Rect {500, 200, 200, 100},
                                     SDL_FRect {150, 550, 200, 100}));
}

MenuState::MenuState() {
    initState(StateName::menu);
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
                    if (m_buttons[start]->isSelected()) {
                        Application::getStateManager()->pushState(StateName::play);
                        m_pause = true;
                    }
                    if (m_buttons[exit]->isSelected())
                        m_close = true;
                }
                break;
		}
	}
}

void MenuState::update() {
    m_mouse.update();
    for (auto& button : m_buttons) button->update(m_mouse);
}

void MenuState::render() {
    SDL_RenderClear(Application::getRenderer());

    TextureManager::render(m_bg_texture, &m_bg_dest);
    TextureManager::render(m_title_texture, &m_title_dest);

    for (auto& button : m_buttons) button->render();
    m_mouse.render();

    SDL_RenderPresent(Application::getRenderer());
}