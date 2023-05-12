/*******************************************************************//*
 * Animation class is used to archive and run animation of object
 *
 *********************************************************************/

#pragma once

#include <iostream>

class Animation {
private:
    unsigned int m_index;
    unsigned int m_frames;
    unsigned int m_speed;

public:
    Animation();
    Animation (const unsigned int& i, const unsigned int& f, const unsigned int& s);
    virtual ~Animation();

    unsigned int getIndex();
    unsigned int getFrames();
    unsigned int getSpeed();
};