#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "Layer/FriendListLayer.h"
#include "Layer/SelectRoomLayer.h"
#include "Layer/WaitingRoomLayer.h"
#include "GameDelegate.h"

class MenuScene : public cocos2d::Layer, FacebookDelegate, GameDelegate
{
	FriendListLayer *m_frendListLayer;
	SelectRoomLayer *m_selectRoomLayer;
	WaitingRoomLayer *m_waitingRoomLayer;
	cocos2d::Sprite *m_avarta;
	cocos2d::Label *m_lblUserInfo;
	cocos2d::Label *m_lblHeart;
	cocos2d::Label *m_lblCash;

	//Game delegate
	//delegate
	void onReplay() {};
	void onReturnToMenu() {};
	void onEnterRoom(RoomModel *model);


	void callBackBtn(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type);
    
    //facebook delegate
    void onLogin(bool isLogin, const std::string& msg) {};
    void onPermission(bool isLogin, const std::string& msg) {};
    void onAPI(const std::string& tag, const std::string& jsonData);
    void onSharedSuccess(const std::string& message) {};
    void onSharedFailed(const std::string& message) {};
    void onSharedCancel(){};
    void onFetchFriends(bool ok, const std::string & msg) {};
    //virtual void onRequestInvitableFriends(const FBInvitableFriendsInfo & invitable_friends_and_pagination_json_as_string) =0;
    void onInviteFriendsWithInviteIdsResult(bool result,
                                            const std::string & description){};
    void onInviteFriendsResult(bool result, const std::string & description){};
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MenuScene);
};

#endif // __LOADING_SCENE_H__