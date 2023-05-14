/*******************************************************************//*
 * Implementation of the ResultState class.
 *
 *********************************************************************/

#include <headers/ApplicationState/ResultState.hpp>

#include <headers/Global.hpp>
#include <headers/Application.hpp>
#include <headers/ApplicationManager/ResourceMethodManager.hpp>
#include <headers/ApplicationState/PlayState.hpp>

void ResultState::initBackground() {
    if (!PlayState::getWinning()) {
        m_bg_texture = Application::getResourceManager()->getTexture(result_bg1);
        m_text_color = SDL_Color {255, 255, 255, 255};
        AudioManager::playMusic(result_defeated_bgm);
    } else {
        m_bg_texture = Application::getResourceManager()->getTexture(result_bg2);
        m_text_color = SDL_Color {255, 255, 0, 255};
        AudioManager::playMusic(result_victory_bgm);
    }
    
    m_bg_dest = BACKGROUND_DEST;

    m_score_dest.x = RESULT_DEST_X;
    m_score_dest.y = RESULT_SC_Y;

    m_wrong_dest.x = RESULT_DEST_X;
    m_wrong_dest.y = RESULT_WT_Y;
}

void ResultState::initButtons() {
    m_buttons.push_back (new Button (SDL_Rect {15, 300, 620, 100},
                                     SDL_Rect {665, 300, 620, 100},
                                     SDL_FRect {655, 900, 620, 100}));
}

ResultState::ResultState() {
    initState(result_state);
    setScoreText();
    setWrongText();
}

ResultState::~ResultState() {}

void ResultState::run() {
    pollEvent();
    update();
    render();
}

void ResultState::setScoreText() {
    std::string text = "SCORE: " + NumToString(Application::getScore());

    SDL_Surface* surface = TTF_RenderText_Blended(Application::getResourceManager()->getFont(pixel_80), text.c_str(), m_text_color);
    m_score_texture = SDL_CreateTextureFromSurface(Application::getRenderer(), surface);
    if (m_score_texture == nullptr)
        std::cout << "Unable to create texture ScoreTexture\n";
        
    SDL_FreeSurface(surface);

    SDL_QueryTexture(m_score_texture, nullptr, nullptr, &m_score_dest.w, &m_score_dest.h);
}

void ResultState::setWrongText() {
    std::string text = "Wrong: " + NumToString(Application::getWrongCount());

    SDL_Surface* surface = TTF_RenderText_Blended(Application::getResourceManager()->getFont(pixel_80), text.c_str(), m_text_color);
    m_wrong_texture = SDL_CreateTextureFromSurface(Application::getRenderer(), surface);
    if (m_wrong_texture == nullptr)
        std::cout << "Unable to create texture ScoreTexture\n";
        
    SDL_FreeSurface(surface);

    SDL_QueryTexture(m_wrong_texture, nullptr, nullptr, &m_wrong_dest.w, &m_wrong_dest.h);
}

void ResultState::pollEvent() {
    SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				m_close = true;
                Application::closeApp();
				break;
                
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (m_buttons[menu_back]->isHovered()) {
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

void ResultState::update() {
    if (!m_pause)
        updateInteraction();
}

void ResultState::render() {
    SDL_RenderClear(Application::getRenderer());

    if (!m_pause) {
        TextureManager::render(m_bg_texture, nullptr, &m_bg_dest);
        SDL_RenderCopy(Application::getRenderer(), m_score_texture, nullptr, &m_score_dest);
        SDL_RenderCopy(Application::getRenderer(), m_wrong_texture, nullptr, &m_wrong_dest);
        for (auto& button : m_buttons) button->render();
        m_mouse.render();
    }

    SDL_RenderPresent(Application::getRenderer());
}