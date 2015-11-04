#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "ResultLayer.h"
#include "GameDelegate.h"
#include "GameController/GameController.h"

class GameScene : public Layer, GameDelegate
{
	ResultLayer *m_resultLayer;
	Label *m_lblCountDown;
	int m_countDown;
	Label *m_lblUser1Name;
	Label *m_lblUser2Name;
	Sprite *m_sprUser1;
	Sprite *m_sprUser2;
	Sprite *m_sprAvarta1;
	Sprite *m_sprAvarta2;
	
	BattleResult getResult(int user1Result, int user2Result);
	Action *getDisorderAction();
	void update(float dt);
	void updateCountDown(float dt);

	//delegate
	void onReplay();
public:
    static Scene* createScene();

	void callBackRPS(Ref *sender, Widget::TouchEventType type);

    virtual bool init();
	void startNewRound();
    // implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
