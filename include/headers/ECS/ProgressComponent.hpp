/*******************************************************************//*
 * Component for Score and Wrong Typing Count.
 *
 *********************************************************************/

#pragma once

#include <headers/ECS/ECS.hpp>
#include <headers/ApplicationManager/ResourceManager.hpp>

class ProgressComponent : public Component {
private:
    std::size_t  m_score;
    std::string  m_score_str;
    SDL_Texture* m_score_texture;
    SDL_Rect     m_score_dest;

    std::size_t  m_wrong_type;
    std::string  m_WT_str;
    SDL_Texture* m_WT_texture;
    SDL_Rect     m_WT_dest;

    FontID       m_font_id;

    void setScoreText();
    void setWrongText();
    void setPos();

public:
    ProgressComponent();
    virtual ~ProgressComponent();

    void init()   override;
    void update() override;
    void render() override;

    void increaseScore(const std::size_t& score);
    void decreaseScore(const std::size_t& score);
    void increaseWT(const std::size_t& char_count);
};