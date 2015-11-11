#ifndef __SMARTFOX_DELEGATE_CLIENT_H__
#define __SMARTFOX_DELEGATE_CLIENT_H__
#include <string>
#include <vector>
#include "Buddy.h"
#include "User.h"
#include "Room.h"
#include "Invitation.h"
class SFDelegate {
public:
	virtual void onUserJoinRoomError() = 0;
	virtual void onUserLogout() = 0;
	virtual void onUserConnection(bool success) = 0;
	virtual void onUserLogin(bool success) = 0;
	virtual void onUserJoinRoom(std::string roomName) = 0;
	virtual void onUserEnterRoom(std::string userName, std::string roomName) = 0;
	virtual void onUserExitRoom(std::string userName, std::string roomName) = 0;
	virtual void onUserPublicChat(std::string userName, std::string roomName, std::string message) = 0;
	virtual void onAddBuddySuccess(Buddy *buddy) = 0;
	virtual void onBlockBuddySuccess(Buddy *buddy) = 0;
	virtual void onRemovedBuddy(Buddy *buddy) = 0;
	virtual void onBuddyMessage(string message, bool isMe) = 0;
	virtual void onUpdateBuddyVariables(Buddy *buddy, vector<string> varChanged) = 0;
	virtual void onUpdateRoomVariables(Room *room, vector<string> varChanged) = 0;
	virtual void onUpdateUserVariables(User *room, vector<string> varChanged) = 0;
	virtual void onBuddyError(std::string errorMessage) = 0;
	virtual void onUpdateBuddyOnlineStatus(bool online) = 0;
	virtual void onChangeRoomCapacity(Room *room) = 0;
	virtual void onChangeRoomName(Room *room, string oldName) = 0;
	virtual void onChangeRoomPassword(Room *room) = 0;
	virtual void onChangeRoomStateError(string message) = 0;
	virtual void onCreateRoom(Room *room) = 0;
	virtual void onFindRooms(std::vector<Room *> listRoom) = 0;
	virtual void onFindUsers(std::vector<User *> listUser) = 0;
	virtual void onAdminMessage(User *sender, std::string message) = 0;
	virtual void onModeratorMessage(User *sender, std::string message) = 0;
	virtual void onObjectMessage(User *sender, SFSObject* message) = 0;
	virtual void onInvitationReceived(Entities::Invitation::Invitation *inv) = 0;
	virtual void onPlayerToSpectator(bool sucess) = 0;
	virtual void onSpectatorToPlayer(bool sucess) = 0;
	virtual void onReplyInvitationError(string message) = 0;
	virtual void onSubscribeRoomGroup(vector<Room*> newRoom) = 0;
	virtual void onUnsubscribeRoomGroup(string oldGroupId) = 0;
	virtual void onSubcribeRoomGroupError(string message) = 0;
	virtual void onUnsubscribeRoomGroupError(string message) = 0;

};
#endif // __HELLOWORLD_SCENE_H__
