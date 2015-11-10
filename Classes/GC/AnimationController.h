#ifndef __ANIMATION_CONTROLLER_H__
#define __ANIMATION_CONTROLLER_H__

#include "cocos2d.h"

class AnimationController
{
public:
	cocos2d::Animate*create(std::string prefix, int frameCount, float delay = 0.1f, int startIndex = 0);
};

#endif // __ANIMATION_CONTROLLER_H__
