#ifndef __FACEBOOK_CONTROLLER_H__
#define __FACEBOOK_CONTROLLER_H__
#include "cocos2d.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "PluginFacebook/PluginFacebook.h"
using namespace sdkbox;
#endif

class FacebookDelegate {
public:
	virtual void onLogin(bool isLogin, const std::string& msg) = 0;
	virtual void onPermission(bool isLogin, const std::string& msg) = 0;
	virtual void onAPI(const std::string& tag, const std::string& jsonData) = 0;
	virtual void onSharedSuccess(const std::string& message) = 0;
	virtual void onSharedFailed(const std::string& message) = 0;
	virtual void onSharedCancel() = 0;
	virtual void onFetchFriends(bool ok, const std::string & msg) = 0;
	//virtual void onRequestInvitableFriends(const FBInvitableFriendsInfo & invitable_friends_and_pagination_json_as_string) =0;
	virtual void onInviteFriendsWithInviteIdsResult(bool result,
		const std::string & description) =0;
	virtual void onInviteFriendsResult(bool result, const std::string & description) = 0;
	//virtual void onGetUserInfo(const FBGraphUser & userInfo) = 0;
};

class FacebookController	
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	:public sdkbox::FacebookListener 
#endif
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	void onLogin(bool isLogin, const std::string& msg);
	void onPermission(bool isLogin, const std::string& msg);
	void onAPI(const std::string& tag, const std::string& jsonData);
	void onSharedSuccess(const std::string& message);
	void onSharedFailed(const std::string& message);
	void onSharedCancel();
	void onFetchFriends(bool ok, const std::string & msg);
	void onRequestInvitableFriends(const FBInvitableFriendsInfo & invitable_friends_and_pagination_json_as_string);
	void onInviteFriendsWithInviteIdsResult(bool result,
		const std::string & description);
	void onInviteFriendsResult(bool result, const std::string & description);
	void onGetUserInfo(const FBGraphUser & userInfo);
#endif
	FacebookDelegate *m_delegate;
public:
	FacebookController();
	void setDelegate(FacebookDelegate *del);
	void login();
};

#endif // __LABEL_CONTROLLER_H__
