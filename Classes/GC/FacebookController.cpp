#include "FacebookController.h"

FacebookController::FacebookController():m_delegate(nullptr) {
	CCLOG("on setListener");
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	sdkbox::PluginFacebook::setListener(this);
#endif
}

void FacebookController::login() {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	sdkbox::PluginFacebook::login();
#endif
}

void FacebookController::logout() {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    sdkbox::PluginFacebook::logout();
#endif
}

bool FacebookController::isLoggedIn(){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return sdkbox::PluginFacebook::isLoggedIn();
#endif
}

void FacebookController::requestInvitableFriends(std::map<std::string, std::string> params) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    sdkbox::PluginFacebook::requestInvitableFriends(params);
#endif
}

void FacebookController::api(const std::string& path,
         const std::string& method,
         std::map<std::string, std::string> params,
         const std::string& tag) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    sdkbox::PluginFacebook::api(path, method, params, tag);

#endif
}

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
void FacebookController::onLogin(bool isLogin, const std::string& msg) {
	CCLOG("on Login %s", msg.c_str());
	if (m_delegate) {
		m_delegate->onLogin(isLogin, msg);
	}
    if(isLogin) {
        sdkbox::PluginFacebook::requestReadPermissions({FB_PERM_READ_PUBLIC_PROFILE, FB_PERM_READ_USER_FRIENDS,FB_PERM_READ_EMAIL});
    }
}
void FacebookController::onPermission(bool isLogin, const std::string& msg) {
	if (m_delegate) {
		m_delegate->onPermission(isLogin, msg);
	}
    if(isLogin) {
        FBAPIParam param;
        sdkbox::PluginFacebook::requestInvitableFriends(param);
    }
}
void FacebookController::onAPI(const std::string& tag, const std::string& jsonData) {
    CCLOG("jsonAPI %s", jsonData.c_str());
	if (m_delegate) {
		m_delegate->onAPI(tag, jsonData);
	}
}
void FacebookController::onSharedSuccess(const std::string& message) {
	if (m_delegate) {
		m_delegate->onSharedSuccess(message);
	}
}
void FacebookController::onSharedFailed(const std::string& message) {
	if (m_delegate) {
		m_delegate->onSharedFailed(message);
	}
}
void FacebookController::onSharedCancel() {
	if (m_delegate) {
		m_delegate->onSharedCancel();
	}
}

void FacebookController::onFetchFriends(bool ok, const std::string & msg){
    std::vector<FBGraphUser> fr = sdkbox::PluginFacebook::getFriends();
    CCLOG("on getFriends %s", msg.c_str());
}
void FacebookController::onRequestInvitableFriends(const FBInvitableFriendsInfo & invitable_friends_and_pagination_json_as_string){
    FBInvitableFriendsInfo a = invitable_friends_and_pagination_json_as_string;
  
}
void FacebookController::onInviteFriendsWithInviteIdsResult(bool result,
	const std::string & description){};
void FacebookController::onInviteFriendsResult(bool result, const std::string & description){
};
void FacebookController::onGetUserInfo(const FBGraphUser & userInfo){};
#endif

void FacebookController::setDelegate(FacebookDelegate *del) {
	m_delegate = del;
}