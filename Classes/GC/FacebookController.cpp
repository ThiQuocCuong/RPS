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

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
void FacebookController::onLogin(bool isLogin, const std::string& msg) {
	CCLOG("on Login %s", msg.c_str());
	if (m_delegate) {
		m_delegate->onLogin(isLogin, msg);
	}
}
void FacebookController::onPermission(bool isLogin, const std::string& msg) {
	if (m_delegate) {
		m_delegate->onPermission(isLogin, msg);
	}
}
void FacebookController::onAPI(const std::string& tag, const std::string& jsonData) {
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

void FacebookController::onFetchFriends(bool ok, const std::string & msg){};
void FacebookController::onRequestInvitableFriends(const FBInvitableFriendsInfo & invitable_friends_and_pagination_json_as_string){};
void FacebookController::onInviteFriendsWithInviteIdsResult(bool result,
	const std::string & description){};
void FacebookController::onInviteFriendsResult(bool result, const std::string & description){};
void FacebookController::onGetUserInfo(const FBGraphUser & userInfo){};
#endif

void FacebookController::setDelegate(FacebookDelegate *del) {
	m_delegate = del;
}