#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__

#include "cocos2d.h"
#include "SpriteController.h"
#include "ResourceController.h"
#include "ButtonController.h"
#include "LabelController.h"
#include "FacebookController.h"
#include "../Prefix.h"

class GC
{
	GC();
	static GC *m_controller;
	LabelController *m_lblController;
	ButtonController *m_btnController;
	SpriteController *m_sprController;
	ResourceController *m_resourceController;
	FacebookController *m_fbController;
public:
	static GC *gI();
	LabelController *lbl();
	ButtonController *btn();
	SpriteController *spr();
	ResourceController *resoure();
	FacebookController *fb();
};

#endif // __HELLOWORLD_SCENE_H__
