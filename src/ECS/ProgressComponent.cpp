#include <headers/ECS/ProgressComponent.hpp>

#include <headers/Global.hpp>
#include <headers/Application.hpp>

ProgressComponent::ProgressComponent() {
    m_score = 0;
    m_score_str = "Score: 0";
    
    m_wrong_type = 0;
    m_WT_str = "Wrong: 0";

    m_font_id = yoster;
}

void ProgressComponent::setScoreText() {
    SDL_Surface* surface = TTF_RenderText_Blended(Application::getResourceManager()->getFont(m_font_id), m_score_str.c_str(), SDL_Color {255, 255, 255, 255});
    m_score_texture = SDL_CreateTextureFromSurface(Application::getRenderer(), surface);
    if (m_score_texture == nullptr)
        std::cout << "Unable to create texture ProgressComponent\n";

    SDL_FreeSurface(surface);

    SDL_QueryTexture(m_score_texture, nullptr, nullptr, &m_score_dest.w, &m_score_dest.h);
}

void ProgressComponent::setWrongText() {
    SDL_Surface* surface = TTF_RenderText_Blended(Application::getResourceManager()->getFont(m_font_id), m_WT_str.c_str(), SDL_Color {255, 255, 255, 255});
    m_WT_texture = SDL_CreateTextureFromSurface(Application::getRenderer(), surface);
    if (m_WT_texture == nullptr)
        std::cout << "Unable to create texture ProgressComponent\n";

    SDL_FreeSurface(surface);

    SDL_QueryTexture(m_WT_texture, nullptr, nullptr, &m_WT_dest.w, &m_WT_dest.h);
}

void ProgressComponent::setPos() {
    m_score_dest.x = TEXT_DEST_X;
    m_score_dest.y = SCORE_TEXT_DEST_Y;

    m_WT_dest.x = TEXT_DEST_X;
    m_WT_dest.y = WT_TEXT_DEST_Y;
}

void ProgressComponent::init() {
    setScoreText();
    setWrongText();
    setPos();
}

void ProgressComponent::update() {

}

void ProgressComponent::render() {
    SDL_RenderCopy(Application::getRenderer(), m_score_texture, nullptr, &m_score_dest);
    SDL_RenderCopy(Application::getRenderer(), m_WT_texture, nullptr, &m_WT_dest);
}

void ProgressComponent::increaseScore(const std::size_t& score) {
    m_score += score;
    m_score_str = "Score: " + NumToString(m_score);
    setScoreText();
}

void ProgressComponent::decreaseScore(const std::size_t& score) {
    if (m_score <= score)
        m_score = 0;
    else m_score -= score;

    m_score_str = "Score: " + NumToString(m_score);
    setScoreText();
}

void ProgressComponent::increaseWT(const std::size_t& char_count) {
    m_wrong_type += char_count;
    m_WT_str = "Wrong: " + NumToString(m_wrong_type);
    setWrongText();
}