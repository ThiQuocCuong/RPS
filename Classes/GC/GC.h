#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__

#include "SpriteController.h"
#include "ResourceController.h"
#include "ButtonController.h"
#include "LabelController.h"
#include "FacebookController.h"
#include "JsonController.h"
#include "../Prefix.h"
using namespace cocos2d;
using namespace extension;
using namespace ui;

class GC
{
	GC();
	static GC *m_controller;
	LabelController *m_lblController;
	ButtonController *m_btnController;
	SpriteController *m_sprController;
	ResourceController *m_resourceController;
	FacebookController *m_fbController;
	JsonController *m_jsonController;
public:
	static GC *gI();
	LabelController *lbl();
	ButtonController *btn();
	SpriteController *spr();
	ResourceController *resoure();
	FacebookController *fb();
	JsonController *json();
};

#endif // __HELLOWORLD_SCENE_H__
