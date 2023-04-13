#pragma once

#include <iostream> //TODO : Delete this
#include <sstream>
#include <string>
#include <cmath>

//------------------------------Constant Value------------------------------------
//File path
const std::string PATH_BEGIN        = "D:/Project/SDL/SpaceTyping/res/";
const std::string PATH_BEGIN_IMAGE  = PATH_BEGIN + "img/";
const std::string PATH_BEGIN_FONT   = PATH_BEGIN + "font/";
const std::string PATH_BEGIN_AUDIO  = PATH_BEGIN + "audio/";

//Window
#define WINDOW_SIZE_WIDTH  1920
#define WINDOW_SIZE_HEIGHT 1080
#define FRAME_PER_SECOND   60

//Player
#define PLAYER_START_POS_X 10
#define PLAYER_START_POS_Y 410
#define PLAYER_WIDTH       137.75
#define PLAYER_HEIGHT      130.25

//Enemy
#define ENEMY_START_POS_X  1920
#define ENEMY_WIDTH        243
#define ENEMY_HEIGHT       130.5
#define ENEMY_FIRE_CHANCE  1024
#define ENEMY_VELOCITY     50
#define ENEMY_BULLET_VELOCITY  200

//Bullet
#define BULLET_PLAYER_START_POS_X 40
#define BULLET_PLAYER_START_POS_Y 410
#define BULLET_PLAYER_SIZE 28.125
#define BULLET_PLAYER_VELOCITY 600

//--------------------------------Functions---------------------------------------
std::string NumToString(const unsigned int& i_num);
