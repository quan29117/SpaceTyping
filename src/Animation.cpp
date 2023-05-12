/*******************************************************************//*
 * Implementation of the Animation class.
 *
 *********************************************************************/

#include <headers/Animation.hpp>

Animation::Animation() {}

Animation::Animation(const unsigned int& i, const unsigned int& f, const unsigned int& s)
    : m_index(i), m_frames(f), m_speed(s)
{}

Animation::~Animation() {}

unsigned int Animation::getIndex() {
    return m_index;
}

unsigned int Animation::getFrames() {
    return m_frames;
}

unsigned int Animation::getSpeed() {
    return m_speed;
}
