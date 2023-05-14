/*******************************************************************//*
 * ApplicationState class for the game.
 * This state is entered after clicking the "Back to Menu" button
 * from the pause game state
 *
 *********************************************************************/

#pragma once

#include <SDL2/SDL_pixels.h>
#include <headers/ApplicationState/State.hpp>

class ResultState : public State {
private:
    enum ButtonNames {menu_back = 0};

//Progress Display
    SDL_Texture* m_score_texture;
    SDL_Rect     m_score_dest;

    SDL_Texture* m_wrong_texture;
    SDL_Rect     m_wrong_dest;

    SDL_Color    m_text_color;

//Functions
    void setScoreText();
    void setWrongText();

    void initBackground() override;
    void initButtons()	  override;

    void pollEvent() override;
	void update()	 override;
	void render()	 override;

public:
    ResultState();
    virtual ~ResultState();

    void run()		 override;
};