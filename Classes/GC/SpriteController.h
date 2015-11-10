#ifndef __SPRITE_CONTROLLER_H__
#define __SPRITE_CONTROLLER_H__

#include "cocos2d.h"
#include "RemoteSprite.h"

class SpriteController
{
public:
    RemoteSprite *createWithURL(std::string url, std::string defaultImg = "");
};

#endif // __HELLOWORLD_SCENE_H__
