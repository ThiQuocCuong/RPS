#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__

#include "SpriteController.h"
#include "ResourceController.h"
#include "ButtonController.h"
#include "LabelController.h"
#include "FacebookController.h"
#include "JsonController.h"
#include "AnimationController.h"
#include "smartfox/SmartfoxClient.h"
#include "../Prefix.h"
using namespace cocos2d;
using namespace extension;
using namespace ui;
using namespace std;

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
	AnimationController *m_animationController;
	SmartFoxClient *m_sfs2XClient;
public:
	static GC *gI();
	LabelController *lbl();
	ButtonController *btn();
	SpriteController *spr();
	ResourceController *resoure();
	FacebookController *fb();
	JsonController *json();
	AnimationController *anim();
	SmartFoxClient *sfs2X();
};

#endif // __HELLOWORLD_SCENE_H__
