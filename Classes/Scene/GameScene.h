#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "Layer/ResultLayer.h"

class GameScene : public Layer, GameDelegate, FacebookDelegate
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
    void onReturnToMenu();
    
    //fb Delegate
    void onLogin(bool isLogin, const std::string& msg);
    void onPermission(bool isLogin, const std::string& msg);
    void onAPI(const std::string& tag, const std::string& jsonData);
    void onSharedSuccess(const std::string& message);
    void onSharedFailed(const std::string& message);
    void onSharedCancel();
    void onFetchFriends(bool ok, const std::string & msg);
    //virtual void onRequestInvitableFriends(const FBInvitableFriendsInfo & invitable_friends_and_pagination_json_as_string) =0;
    void onInviteFriendsWithInviteIdsResult(bool result,
                                            const std::string & description);
    void onInviteFriendsResult(bool result, const std::string & description);
    //virtual void onGetUserInfo(const FBGraphUser & userInfo) = 0;
public:
    static Scene* createScene();

	void callBackRPS(Ref *sender, Widget::TouchEventType type);

    virtual bool init();
	void startNewRound();
    // implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
