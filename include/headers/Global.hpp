/*******************************************************************//*
 * Global const and functions for understanding and changing parameters
 * more easily
 *
 *********************************************************************/

#pragma once

#include <sstream>
#include <string>
#include <cmath>
#include <headers/Math/Vector2D.hpp>

//------------------------------Constant Value------------------------------------
//File path
//TODO : Edit the PATH_BEGIN for directing to folder "res" of this game
const std::string PATH_BEGIN        = "./res/";
const std::string PATH_BEGIN_IMAGE  = PATH_BEGIN + "img/";
const std::string PATH_BEGIN_FONT   = PATH_BEGIN + "font/";
const std::string PATH_BEGIN_AUDIO  = PATH_BEGIN + "audio/";

//Window
#define WINDOW_SIZE_WIDTH   1920
#define WINDOW_SIZE_HEIGHT  1080
#define FRAME_PER_SECOND    60

//RNG
#define MAX_RANDOM_NUMBER   2048

//Background
#define PLAYSTATE_BACKGROUND_WIDTH  3840
#define CAMERA_RECT         SDL_Rect  {0, 0, 1920, 1080}
#define BACKGROUND_DEST     SDL_FRect {0, 0, 1920, 1080}
#define BOARD_DEST          SDL_FRect {10, 10, 360, 150}

//Title
#define TITLE_DEST          SDL_FRect {620, 250, 720, 120}

//Mouse
#define MOUSE_WIDTH         15
#define MOUSE_HEIGHT        25.5
#define MOUSE_POINT_SIZE    1

//Button
#define BUTTON_WIDTH    400
#define BUTTON_HEIGHT   100

//Player
#define PLAYER_POS      Vector2D {40, 510}
#define PLAYER_SRC      SDL_Rect {0, 0, 431, 170}
#define PLAYER_SIZE     Vector2D {144, 57}
#define PLAYER_WIDTH    137.75
#define PLAYER_HEIGHT   130.25

//Enemy
#define ENEMY_START_POS_X   1980
#define ENEMY_SRC           SDL_Rect {0, 0, 540, 290}
#define ENEMY_SIZE          Vector2D {270, 130.5}
#define ENEMY_CENTER_X      135
#define ENEMY_CENTER_Y      105
#define ENEMY_SPEED         5
#define ENEMY_FIRE_CHANCE   1024

//Bullet
#define BULLET_SRC                SDL_Rect {0, 0, 1350, 1350}
#define BULLET_PLAYER_START_POS   Vector2D {184, 535}
#define BULLET_PLAYER_SIZE        Vector2D {25, 25}
#define BULLET_SPEED              7
#define BULLET_ENEMY_SIZE         Vector2D {50, 50}

//Explosion
#define EXPLOSION_SRC       SDL_Rect {0, 0, 150, 150}
#define EXPLOSION_SIZE      Vector2D {150, 150}

//Progress
#define TEXT_DEST_X         40
#define SCORE_TEXT_DEST_Y   30
#define WT_TEXT_DEST_Y      90

//--------------------------------Functions---------------------------------------
std::string NumToString(const unsigned int& i_num);
