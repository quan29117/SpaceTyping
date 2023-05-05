#pragma once

#include <sstream>
#include <string>
#include <cmath>
#include <headers/Vector2D.hpp>

//------------------------------Constant Value------------------------------------
//File path
const std::string PATH_BEGIN        = "D:/Project/SDL/SpaceTyping/res/";
const std::string PATH_BEGIN_IMAGE  = PATH_BEGIN + "img/";
const std::string PATH_BEGIN_FONT   = PATH_BEGIN + "font/";
const std::string PATH_BEGIN_AUDIO  = PATH_BEGIN + "audio/";

//Window
#define WINDOW_SIZE_WIDTH   1920
#define WINDOW_SIZE_HEIGHT  1080
#define FRAME_PER_SECOND    60

//Background
#define PLAYSTATE_BACKGROUND_WIDTH  3840
#define BACKGROUND_WIDTH            1920
#define BACKGROUND_HEIGHT           1080

//Title
#define TITLE_WIDTH     800
#define TITLE_HEIGHT    225

//Mouse
#define MOUSE_WIDTH     15
#define MOUSE_HEIGHT    25.5

//Button
#define BUTTON_WIDTH    400
#define BUTTON_HEIGHT   100

//Player
#define PLAYER_POS          Vector2D {40, 410}
#define PLAYER_WIDTH        137.75
#define PLAYER_HEIGHT       130.25
#define PLAYER_CENTER       Vector2D {73.875, 270.125}

//Enemy
#define ENEMY_START_POS_X   1680
#define ENEMY_WIDTH         243
#define ENEMY_HEIGHT        130.5
#define ENEMY_CENTER_X      120
#define ENEMY_CENTER_Y      95
#define ENEMY_FIRE_CHANCE   1024
#define ENEMY_SPEED         3

//Bullet
#define BULLET_PLAYER_START_POS     Vector2D {40, 410}
#define BULLET_PLAYER_SIZE          35
#define BULLET_PLAYER_SPEED         5
#define BULLET_ENEMY_SIZE           50
#define BULLET_ENEMY_SPEED          5

//--------------------------------Functions---------------------------------------
std::string NumToString(const unsigned int& i_num);
