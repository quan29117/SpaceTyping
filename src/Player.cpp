#include <headers/Player.hpp>

void Player::initSpec() {
//m_pos
    m_pos.w = PLAYER_WIDTH;
    m_pos.h = PLAYER_HEIGHT;
    m_pos.x = PLAYER_START_POS_X;
    m_pos.y = PLAYER_START_POS_Y;
    
}

void Player::initImage(SDL_Renderer* renderer) {
    SDL_Surface *image = IMG_Load((PATH_BEGIN_IMAGE + "Player.png").c_str());
    // SDL_Surface* image = new SDL_Surface (res->getImages("Player"));

    m_texture = SDL_CreateTextureFromSurface(renderer, image);
    if (m_texture == nullptr)
        std::cout << "Unable to create texture Player\n";
    
    SDL_FreeSurface(image);
}

Player::Player(SDL_Renderer* renderer) 
    : m_destroyed(false), m_wrong_type(0)
{
    initSpec();
    initImage(renderer);
}

Player::~Player() {
    SDL_DestroyTexture(m_texture);
}

bool Player::getStatus() {
	return m_destroyed;
}

unsigned int Player::getWrongType() {
	return m_wrong_type;
}

// std::vector<Bullet_Player*>& Player::getBE() {
// 	/**
// 		Return bullets to shoot Enemies
// 	*/
// 	return bullet_BE;
// }

// std::vector<Bullet_Player*>& Player::getBB() {
// 	/**
// 		Return bullets to shoot Bullet Enemy
// 	*/
// 	return bullet_BB;
// }

void Player::dead() {
	m_destroyed = true;
}

void Player::update() {
    
}

void Player::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, m_texture, nullptr, nullptr);
}