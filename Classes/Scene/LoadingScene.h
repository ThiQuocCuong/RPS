#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "cocos2d.h"
#include "../GameController/GameController.h"
using namespace cocos2d;

class LoadingScene : public Layer
{
	int m_lastPercent;
	Label *m_lblPercent;
	void loadResources();
public:
    static Scene* createScene();
	virtual bool init();
	void update(float dt);
	CREATE_FUNC(LoadingScene);
};

#endif // __LOADING_SCENE_H__