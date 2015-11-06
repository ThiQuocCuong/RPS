#ifndef __LOGIN_SCENE_H__
#define __LOGIN_SCENE_H__

#include "../GC/GC.h"

class LoginScene : public cocos2d::Layer
{
	cocos2d::ui::Button *m_btnLogin;
	cocos2d::Node *m_loginNode;
	void callBackBtn(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LoginScene);
};

#endif // __LOADING_SCENE_H__