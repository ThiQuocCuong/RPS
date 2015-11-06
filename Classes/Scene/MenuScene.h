#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "../GC/GC.h"

class MenuScene : public cocos2d::Layer
{
	cocos2d::Sprite *m_avarta;
	cocos2d::Label *m_lblUserInfo;
	cocos2d::Label *m_lblHeart;
	cocos2d::Label *m_lblCash;

	void callBackBtn(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MenuScene);
};

#endif // __LOADING_SCENE_H__